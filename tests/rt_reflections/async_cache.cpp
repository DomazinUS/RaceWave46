#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
#include "common/rt64_wr64_async_cache.h"

using Clock=std::chrono::steady_clock;
static size_t checks=0;
static void require(bool value,const char* message){++checks;if(!value)throw std::runtime_error(message);}
struct Result {
    int value;std::atomic<int>* destroyed;
    ~Result(){++*destroyed;}
};
int main() {
    std::setvbuf(stdout,nullptr,_IONBF,0);
    try {
        std::mutex gateMutex;std::condition_variable gateChanged;
        bool started=false,release=false;std::atomic<int> builds{0},secondBuilds{0},failedBuilds{0},destroyed{0};
        RT64::Wr64AsyncCache<Result,4> cache;
        auto slowCompiler=[&]() {
            ++builds;std::unique_lock lock(gateMutex);started=true;gateChanged.notify_all();
            // A bounded emergency release ensures an incorrect blocking cache
            // fails the timing assertion instead of hanging the test itself.
            gateChanged.wait_for(lock,std::chrono::seconds(2),[&]{return release;});
            return std::make_unique<Result>(Result{41,&destroyed});
        };
        auto secondCompiler=[&](){++secondBuilds;return std::make_unique<Result>(Result{42,&destroyed});};
        const auto begin=Clock::now();const Result* initial=cache.get(0,slowCompiler,false);
        const double requestMs=std::chrono::duration<double,std::milli>(Clock::now()-begin).count();
        bool observedStart;
        {std::unique_lock lock(gateMutex);observedStart=gateChanged.wait_for(lock,std::chrono::seconds(2),[&]{return started;});}
        bool pending=true;double maxPollMs=0;const auto pollBegin=Clock::now();
        for(uint32_t i=0;i<2000;++i) {
            const auto t=Clock::now();pending &= cache.get(0,slowCompiler,false)==nullptr;
            pending &= cache.get(1,secondCompiler,false)==nullptr;
            maxPollMs=std::max(maxPollMs,std::chrono::duration<double,std::milli>(Clock::now()-t).count());
        }
        const double pollsMs=std::chrono::duration<double,std::milli>(Clock::now()-pollBegin).count();
        const bool secondStayedQueued=secondBuilds.load()==0;
        {std::lock_guard lock(gateMutex);release=true;}gateChanged.notify_all();cache.waitForPending();
        require(observedStart&&initial==nullptr&&pending&&secondStayedQueued,"Pending compiler blocked/published or ran duplicate work");
        require(requestMs<100&&maxPollMs<100&&pollsMs<250,"Async requests waited for the held compiler");
        require(builds==1&&secondBuilds==1,"Repeated pending requests compiled a key more than once");
        const Result* first=cache.get(0,slowCompiler,false);const Result* second=cache.get(1,secondCompiler,false);
        require(first&&second&&first->value==41&&second->value==42,"Ready results were not published under the requested keys");
        for(uint32_t i=0;i<100;++i)require(cache.get(0,slowCompiler,false)==first&&cache.get(1,secondCompiler,false)==second,"Published pipeline pointers changed");
        auto fail=[&]()->std::unique_ptr<Result>{++failedBuilds;throw std::runtime_error("injected compiler failure");};
        cache.get(2,fail,false);cache.waitForPending();
        for(uint32_t i=0;i<100;++i)require(cache.get(2,fail,false)==nullptr,"Failed compile returned a result");
        require(failedBuilds==1,"Failed compile was requeued every frame");
        require(cache.get(99,slowCompiler,false)==nullptr&&builds==1,"Out-of-range key scheduled work");
        // Account only for live heap objects: the aggregate temporaries above
        // also destroy, so establish the baseline immediately before reset.
        const int destroyedBeforeReset=destroyed;
        cache.reset();require(destroyed==destroyedBeforeReset+2,"Cache reset did not release its two published objects");
        const auto* recovered=cache.get(2,secondCompiler,true);
        require(recovered&&recovered->value==42&&secondBuilds==2,"Explicit reset did not allow a failed key to be retried");
        // Destruction must join the worker before the factory's captured
        // resources can be released. Hold a real pending callback while a
        // separate owner destroys the cache, then release it explicitly.
        std::mutex drainMutex;std::condition_variable drainChanged;
        bool drainStarted=false,drainRelease=false;
        std::atomic<bool> destroyStarted{false},destroyReturned{false},factoryFinished{false};
        auto draining=std::make_unique<RT64::Wr64AsyncCache<Result,1>>();
        draining->get(0,[&]() {
            std::unique_lock lock(drainMutex);drainStarted=true;drainChanged.notify_all();
            drainChanged.wait(lock,[&]{return drainRelease;});
            factoryFinished=true;
            return std::make_unique<Result>(Result{43,&destroyed});
        },false);
        {std::unique_lock lock(drainMutex);drainChanged.wait(lock,[&]{return drainStarted;});}
        const int destroyedBeforeDrain=destroyed;
        std::thread owner([&]() {destroyStarted=true;draining.reset();destroyReturned=true;});
        while(!destroyStarted.load())std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        const bool heldDestruction=!destroyReturned.load()&&!factoryFinished.load();
        {std::lock_guard lock(drainMutex);drainRelease=true;}drainChanged.notify_all();owner.join();
        require(heldDestruction&&destroyReturned&&factoryFinished,"Cache destructor returned while its compiler still used captured resources");
        require(destroyed==destroyedBeforeDrain+2,"Pending result was not destroyed after draining the compiler");
        std::printf("PASS: %zu checks; initial_ms=%.6f, 4000 held-compiler requests_ms=%.6f, max_pair_ms=%.6f; stable publication, sticky failure and reset\n",checks,requestMs,pollsMs,maxPollMs);
        return 0;
    }
    catch(const std::exception& e){std::fprintf(stderr,"FAIL after %zu checks: %s\n",checks,e.what());return 1;}
}
