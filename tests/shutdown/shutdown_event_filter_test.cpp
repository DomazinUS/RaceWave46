#define SDL_MAIN_HANDLED
#include <Windows.h>
#include <SDL.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <thread>
#include "event_filter.inc"

using namespace std::chrono_literals;
namespace {
unsigned assertions=0;
void check(bool condition,const char* message) {
    ++assertions;
    if (!condition) {std::fprintf(stderr,"%s (%s)\n",message,SDL_GetError());std::abort();}
}
struct Prior {std::atomic<unsigned> calls{0};};
int prior_filter(void* userdata,SDL_Event* event) {
    if (event->type==SDL_USEREVENT) {
        ++static_cast<Prior*>(userdata)->calls;
        return event->user.code==42?0:1;
    }
    return 1;
}
int other_filter(void*,SDL_Event*) {return 1;}
struct Listener:RT64::ApplicationWindow::Listener {
    std::atomic<unsigned> calls{0},windowCalls{0};
    bool enabled=true,consume=false,recurse=false,block=false;
    std::mutex mutex;
    std::condition_variable condition;
    bool entered=false,released=false;
    bool usesWindowMessageFilter() override {return enabled;}
    bool windowMessageFilter(unsigned int,WPARAM,LPARAM) override {++windowCalls;return false;}
    bool sdlEventFilter(SDL_Event* event) override {
        if (event->type!=SDL_USEREVENT) return false;
        ++calls;
        if (recurse && event->user.code==1) {
            SDL_Event nested{};nested.type=SDL_USEREVENT;nested.user.code=2;
            if (SDL_PushEvent(&nested)!=1) std::abort();
        }
        if (block) {
            std::unique_lock lock(mutex);
            entered=true;condition.notify_all();
            condition.wait(lock,[&]{return released;});
        }
        return consume;
    }
};
int push(int code=0) {SDL_Event event{};event.type=SDL_USEREVENT;event.user.code=code;return SDL_PushEvent(&event);}
void attach(RT64::ApplicationWindow& window,Listener& listener) {
    window.listener=&listener;
    // The production installation method only tests this pointer for null.
    // No SDL_Window or video subsystem is created by this fixture.
    window.sdlWindow=reinterpret_cast<SDL_Window*>(uintptr_t(1));
    window.sdlCheckFilterInstallation();
}
bool current(SDL_EventFilter expected,void* userdata) {
    SDL_EventFilter actual=nullptr;void* actualData=nullptr;
    SDL_GetEventFilter(&actual,&actualData);
    return actual==expected && actualData==userdata;
}
void owned_filter() {
    Prior prior;SDL_SetEventFilter(prior_filter,&prior);
    Listener listener;RT64::ApplicationWindow window;attach(window,listener);
    check(current(RT64::ApplicationWindow::sdlEventFilter,&window),"Actual installation did not acquire the SDL filter");
    check(push()==1 && listener.calls==1 && prior.calls==1,"Listener did not chain the previous SDL filter");
    check(push(42)==0 && listener.calls==2 && prior.calls==2,"Previous filter's rejection result was lost");
    listener.consume=true;
    check(push()==0 && listener.calls==3 && prior.calls==2,"Consumed event was forwarded to the previous filter");
    listener.consume=false;listener.recurse=true;
    check(push(1)==1 && listener.calls==5 && prior.calls==4,"Same-thread recursive SDL dispatch failed");
    window.stopEventFilters();
    check(current(prior_filter,&prior),"Stopping the owned filter did not restore its predecessor and userdata");
    const auto calls=listener.calls.load();
    window.listener=nullptr;
    check(push()==1 && listener.calls==calls,"Restored SDL filter accessed the stopped listener");
    SDL_Event late{};late.type=SDL_USEREVENT;
    check(RT64::ApplicationWindow::sdlEventFilter(&window,&late)==1 && listener.calls==calls,
        "Late captured callback accessed the released listener");
    window.windowMessage(WM_APP,0,0);
    check(listener.windowCalls==0,"Late native window message accessed the released listener");
    window.sdlCheckFilterInstallation();window.stopEventFilters();
    check(current(prior_filter,&prior),"Stopped object reinstalled itself or altered the restored registration");
    SDL_SetEventFilter(nullptr,nullptr);SDL_FlushEvents(SDL_FIRSTEVENT,SDL_LASTEVENT);
}
void changed_owner() {
    for (bool sameFunction:{false,true}) {
        Prior prior;SDL_SetEventFilter(prior_filter,&prior);
        Listener listener,otherListener;RT64::ApplicationWindow window,other;
        attach(window,listener);other.listener=&otherListener;
        const auto callback=sameFunction?RT64::ApplicationWindow::sdlEventFilter:other_filter;
        SDL_SetEventFilter(callback,&other);
        window.stopEventFilters();
        check(current(callback,&other),"Stopping RT64 replaced another owner's SDL registration");
        check(!window.sdlEventFilterInstalled,"Stopped filter retained its installed flag");
        SDL_SetEventFilter(nullptr,nullptr);
    }
    Listener listener;RT64::ApplicationWindow window;attach(window,listener);
    window.stopEventFilters();
    check(current(nullptr,nullptr),"An absent predecessor was not restored to no filter");
}
void in_flight() {
    Prior prior;SDL_SetEventFilter(prior_filter,&prior);
    Listener listener;listener.block=true;RT64::ApplicationWindow window;attach(window,listener);
    std::thread dispatch([&]{if(push()!=1) std::abort();});
    {
        std::unique_lock lock(listener.mutex);
        check(listener.condition.wait_for(lock,2s,[&]{return listener.entered;}),"Synthetic listener did not start");
    }
    std::mutex stoppedMutex;std::condition_variable stoppedCondition;
    bool starting=false,stopped=false;
    std::thread teardown([&] {
        {std::lock_guard lock(stoppedMutex);starting=true;}stoppedCondition.notify_all();
        window.stopEventFilters();
        {std::lock_guard lock(stoppedMutex);stopped=true;}stoppedCondition.notify_all();
    });
    {
        std::unique_lock lock(stoppedMutex);
        check(stoppedCondition.wait_for(lock,2s,[&]{return starting;}),"Teardown worker did not start");
        check(!stoppedCondition.wait_for(lock,50ms,[&]{return stopped;}),
            "Filter shutdown returned while the listener still owned renderer state");
    }
    {std::lock_guard lock(listener.mutex);listener.released=true;}listener.condition.notify_all();
    {
        std::unique_lock lock(stoppedMutex);
        check(stoppedCondition.wait_for(lock,2s,[&]{return stopped;}),"Filter shutdown deadlocked behind SDL dispatch");
    }
    dispatch.join();teardown.join();
    check(listener.calls==1 && prior.calls==1,"In-flight callback failed to complete normal prior-filter chaining");
    check(current(prior_filter,&prior),"Concurrent shutdown failed to restore the prior filter");
    window.listener=nullptr;
    check(push()==1 && listener.calls==1,"Post-shutdown event touched released renderer state");
    SDL_SetEventFilter(nullptr,nullptr);SDL_FlushEvents(SDL_FIRSTEVENT,SDL_LASTEVENT);
}
}
int main() {
    SDL_SetMainReady();
    check(SDL_Init(SDL_INIT_EVENTS)==0,"SDL event-only initialization failed");
    owned_filter();changed_owner();in_flight();
    check(SDL_WasInit(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER)==0,
        "Offline fixture initialized video or physical controller input");
    SDL_Quit();
    std::printf("Passed %u actual RT64/SDL filter shutdown assertions; no window or input devices opened.\n",assertions);
}
