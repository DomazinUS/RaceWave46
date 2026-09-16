#include "wr64_achievements_ui.hpp"

#ifdef WR64_ENABLE_FRONTEND
#include "wr64_achievements.hpp"
#include "wr64_achievement_badges.hpp"
#include "wr64_badge_rounding.hpp"
#include "stb/stb_image.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <deque>
#include <limits>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "recompui/recompui.h"
#include "recompui/config.h"
#include "elements/ui_config_page.h"
#include "elements/ui_container.h"
#include "elements/ui_image.h"
#include "elements/ui_label.h"
#include "elements/ui_scroll_container.h"
#include "elements/ui_text_input.h"
#include "elements/ui_toggle.h"

namespace wr64::achievements_ui {
namespace {
using namespace recompui;
using Clock = std::chrono::steady_clock;
using Snapshot = achievements::Snapshot;
using Achievement = achievements::Achievement;
constexpr Color menuPurple{101, 96, 172, 255}; // Native modal header palette.
constexpr Color deepPurple{66, 60, 123, 255};
constexpr Color palePurple{246, 244, 252, 255};

// Keep the small public image payloads across full UI recreation. API switches
// already preserve the renderer's virtual image map and need no re-upload.
std::unordered_map<std::string, std::vector<char>> badgeImages;
struct RoundedBadgeImage {
    std::vector<char> pixels;
    uint32_t width, height;
};
std::unordered_map<std::string, RoundedBadgeImage> roundedBadgeImages;
std::unordered_set<std::string> failedRoundedBadges;
uint64_t badgeImageRevision = 0;
bool uploadBadgeImages = false;

void upload_known_badges() {
    if (!uploadBadgeImages) return;
    for (const auto& [source, bytes] : badgeImages) queue_image_from_bytes_file(source, bytes);
    for (const auto& [source, image] : roundedBadgeImages)
        queue_image_from_bytes_rgba32(source, image.pixels, image.width, image.height);
    uploadBadgeImages = false;
}

std::string rounded_badge_source(const std::string& source) {
    const auto roundedSource = source + "-rounded";
    if (roundedBadgeImages.contains(roundedSource)) return roundedSource;
    if (failedRoundedBadges.contains(source)) return {};
    const auto original = badgeImages.find(source);
    if (original == badgeImages.end()) return {};
    const auto* bytes = reinterpret_cast<const stbi_uc*>(original->second.data());
    const int count = static_cast<int>(original->second.size());
    int width = 0, height = 0, channels = 0;
    if (!stbi_info_from_memory(bytes, count, &width, &height, &channels) ||
        width <= 0 || height <= 0 || width > 512 || height > 512) {
        failedRoundedBadges.insert(source);
        return {};
    }
    std::unique_ptr<stbi_uc, decltype(&stbi_image_free)> decoded(
        stbi_load_from_memory(bytes, count, &width, &height, &channels, 4), stbi_image_free);
    if (!decoded) {
        failedRoundedBadges.insert(source);
        return {};
    }
    const auto* begin = reinterpret_cast<const char*>(decoded.get());
    RoundedBadgeImage image{{begin, begin + size_t(width) * height * 4}, uint32_t(width), uint32_t(height)};
    // Convert once per public badge variant. Original PNG/cache/list images
    // remain intact; the popup uses an alpha mask that also survives fading.
    if (!achievement_badges::round_badge_pixels(image.pixels, image.width, image.height)) {
        failedRoundedBadges.insert(source);
        return {};
    }
    const auto [entry, added] = roundedBadgeImages.emplace(roundedSource, std::move(image));
    queue_image_from_bytes_rgba32(entry->first, entry->second.pixels, entry->second.width, entry->second.height);
    return entry->first;
}

float ease(float value) {
    value = std::clamp(value, 0.0f, 1.0f);
    return value * value * (3.0f - 2.0f * value);
}
Color blend(Color first, Color second, float amount) {
    auto channel = [amount](uint8_t a, uint8_t b) { return uint8_t(a + (float(b) - a) * amount + 0.5f); };
    return {channel(first.r, second.r), channel(first.g, second.g), channel(first.b, second.b), channel(first.a, second.a)};
}
void queue_preview(const achievements::Notification& notice);

std::string unlock_date(int64_t epoch) {
    if (epoch <= 0) return {};
    const auto timestamp = static_cast<std::time_t>(epoch);
    std::tm local{};
#ifdef _WIN32
    if (localtime_s(&local, &timestamp) != 0) return {};
#else
    if (localtime_r(&timestamp, &local) == nullptr) return {};
#endif
    char value[48]{};
    if (std::strftime(value, sizeof(value), "%d %b %Y, %H:%M", &local) == 0) return {};
    return value;
}

bool has_rarity(float value) { return std::isfinite(value) && value >= 0.0f && value <= 100.0f; }

std::string rarity_text(float value) {
    char percent[24]{};
    std::snprintf(percent, sizeof(percent), "%.1f%%", double(value));
    return std::string(percent) + " of players unlocked";
}

// A native tab callback already owns its context; the frame callback does not.
// Restore whichever context the caller had rather than nesting context locks.
class ContextScope {
    ContextId context;
    ContextId previous;
public:
    explicit ContextScope(ContextId selected) : context(selected), previous(try_close_current_context()) { context.open(); }
    ~ContextScope() { context.close(); if (previous != ContextId::null()) previous.open(); }
    ContextScope(const ContextScope&) = delete;
    ContextScope& operator=(const ContextScope&) = delete;
};

Label* text(ContextId context, Element* parent, const std::string& value, float size = 20.0f) {
    auto* label = context.create_element<Label>(parent, value, LabelStyle::Small);
    label->set_color(theme::color::Text);
    // Native dp values scale with the frontend. Match its normal settings text
    // at 720p, while keeping the heading/body hierarchy at larger resolutions.
    size *= 1.5f;
    label->set_font_size(size);
    label->set_line_height(size * 1.3f);
    label->set_letter_spacing(0);
    label->set_white_space(WhiteSpace::Preline);
    label->set_flex_shrink(0);
    return label;
}

class BadgeView final : public Element {
    Image *lockedImage, *colorImage;
    Label* fallback;
    std::string badge, boundLocked, boundColor;
    bool unlocked = false, animate = false;
    const bool rounded;
    Clock::time_point assignedAt{}, revealAt{};
    float lastReveal = -1, lastParentOpacity = -1;
protected:
    std::string_view get_type_name() override { return "Wr64AchievementBadge"; }
public:
    BadgeView(ResourceId rid, Element* parent, float size, bool roundImage = false) : Element(rid, parent), rounded(roundImage) {
        auto context = get_current_context();
        set_position(Position::Relative);
        set_width(size); set_height(size); set_flex_shrink(0);
        set_display(Display::Flex);
        set_align_items(AlignItems::Center); set_justify_content(JustifyContent::Center);
        set_background_color(deepPurple);
        set_border_radius(12); set_border_width(2); set_border_color(menuPurple);
        set_overflow(Overflow::Hidden);
        set_focusable(false); set_tab_index_none(); set_pointer_events(PointerEvents::None);
        fallback = text(context, this, "RA", 21);
        fallback->set_color(theme::color::White);
        fallback->set_font_weight(700);
        lockedImage = context.create_element<Image>(this, "");
        colorImage = context.create_element<Image>(this, "");
        for (auto* image : {lockedImage, colorImage}) {
            image->set_position(Position::Absolute); image->set_left(0); image->set_top(0);
            image->set_width(100, Unit::Percent); image->set_height(100, Unit::Percent);
            image->set_pointer_events(PointerEvents::None); image->set_display(Display::None);
        }
    }
    void restart_reveal(Clock::time_point now) {
        assignedAt = now; revealAt = {}; lastReveal = -1;
    }
    void assign(const std::string& name, bool isUnlocked, bool reveal, Clock::time_point now, float parentOpacity = 1.0f) {
        if (badge == name && unlocked == isUnlocked && animate == reveal && !reveal) return;
        badge = name; unlocked = isUnlocked; animate = reveal;
        restart_reveal(now);
        boundLocked.clear(); boundColor.clear();
        lockedImage->set_display(Display::None); colorImage->set_display(Display::None);
        lockedImage->set_src(""); colorImage->set_src("");
        fallback->set_display(Display::Block);
        refresh(now, parentOpacity);
    }
    float refresh(Clock::time_point now, float parentOpacity = 1.0f) {
        upload_known_badges();
        auto bind_ready = [&](Image* image, bool locked, std::string& bound) {
            auto source = achievement_badges::source_name(badge, locked);
            if (source.empty() || !badgeImages.contains(source)) return false;
            if (rounded) {
                source = rounded_badge_source(source);
                if (source.empty()) return false;
            }
            if (bound != source) {
                // Assign only after upload is queued. Loading a virtual source
                // too early can permanently cache a transparent placeholder.
                image->set_src(source); image->set_display(Display::Block); bound = source;
                lastReveal = -1;
            }
            return true;
        };
        const bool grayReady = bind_ready(lockedImage, true, boundLocked);
        const bool colorReady = unlocked && bind_ready(colorImage, false, boundColor);
        float revealed = colorReady ? 1.0f : 0.0f;
        if (animate && colorReady) {
            if (revealAt == Clock::time_point{} && (grayReady || now - assignedAt >= std::chrono::milliseconds(450)))
                revealAt = now + std::chrono::milliseconds(grayReady ? 180 : 0);
            revealed = revealAt == Clock::time_point{} ? 0.0f :
                ease(std::chrono::duration<float>(now - revealAt).count() / 0.7f);
        }
        if (revealed != lastReveal || parentOpacity != lastParentOpacity) {
            // RmlUi inherits opacity; explicit child values replace the parent
            // fade instead of multiplying it as browser compositing would.
            lockedImage->set_opacity((grayReady ? 1.0f - revealed : 0.0f) * parentOpacity);
            colorImage->set_opacity(revealed * parentOpacity);
            fallback->set_opacity((grayReady ? 0.0f : 1.0f - revealed) * parentOpacity);
            set_border_color(blend(menuPurple, theme::get_theme_color(theme::color::Border), revealed));
            lastReveal = revealed;
            lastParentOpacity = parentOpacity;
        }
        return revealed;
    }
};

class AchievementCard final : public Element {
    Label *title, *description, *status, *rarityLabel;
    Element *rarityGroup, *rarityFill;
    BadgeView* badge;
    Style focused;
    Achievement last{};
    bool populated = false;
    unsigned int deferredScroll = 0;
protected:
    void process_event(const Event& event) override {
        if (event.type == EventType::Focus) {
            const bool active = std::get<EventFocus>(event.variant).active;
            set_style_enabled(focus_state, active);
            if (active) scroll_into_view();
        } else if (event.type == EventType::Update && deferredScroll != 0) {
            if (--deferredScroll != 0) queue_update();
            else if (get_current_context().get_focused_element() == this) scroll_into_view();
        }
    }
    std::string_view get_type_name() override { return "Wr64AchievementCard"; }
public:
    AchievementCard(ResourceId rid, Element* parent) : Element(rid, parent, Events(EventType::Focus, EventType::Update)) {
        auto context = get_current_context();
        set_display(Display::Flex);
        set_position(Position::Relative);
        set_flex_direction(FlexDirection::Row);
        set_align_items(AlignItems::Center);
        set_flex_shrink(0);
        set_gap(20);
        set_padding(18);
        set_margin_bottom(10);
        set_background_color(theme::color::ModalOverlay);
        set_border_width(2);
        set_border_radius(14);
        set_border_color(theme::color::BorderSoft);
        set_border_left_width(5);
        set_border_left_color(menuPurple);
        enable_focus();
        focused.set_border_color(theme::color::Secondary);
        add_style(&focused, focus_state);
        auto* content = context.create_element<Container>(this, FlexDirection::Column, JustifyContent::FlexStart);
        content->set_flex(1, 1, 0); content->set_min_width(0); content->set_gap(7);
        title = text(context, content, "", 22);
        title->set_font_weight(700);
        title->set_color(deepPurple);
        description = text(context, content, "", 18);
        status = text(context, content, "", 17);
        rarityGroup = context.create_element<Container>(content, FlexDirection::Column, JustifyContent::FlexStart);
        rarityGroup->set_gap(5);
        rarityGroup->set_display(Display::None);
        rarityLabel = text(context, rarityGroup, "", 16);
        rarityLabel->set_color(theme::color::TextDim);
        auto* rarityTrack = context.create_element<Container>(rarityGroup, FlexDirection::Row, JustifyContent::FlexStart);
        rarityTrack->set_height(7); rarityTrack->set_flex_shrink(0);
        rarityTrack->set_border_radius(4); rarityTrack->set_overflow(Overflow::Hidden);
        rarityTrack->set_background_color(Color{222, 218, 241, 255});
        rarityFill = context.create_element<Container>(rarityTrack, FlexDirection::Row, JustifyContent::FlexStart);
        rarityFill->set_height(100, Unit::Percent); rarityFill->set_width(0, Unit::Percent);
        rarityFill->set_flex_shrink(0); rarityFill->set_background_color(menuPurple);
        badge = context.create_element<BadgeView>(this, 96.0f);
    }
    void refresh(const Achievement& achievement) {
        if (!populated) set_debug_id("wr64-achievement-" + std::to_string(achievement.id));
        if (!populated || achievement.title != last.title || achievement.points != last.points)
            title->set_text(achievement.title + "  ·  " + std::to_string(achievement.points) + " points");
        if (!populated || achievement.description != last.description)
            description->set_text(achievement.description);
        if (!populated || achievement.unlocked != last.unlocked || achievement.progress != last.progress ||
            achievement.unlock_time != last.unlock_time) {
            const auto date = achievement.unlocked ? unlock_date(achievement.unlock_time) : std::string{};
            status->set_text(achievement.unlocked ? (date.empty() ? "Unlocked" : "Unlocked " + date) :
                achievement.progress.empty() ? "Locked" : "Progress: " + achievement.progress);
            status->set_color(achievement.unlocked ? theme::color::SuccessD : theme::color::TextDim);
            set_border_left_color(achievement.unlocked ? theme::get_theme_color(theme::color::Border) : menuPurple);
            set_background_color(achievement.unlocked ? Color{238, 250, 247, 255} : Color{252, 253, 252, 255});
        }
        if (!populated || achievement.rarity != last.rarity) {
            const bool available = has_rarity(achievement.rarity);
            rarityGroup->set_display(available ? Display::Flex : Display::None);
            if (available) {
                rarityLabel->set_text(rarity_text(achievement.rarity));
                rarityFill->set_width(achievement.rarity, Unit::Percent);
            }
        }
        badge->assign(achievement.badge_name, achievement.unlocked, false, Clock::now());
        last = achievement;
        populated = true;
    }
    void refresh_badge(Clock::time_point now) { badge->refresh(now); }
    void restore_focus_after_reorder() {
        focus();
        // Text assignments and flex layout settle after native UI updates.
        // Scroll the same card once that layout is available, unless the user
        // has already moved focus elsewhere.
        deferredScroll = 2;
        queue_update();
    }
};

class AchievementsPage;
AchievementsPage* activePage = nullptr;

class AchievementsPage final : public ConfigPage {
    ContextId context;
    TextInput *username, *password;
    Toggle* remember;
    Button *signIn, *signOut, *preview, *refreshCatalog;
    achievements::Notification previewNotice;
    Label *account, *status, *summary, *catalogStatus, *empty;
    Element *loginForm, *list;
    std::vector<AchievementCard*> cards;
    std::vector<uint32_t> cardIds;
    uint64_t revision = std::numeric_limits<uint64_t>::max();
    uint64_t generation = std::numeric_limits<uint64_t>::max();
    Element* lastAccountFocus = nullptr;
protected:
    std::string_view get_type_name() override { return "Wr64AchievementsPage"; }
public:
    AchievementsPage(ResourceId rid, Element* parent) : ConfigPage(rid, parent), context(get_current_context()) {
        set_debug_id("wr64-achievements-page");
        set_color(theme::color::Text);
        set_min_height(0);
        set_overflow(Overflow::Hidden);
        set_as_navigation_container(NavigationType::Vertical);
        get_body()->set_debug_id("wr64-achievements-columns");
        get_body()->set_min_height(0);
        get_body()->set_height(0);
        get_body()->set_flex(1, 1, 0);
        get_body()->set_overflow(Overflow::Hidden);
        get_body()->set_as_navigation_container(NavigationType::Horizontal);
        auto* left = get_body()->get_left();
        auto* right = get_body()->get_right();
        left->set_debug_id("wr64-achievements-account-pane");
        left->set_position(Position::Relative);
        left->set_flex_basis(34, Unit::Percent);
        left->set_min_width(245);
        left->set_min_height(0);
        left->set_display(Display::Flex);
        left->set_flex_direction(FlexDirection::Column);
        left->set_gap(14);
        left->set_overflow_x(Overflow::Hidden);
        left->set_overflow_y(Overflow::Auto);
        left->set_as_navigation_container(NavigationType::Vertical);
        left->set_background_color(palePurple);
        right->set_debug_id("wr64-achievements-catalog-pane");
        right->set_position(Position::Relative);
        right->set_flex_basis(66, Unit::Percent);
        right->set_min_width(0);
        right->set_min_height(0);
        right->set_display(Display::Flex);
        right->set_flex_direction(FlexDirection::Column);
        right->set_gap(12);
        right->set_overflow(Overflow::Hidden);

        auto* accountHeader = context.create_element<Container>(left, FlexDirection::Column, JustifyContent::FlexStart);
        accountHeader->set_flex_shrink(0);
        accountHeader->set_background_color(menuPurple); accountHeader->set_padding(18);
        accountHeader->set_border_radius(12); accountHeader->set_border_bottom_width(4);
        accountHeader->set_border_bottom_color(theme::color::Secondary); accountHeader->set_gap(5);
        auto* heading = text(context, accountHeader, "RetroAchievements", 26);
        heading->set_font_weight(700);
        heading->set_color(theme::color::White);
        auto* subtitle = text(context, accountHeader, "Wave Race 64", 17);
        subtitle->set_color(Color{237, 236, 252, 255});
        account = text(context, left, "Sign in to your account.");
        loginForm = context.create_element<Container>(left, FlexDirection::Column, JustifyContent::FlexStart);
        loginForm->set_gap(8);
        loginForm->set_flex_shrink(0);
        text(context, loginForm, "Username", 18);
        username = context.create_element<TextInput>(loginForm);
        username->set_debug_id("wr64-achievements-username");
        username->set_width(100, Unit::Percent);
        username->set_font_size(30);
        text(context, loginForm, "Password", 18);
        password = context.create_element<TextInput>(loginForm, false);
        password->set_debug_id("wr64-achievements-password");
        password->set_width(100, Unit::Percent);
        password->set_font_size(30);
        auto* rememberRow = context.create_element<Container>(loginForm, FlexDirection::Row, JustifyContent::FlexStart);
        rememberRow->set_align_items(AlignItems::Center);
        rememberRow->set_gap(10);
        remember = context.create_element<Toggle>(rememberRow, ToggleSize::Medium);
        remember->set_debug_id("wr64-achievements-remember");
        remember->set_checked(false);
        text(context, rememberRow, "Remember me", 18);
        signIn = context.create_element<Button>(loginForm, "Sign in", ButtonStyle::Primary, ButtonSize::Large);
        signIn->set_debug_id("wr64-achievements-sign-in");
        signIn->set_margin_top(6);
        signIn->add_pressed_callback([this] {
            if (username->get_text().empty() || password->get_text().empty()) {
                status->set_text("Enter your username and password.");
                return;
            }
            // Transfer only on explicit Sign in. Never persist the password as
            // a frontend option or include it in diagnostics/captured callbacks.
            std::string user = username->get_text();
            std::string secret = password->get_text();
            password->set_text("");
            signIn->set_enabled(false);
            status->set_text("Signing in…");
            achievements::request_login(std::move(user), std::move(secret), remember->is_checked());
        });
        signOut = context.create_element<Button>(left, "Sign out", ButtonStyle::Tertiary, ButtonSize::Large);
        signOut->set_debug_id("wr64-achievements-sign-out");
        signOut->add_pressed_callback([this] {
            clear_password();
            signOut->set_enabled(false);
            achievements::request_logout();
        });
        status = text(context, left, "", 18);
        status->set_debug_id("wr64-achievements-status");
        status->set_color(theme::color::TextDim);
        auto* mode = text(context, left, "Softcore achievements", 17);
        mode->set_color(theme::color::TextDim);
        preview = context.create_element<Button>(left, "Preview notification", ButtonStyle::Tertiary, ButtonSize::Large);
        preview->set_debug_id("wr64-achievements-preview");
        // Retain the preview for development, outside normal layout/navigation.
        preview->set_display(Display::None);
        preview->set_enabled(false);
        preview->add_pressed_callback([this] { queue_preview(previewNotice); });
        refreshCatalog = context.create_element<Button>(left, "Refresh achievements", ButtonStyle::Tertiary, ButtonSize::Large);
        refreshCatalog->set_debug_id("wr64-achievements-refresh");
        refreshCatalog->set_enabled(false);
        refreshCatalog->add_pressed_callback([] { achievements::request_catalog_refresh(); });
        auto* collectionHeader = context.create_element<Container>(right, FlexDirection::Column, JustifyContent::FlexStart);
        collectionHeader->set_debug_id("wr64-achievements-catalog-header");
        collectionHeader->set_flex_shrink(0);
        collectionHeader->set_background_color(menuPurple); collectionHeader->set_padding(18);
        collectionHeader->set_border_radius(12); collectionHeader->set_border_bottom_width(4);
        collectionHeader->set_border_bottom_color(theme::color::Border);
        summary = text(context, collectionHeader, "Wave Race 64", 23);
        summary->set_debug_id("wr64-achievements-summary");
        summary->set_font_weight(700);
        summary->set_color(theme::color::White);
        catalogStatus = text(context, right, "", 17);
        catalogStatus->set_debug_id("wr64-achievements-catalog-status");
        catalogStatus->set_color(theme::color::TextDim);
        catalogStatus->set_display(Display::None);
        empty = text(context, right, "Sign in to see achievements and your progress.", 19);
        empty->set_color(theme::color::TextDim);
        auto* scroll = context.create_element<ScrollContainer>(right, ScrollDirection::Vertical);
        scroll->set_debug_id("wr64-achievements-list-scroll");
        // RmlUi walks offset parents when building the clip region. A static
        // scrollport is skipped, letting cards paint over the panel header.
        scroll->set_position(Position::Relative);
        scroll->set_overflow_x(Overflow::Hidden);
        scroll->set_min_width(0);
        scroll->set_min_height(0);
        scroll->set_height(0);
        scroll->set_flex(1, 1, 0);
        scroll->set_as_navigation_container(NavigationType::Vertical);
        list = context.create_element<Container>(scroll, FlexDirection::Column, JustifyContent::FlexStart);
        list->set_debug_id("wr64-achievements-list");
        list->set_width(100, Unit::Percent);
        list->set_flex_shrink(0);
        refresh(achievements::snapshot());
        activePage = this;
    }
    ~AchievementsPage() override { if (activePage == this) activePage = nullptr; }
    ContextId ui_context() const { return context; }
    void clear_password() { password->set_text(""); }
    void refresh_badges(Clock::time_point now) { for (auto* card : cards) card->refresh_badge(now); }
    void refresh(const Snapshot& snapshot) {
        // Native buttons and text fields do not scroll their parent on focus.
        // Follow controller focus in the account column only when it changes;
        // mouse wheel scrolling must not continually snap back to that field.
        auto* focusedElement = context.get_focused_element();
        if (focusedElement != lastAccountFocus) {
            lastAccountFocus = focusedElement;
            for (auto* parent = focusedElement; parent; parent = parent->get_parent()) {
                if (parent == get_body()->get_left()) { focusedElement->scroll_into_view(); break; }
            }
        }
        if (revision == snapshot.revision && generation == snapshot.account_generation) return;
        const bool first = revision == std::numeric_limits<uint64_t>::max();
        if (generation != snapshot.account_generation) {
            clear_password();
            if (first || snapshot.logged_in) username->set_text(snapshot.username);
        }
        revision = snapshot.revision;
        generation = snapshot.account_generation;
        loginForm->set_display(snapshot.logged_in ? Display::None : Display::Flex);
        signOut->set_display(snapshot.logged_in ? Display::Flex : Display::None);
        username->set_enabled(!snapshot.busy);
        password->set_enabled(!snapshot.busy);
        remember->set_enabled(!snapshot.busy);
        signIn->set_enabled(!snapshot.busy);
        signOut->set_enabled(!snapshot.busy);
        const bool hasCatalog = snapshot.logged_in && (snapshot.catalog_loaded || !snapshot.achievements.empty());
        const bool canPreview = snapshot.logged_in && !snapshot.achievements.empty();
        preview->set_enabled(canPreview);
        refreshCatalog->set_display(snapshot.logged_in ? Display::Flex : Display::None);
        refreshCatalog->set_enabled(snapshot.logged_in && !snapshot.catalog_busy && !snapshot.busy);
        if (canPreview) {
            const auto& achievement = snapshot.achievements.front();
            previewNotice = {snapshot.account_generation,
                "Notification preview · " + std::to_string(achievement.points) + " points", achievement.title, achievement.badge_name};
        } else previewNotice = {};
        account->set_text(snapshot.logged_in ? "Signed in as " + snapshot.username : "Sign in to your account.");
        status->set_text(snapshot.status);
        summary->set_text(hasCatalog ?
            std::to_string(snapshot.unlocked) + " / " + std::to_string(snapshot.total) +
                " unlocked\n" + std::to_string(snapshot.points) + " / " + std::to_string(snapshot.total_points) +
                " points earned" : "Wave Race 64");
        const auto catalogMessage = !snapshot.logged_in ? std::string{} :
            !snapshot.catalog_status.empty() ? snapshot.catalog_status :
            snapshot.catalog_busy ? std::string("Loading achievements…") : std::string{};
        catalogStatus->set_display(catalogMessage.empty() ? Display::None : Display::Block);
        catalogStatus->set_text(catalogMessage);
        empty->set_display(snapshot.achievements.empty() ? Display::Block : Display::None);
        empty->set_text(!snapshot.logged_in ? "Sign in to see achievements and your progress." :
            snapshot.catalog_busy ? "Your achievement list will appear here." : snapshot.catalog_loaded ?
                "No achievements available." : "Use Refresh achievements to try loading the list again.");
        // Keep the service's catalog order within each group, so repeated
        // progress refreshes do not shuffle cards or disturb list navigation.
        std::vector<const Achievement*> ordered;
        ordered.reserve(snapshot.achievements.size());
        for (const auto& achievement : snapshot.achievements) ordered.push_back(&achievement);
        std::stable_partition(ordered.begin(), ordered.end(), [](const Achievement* achievement) { return achievement->unlocked; });
        bool reordered = cards.size() != ordered.size();
        if (!reordered) for (size_t i = 0; i < cards.size(); ++i)
            if (cardIds[i] != ordered[i]->id) { reordered = true; break; }
        AchievementCard* retainedFocus = nullptr;
        if (reordered) {
            std::unordered_map<uint32_t, AchievementCard*> existing;
            for (size_t i = 0; i < cards.size(); ++i) existing.emplace(cardIds[i], cards[i]);
            std::vector<AchievementCard*> updated;
            std::vector<uint32_t> updatedIds;
            updated.reserve(ordered.size()); updatedIds.reserve(ordered.size());
            for (const auto* achievement : ordered) {
                auto found = existing.find(achievement->id);
                auto* card = found == existing.end() ? context.create_element<AchievementCard>(list) : found->second;
                if (found != existing.end()) existing.erase(found);
                if (card == focusedElement) retainedFocus = card;
                updated.push_back(card); updatedIds.push_back(achievement->id);
            }
            for (const auto& [id, card] : existing) list->remove_child(card);
            // Reparenting to the same list appends the existing native element,
            // preserving card identity, badge resources and focused content.
            for (auto* card : updated) card->set_parent(list);
            cards = std::move(updated); cardIds = std::move(updatedIds);
        }
        for (size_t i = 0; i < cards.size(); ++i) cards[i]->refresh(*ordered[i]);
        if (retainedFocus) retainedFocus->restore_focus_after_reorder();
    }
};

ContextId toastContext = ContextId::null();
Label *toastTitle = nullptr, *toastBody = nullptr;
Element* toastCard = nullptr;
BadgeView* toastBadge = nullptr;
std::deque<achievements::Notification> pending;
uint64_t accountGeneration = std::numeric_limits<uint64_t>::max();
Clock::time_point expires{}, nextPoll{}, toastStarted{};
bool toastActive = false, toastPrepared = false;
float lastToastOpacity = -1;

void queue_preview(const achievements::Notification& notice) {
    if (notice.title.empty() || notice.account_generation != accountGeneration) return;
    achievement_badges::request(notice.badge_name, true);
    pending.push_back(notice);
}

// Owned by the native context. Full UI shutdown invalidates our handles;
// graphics-API reconfiguration retains the context and its ordinary resources.
class ToastCard final : public Element {
protected:
    std::string_view get_type_name() override { return "Wr64AchievementToast"; }
public:
    ToastCard(ResourceId rid, Element* parent) : Element(rid, parent) {}
    ~ToastCard() override {
        toastContext = ContextId::null();
        toastTitle = toastBody = nullptr;
        toastCard = nullptr;
        toastBadge = nullptr;
        toastActive = toastPrepared = false;
        uploadBadgeImages = true;
    }
};

void hide_toast() {
    if (toastContext != ContextId::null() && is_context_shown(toastContext)) hide_context(toastContext);
    toastActive = toastPrepared = false;
}

void create_toast() {
    // Called only from update(), with no other native context open.
    toastContext = create_context();
    upload_known_badges();
    ContextScope scope(toastContext);
    toastContext.set_captures_input(false);
    toastContext.set_captures_mouse(false);
    auto* document = toastContext.get_root_element();
    // Native Show() otherwise focuses the document even without interactive
    // children. Keep an unlock notice from blurring a settings text field.
    document->set_focusable(false);
    document->set_tab_index_none();
    document->set_pointer_events(PointerEvents::None);
    document->set_background_color(Color{0, 0, 0, 0});
    auto* card = toastContext.create_element<ToastCard>(document);
    toastCard = card;
    card->set_focusable(false);
    card->set_tab_index_none();
    card->set_debug_id("wr64-achievements-toast");
    card->set_position(Position::Absolute);
    card->set_top(18);
    card->set_left(25, Unit::Percent);
    card->set_width(50, Unit::Percent);
    card->set_display(Display::Flex);
    card->set_opacity(0);
    card->set_flex_direction(FlexDirection::Column);
    card->set_background_color(theme::color::White);
    card->set_border_width(0);
    card->set_border_radius(16);
    card->set_overflow(Overflow::Hidden);
    card->set_pointer_events(PointerEvents::None);
    auto* headingBand = toastContext.create_element<Container>(card, FlexDirection::Row, JustifyContent::FlexStart);
    headingBand->set_background_color(menuPurple);
    // Overflow clips rectangularly here; match the borderless popup corners.
    headingBand->set_border_top_left_radius(16);
    headingBand->set_border_top_right_radius(16);
    headingBand->set_padding_left(22); headingBand->set_padding_right(22);
    headingBand->set_padding_top(10); headingBand->set_padding_bottom(10);
    auto* heading = text(toastContext, headingBand, "RetroAchievements", 16);
    heading->set_color(theme::color::White); heading->set_font_weight(700);
    auto* body = toastContext.create_element<Container>(card, FlexDirection::Row, JustifyContent::SpaceBetween);
    body->set_padding(22); body->set_gap(22); body->set_align_items(AlignItems::Center);
    auto* copy = toastContext.create_element<Container>(body, FlexDirection::Column, JustifyContent::Center);
    copy->set_flex(1, 1, 0); copy->set_min_width(0); copy->set_gap(7);
    toastTitle = text(toastContext, copy, "", 23);
    toastTitle->set_font_weight(700);
    toastTitle->set_color(deepPurple);
    toastBody = text(toastContext, copy, "", 19);
    toastBadge = toastContext.create_element<BadgeView>(body, 120.0f, true);
    toastBadge->set_border_width(0);
}
}

void register_tab() {
    config::create_tab("Achievements", "achievements",
        [](ContextId context, Element* parent) { context.create_element<AchievementsPage>(parent); },
        nullptr,
        [](TabCloseContext) {
            if (activePage) {
                ContextScope scope(activePage->ui_context());
                activePage->clear_password();
            }
        });
}

void update() {
    // Service callbacks only publish snapshots/events. All element access,
    // including the non-modal overlay, stays on the UI render thread.
    achievements::ui_tick();
    const auto now = Clock::now();
    // The hidden context also provides a lifetime sentinel: full UI shutdown
    // marks cached image bytes for re-upload; an API switch keeps them intact.
    if (toastContext == ContextId::null()) create_toast();
    upload_known_badges();
    const auto previousImageRevision = badgeImageRevision;
    for (auto& image : achievement_badges::drain_images()) {
        if (image.source.empty() || image.bytes.empty()) continue;
        const auto [entry, added] = badgeImages.emplace(std::move(image.source), std::move(image.bytes));
        if (added) {
            queue_image_from_bytes_file(entry->first, entry->second);
            ++badgeImageRevision;
        }
    }
    if (now >= nextPoll) {
        nextPoll = now + std::chrono::milliseconds(200);
        const auto state = achievements::snapshot();
        if (state.account_generation != accountGeneration) {
            accountGeneration = state.account_generation;
            pending.clear();
            hide_toast();
        }
        if (activePage) {
            ContextScope scope(activePage->ui_context());
            activePage->refresh(state);
        }
        for (const auto& achievement : state.achievements) {
            if (!badgeImages.contains(achievement_badges::source_name(achievement.badge_name, true)) ||
                !badgeImages.contains(achievement_badges::source_name(achievement.badge_name, false)))
                achievement_badges::request(achievement.badge_name);
        }
        for (auto& notice : achievements::drain_notifications())
            if (state.logged_in && notice.account_generation == accountGeneration) {
                achievement_badges::request(notice.badge_name, true);
                pending.push_back(std::move(notice));
            }
    }
    if (activePage && badgeImageRevision != previousImageRevision) {
        ContextScope scope(activePage->ui_context());
        activePage->refresh_badges(now);
    }
    // Prepare one fully transparent frame before starting the clock. Initial
    // layout/texture uploads must not consume the visible reveal animation.
    if (toastPrepared) {
        if (!is_context_shown(toastContext)) hide_toast();
        else {
            ContextScope scope(toastContext);
            toastBadge->restart_reveal(now);
            toastStarted = now;
            expires = now + std::chrono::seconds(5);
            toastPrepared = false;
            toastActive = true;
        }
    }
    if (toastActive && (now >= expires || !is_context_shown(toastContext))) hide_toast();
    if (!toastActive && !toastPrepared && !pending.empty() && !is_input_suspended()) {
        auto notice = std::move(pending.front());
        pending.pop_front();
        if (toastContext == ContextId::null()) create_toast();
        {
            ContextScope scope(toastContext);
            toastTitle->set_text(notice.title);
            toastBody->set_text(notice.body);
            toastBadge->assign(notice.badge_name, true, true, now, 0.0f);
            toastCard->set_opacity(0);
            toastContext.process_updates();
        }
        show_context(toastContext, "");
        lastToastOpacity = 0;
        toastPrepared = true;
    }
    if (toastActive) {
        ContextScope scope(toastContext);
        const auto age = std::chrono::duration<float>(now - toastStarted).count();
        const auto remaining = std::chrono::duration<float>(expires - now).count();
        const auto opacity = std::min(ease(age / 0.16f), ease(remaining / 0.25f));
        if (opacity != lastToastOpacity) { toastCard->set_opacity(opacity); lastToastOpacity = opacity; }
        toastBadge->refresh(now, opacity);
    }
}
}
#else
void wr64::achievements_ui::register_tab() {}
void wr64::achievements_ui::update() {}
#endif
