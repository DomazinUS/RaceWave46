// WR64 matrix-slot diagnostics distinguish stable object addresses from reused
// scratch slots. DrawData records both segmented and physical matrix addresses.
// An address is a useful identity only if unrelated objects do not share it.
//
// WR64_MATRIX_SLOTS aggregates every draw by segmented address, including draws
// outside the watch list, to reveal sharing. WR64_MATRIX_TRACK records watched
// frame/transform/texture rows so physical continuity can be checked over time.
// The watch list includes established families as controls; it is not a list of
// unresolved rendering defects. Both recorders are optional and disabled by default.
// Flush track batches and periodically rewrite summaries during the run so data
// does not depend on normal process shutdown.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// R9: the recorder shares the ring state test with the claim pass, so the
// two can never drift apart again - R8 proved what drift costs (the claim
// and the watch were both blind to Sunset Bay's rings, and the capture
// could not even SHOW the miss).
#include "rt64_wr64_stunt_ring_identity.h"

namespace RT64 {
    // ------------------------------------------------------------- watch list --
    //
    // Every texture the Composer has captured for an animal or a moving prop,
    // with the family it belongs to. The hash is the ONLY key here on purpose:
    // triangle counts move (the newspaper sheet was seen at 6, 12, 18 and 24 in
    // one session) and this is a recorder, not a fix - a texture wrongly
    // included costs one extra column of rows, whereas one wrongly excluded
    // costs a whole play session.
    struct Wr64MatrixWatch {
        uint64_t texture;
        const char *family;
    };

    inline const std::vector<Wr64MatrixWatch> &wr64MatrixWatchList() {
        static const std::vector<Wr64MatrixWatch> list = {
            // ---- Southern Island whale, group 1: opaque, palettised textures.
            // Other mode C8112078 / 0018ACFF. Eleven pieces, 27 triangles.
            { 0xC417848AC758985FULL, "whale_g1" },
            { 0x63C781AA25BE36A9ULL, "whale_g1" },
            { 0xA48B25B56BDC7F73ULL, "whale_g1" },
            { 0x567DFF81F4AA3880ULL, "whale_g1" },
            { 0x482331AC450564E2ULL, "whale_g1" },
            { 0xE68E048DEE5D10EAULL, "whale_g1" },
            { 0xD27BAEEF67D18D73ULL, "whale_g1" },
            { 0xFA988B67A76DE549ULL, "whale_g1" },
            { 0x881DD4775FBA91AAULL, "whale_g1" },
            { 0x941ACFE6EABED169ULL, "whale_g1" },
            { 0x9FC3A165B8D0F63EULL, "whale_g1" },

            // ---- Southern Island whale, group 2: alpha cutout, direct colour.
            // Other mode C8113078 / 00182CFF - the game's animal setting, the
            // same one the tropical fish, the dolphins and the birds all use.
            { 0x2B2B0452B5B6FA70ULL, "whale_g2" },
            { 0xF633FB1461BACE0EULL, "whale_g2" },
            { 0xA3B1F651ACE68FD6ULL, "whale_g2" },
            { 0xAE8AE5E6F2B06CE2ULL, "whale_g2" },
            { 0x577A3C810CB0AE45ULL, "whale_g2" },
            { 0xB878872207DB804CULL, "whale_g2" },

            // ---- Dolphins, Dolphin Park and Sunset Bay. THE PRIMARY TARGET.
            // Measured at 94.7% order-correct with members 853 units apart, so
            // rank naming was refused: a 5% mis-pair would slide an animal most
            // of a screen. Reachable without a championship, which is why the
            // first run of this trace is a Dolphin Park run.
            { 0x197A0A7C04303EE1ULL, "dolphin" },
            { 0x78B25A815B714850ULL, "dolphin" },
            { 0x9DA7414E1DCAEC6CULL, "dolphin" },
            { 0xF1A0EACF0258DBD7ULL, "dolphin" },
            { 0x7AC3BE72B5A94F0DULL, "dolphin" },
            { 0x2908030C8A159B72ULL, "dolphin" },

            // ---- Drake Lake fish. The worst measured case: 45.4% order
            // correct across twelve members. If address keying works anywhere it
            // has to work here to be worth having.
            { 0x2867951E0BDA7D0BULL, "drake_fish" },

            // Drake Lake ducks use all seven textures: Composer capture 4/frame 1931,
            // layers L78-L84. Six transforms each draw L78; a seventh draws the six detail
            // textures. The first-draw-only census sees just two of those textures, so its
            // rows cannot supply the complete watch list. Static scenery texture
            // C7E16FE8A5BC21ED is a separate object in segment-5 scratch storage.
            { 0xF80AED736EA5C5E3ULL, "drake_duck" },   // L78, 4 tri, 6 per duck
            { 0x87D653A4EFF244E5ULL, "drake_duck" },   // L79, 8 tri
            { 0x0802E965833AF77BULL, "drake_duck" },   // L80, 4 tri
            { 0xAF7F087C761F318FULL, "drake_duck" },   // L81, 6 tri
            { 0x8EB5DF4336C95518ULL, "drake_duck" },   // L82, 6 tri
            { 0xEEC5FF0C276EE611ULL, "drake_duck" },   // L83, 10 tri
            { 0xE3BF645F42572CB5ULL, "drake_duck" },   // L84, 4 tri

            // ---- THE ATTRACT-DEMO CRAFT. NOT the craft you race.
            //
            // Kept because they are a real object and cost only columns, but
            // RENAMED on 2026-08-03 after the first 2P capture proved they are
            // the intro demo's craft: they carry 18 transforms on frames 2-114
            // and only ONE of them appears during an actual race, where it sits
            // on a STATIC object. Selecting them from a census filtered on
            // '>=40 transforms' picked up the demo, which is also 'race-like'.
            //
            // ---- (original note) The residual 2P camera
            // drift: the craft has no identity, so when one player passes the
            // other all three of computeTransformMatch's terms go quiet at once
            // and a craft can pair with the OTHER player's previous transform.
            //
            // DERIVED FROM THE CENSUS, NOT THE COMPOSER, and that is defensible
            // here where it was not for the ducks. These eleven are on screen in
            // ALL 1,745 race frames of the 2026-08-02 Drake Lake capture, carry
            // 1 to 4 transforms each, and step a median 47-61 units per frame -
            // the player's own speed. The next candidate below them steps 6.46
            // (the lake fish) and the one below that 0.00 (scenery), so the
            // group separates cleanly rather than by a judgement call.
            //
            // The census's first-draw-wins blindness does not bite for a WATCH
            // LIST of transform owners: a texture that never owns a transform
            // cannot add one to name. It bit the ducks because it hid the shape
            // of the model, not because it hid a matrix.
            //
            // The last two step slightly slower than the rest, which is what an
            // articulated part does when its local motion partly cancels the
            // craft's translation. Expect the rider among them.
            { 0x0494B20750786E57ULL, "craft_demo" },  //  6 tri, 1 xf/frame
            { 0x17A6C757D907FAFDULL, "craft_demo" },  // 20 tri, 1
            { 0xC6EAAE59B6DF829AULL, "craft_demo" },  //  2 tri, 1
            { 0x78EA7153A204F008ULL, "craft_demo" },  //  2 tri, 1
            { 0xF9C78031B3FDF215ULL, "craft_demo" },  //  8 tri, 1
            { 0xC6A47A096C7A82AEULL, "craft_demo" },  //  8 tri, 2
            { 0xEBD5CD6223AD0434ULL, "craft_demo" },  //  9 tri, 1
            { 0x08B22C87B7DB402AULL, "craft_demo" },  // 10 tri, 2
            { 0x82AC62D48C170DBFULL, "craft_demo" },  //  3 tri, 2
            { 0xE7C1090E34E8E870ULL, "craft_demo" },  //  1,10 tri, 4  - slower
            { 0xED1713EFEF17564DULL, "craft_demo" },  //  5 tri, 2     - slower

            // ---- THE REAL IN-RACE WATERCRAFT. Twelve textures.
            //
            // Derived from the 2026-08-03 capture's ACTUAL RACE frames - after
            // frame 200, >=40 transforms - rather than from anything that could
            // be the intro. All twelve are present in all 942 of those frames,
            // carry 1.03 to 3.16 transforms each, and step a median 9.6 to 15.6
            // units per frame. The next texture below them steps 0.31, so the
            // group separates on a cliff rather than a judgement call.
            //
            // ★ THE CRAFT IS NOT THE DUCKS' CASE. Measured on the same frames:
            //       a craft's own parts sit   p50 21.47 units apart
            //       the craft moves           p50  7.89 units per frame
            // Motion is BELOW spacing, which is the condition under which
            // nearest-position matching WORKS. So whatever confuses the bottom
            // camera, it is not a craft being confused with its own parts - it
            // has to be one craft confused with the OTHER one. That needs the
            // two of them close together, which no capture has yet contained.
            { 0x91370C201DDF336BULL, "watercraft" },
            { 0x754CC6962AAB9B5CULL, "watercraft" },
            { 0x7BF86BB56745B0C2ULL, "watercraft" },
            { 0x386F8B786474587EULL, "watercraft" },
            { 0x7E84B0E5324E9CFCULL, "watercraft" },
            { 0xE86B137922686D6CULL, "watercraft" },
            { 0x5B7932613E72B339ULL, "watercraft" },
            { 0x5C54116D20943A73ULL, "watercraft" },
            { 0x35C3697149219CDCULL, "watercraft" },
            { 0x3C2B4CB9E24CB554ULL, "watercraft" },
            { 0xD71D47552615E2D6ULL, "watercraft" },
            { 0x421DD3BB2BC3A905ULL, "watercraft" },

            // Port Blue barrels provide a control for changing instance-count identity.
            { 0x3B0CDAC22E6D20D5ULL, "barrel" },

            // Course buoys: Composer captures 3/frame 3143 and 5/frame 6122 identify four
            // layers per color, with separate texture sets. Parts use 1, 1, 4, and 2 triangles.
            // The four L18/L19 textures were also found together in the 2026-07-16 dump.
            // Render state matches ducks, so texture identity is required to separate them.
            // Watch both colors to compare address continuity across all buoy instances.
            { 0xF12E5A7C9716DF55ULL, "buoy_yellow" },   // L9,  1 tri
            { 0xAC0C00790089DEB0ULL, "buoy_yellow" },   // L10, 1 tri
            { 0x1C107ECADB0C3559ULL, "buoy_yellow" },   // L18, 4 tri
            { 0xE5B734C89178B3F0ULL, "buoy_yellow" },   // L19, 2 tri

            { 0xC093005232F26F52ULL, "buoy_red" },

            // ---- Dolphin Park sun corona. A 28-triangle PERSPECTIVE glow
            // mesh at the sun's position (Composer capture 13 / frame 32598,
            // proj 2 call 251, combiner FC129825 FF33FFFF, other mode
            // 00504B50 00082CFF). NOT the protected sky fan - every field of
            // its render state differs from isWr64CourseSkyDraw's signature -
            // and NOT reachable by the celestial rect fix, which only walks
            // Rectangle projections. Watched here so one capture shows its
            // group flags, whether its transform or its vertices carry the
            // motion, and whether it steps at all.
            { 0xEEFCBAB804DF4B9EULL, "sun_corona" },      // L7,  1 tri
            { 0x6E4F42D43CE128EFULL, "buoy_red" },      // L8,  1 tri
            { 0xDD932255D7967796ULL, "buoy_red" },      // L18, 4 tri
            { 0x6CC118A4C1533415ULL, "buoy_red" },      // L19, 2 tri

            // ---- Tropical fish, Sunny Beach. CONTROL - fixed and validated.
            { 0x4C91465E6EF00146ULL, "trop_fish" },
            { 0x79BB32DB0213A7C9ULL, "trop_fish" },
            { 0x6333853F362F64B5ULL, "trop_fish" },

            // ---- Seagulls / Marine Fortress birds. CONTROL - fixed and
            // validated by eye ("look great and fluid").
            { 0xE0DE60C30E0CA4C1ULL, "seagull" },
            { 0x8730DC2C936F608AULL, "seagull" },
            { 0xA7A7757A4556102EULL, "seagull" },
            { 0x257AFC2EEA156C98ULL, "seagull" },
            { 0xACAC918D3A8DA899ULL, "seagull" },

            // ---- Port Blue helicopter. CONTROL - fixed and validated. Ten
            // pieces, the largest working family, so the strongest control.
            { 0x8679101BFE87295FULL, "helicopter" },
            { 0x5BA82B0E2FFF5B28ULL, "helicopter" },
            { 0x98491F2086F450A4ULL, "helicopter" },
            { 0x2E3AB02EC7746780ULL, "helicopter" },
            { 0x907BF66EE55AA996ULL, "helicopter" },
            { 0x846549D3ADF3C7C6ULL, "helicopter" },
            { 0xF2AF851DFF467FBFULL, "helicopter" },
            { 0x6BD1A280D751F5EFULL, "helicopter" },
            { 0x646F98E1B4D4CA58ULL, "helicopter" },
            { 0x9066CDBFFC1B1740ULL, "helicopter" },

            // ---- Port Blue newspaper sheet. CONTROL - fixed and validated.
            { 0x1F26C4530C35D5B7ULL, "newspaper" },

            // Area buoys have two billboard layers and reused scratch slots. Their
            // position-based IDs use family 0x57D; see rt64_wr64_area_buoy_identity.h.
            { 0xBE02175811C60321ULL, "area_buoy" },       // L5 part, 1 tri
            { 0x21AB19727CE2E9F6ULL, "area_buoy" },       // L6 part, 1 tri
            // Stunt Mode rings: 48-triangle torus, a red-tinted and a white
            // layer per ring, 4 rings in capture 8. MEASURED in MULTI-R1
            // (6,550 rows): same shuffling count-stack, same position-keyed
            // fix - rt64_wr64_stunt_ring_identity.h (matrix_id 0x57Exxxx).
            // The second hash NEVER records - it is the second TILE of the
            // same draw call, not a draw of its own (0 rows in 6,550) - and
            // stays here only so a draw that DID lead with it would be seen.
            { 0xA6589CB96E2D87C9ULL, "stunt_ring" },
            { 0xCE5020650E64CE30ULL, "stunt_ring" },
        };
        return list;
    }

    // Untextured wrong-way arrows and pause-menu cubes are identified by triangle
    // count, combiner, and other mode from Composer captures 2 and 9 (2026-08-04).
    // callDesc stores each command pair in the reverse order from Composer's display:
    // H is the second word and L is the first. Triangle counts use the same convention.
    // Consult this state lookup only when the texture lookup misses.
    struct Wr64MatrixStateWatch {
        uint32_t triangles;
        uint32_t combinerH;
        uint32_t combinerL;
        uint32_t otherModeH;
        uint32_t otherModeL;
        const char *family;
    };

    inline const std::vector<Wr64MatrixStateWatch> &wr64MatrixStateWatchList() {
        static const std::vector<Wr64MatrixStateWatch> list = {
            // Wrong-way arrow: 10 triangles, untextured, prim-tinted pink.
            // Composer: combiner FCFFFFFF FFFE773B, other mode 00552078
            // 00082CFF - stored swapped, per the note above.
            { 10u, 0xFFFE773Bu, 0xFCFFFFFFu, 0x00082CFFu, 0x00552078u, "wrongway_arrow" },
            // Pause-menu rolling cubes: 12 triangles, untextured, prim green,
            // ORTHOGRAPHIC - the first watched family that is not perspective.
            // Composer: combiner FCFFFFFF FFFE793C, other mode 00552048
            // 00000CFF - stored swapped, per the note above.
            { 12u, 0xFFFE793Cu, 0xFCFFFFFFu, 0x00000CFFu, 0x00552048u, "pause_cube" },
            // Ring textures vary by course and section. Fall back to the measured torus
            // render state when texture lookup misses. The fingerprint was checked across
            // 26,984 ring rows; use callDesc's swapped word order as described above.
            { 48u, 0xF0FFF83Cu, 0xFC327E2Cu, 0x00182CFFu, 0xC8112078u, "stunt_ring" },
        };
        return list;
    }

    inline const char *wr64MatrixStateFamily(uint32_t triangles,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        for (const Wr64MatrixStateWatch &w : wr64MatrixStateWatchList()) {
            if ((w.triangles == triangles) &&
                (w.combinerH == combinerH) && (w.combinerL == combinerL) &&
                (w.otherModeH == otherModeH) && (w.otherModeL == otherModeL))
            {
                return w.family;
            }
        }
        return nullptr;
    }

    inline const std::unordered_map<uint64_t, const char *> &wr64MatrixWatchMap() {
        static const std::unordered_map<uint64_t, const char *> map = [] {
            std::unordered_map<uint64_t, const char *> m;
            for (const Wr64MatrixWatch &w : wr64MatrixWatchList()) {
                m.emplace(w.texture, w.family);
            }
            return m;
        }();
        return map;
    }

    // Returns the family name, or nullptr when the texture is not watched.
    inline const char *wr64MatrixWatchFamily(uint64_t texture) {
        const auto &m = wr64MatrixWatchMap();
        const auto it = m.find(texture);
        return (it == m.end()) ? nullptr : it->second;
    }

    // ------------------------------------------------------------------ arming --
    inline const char *wr64MatrixSlotsPath() {
        static const char *path = std::getenv("WR64_MATRIX_SLOTS");
        return path;
    }

    inline const char *wr64MatrixTrackPath() {
        static const char *path = std::getenv("WR64_MATRIX_TRACK");
        return path;
    }

    // WR64_MATRIX_TRACK_FAMILIES: optional comma-separated family filter for
    // the per-frame track. Added 2026-08-04 after the Dolphin Park corona
    // capture: an UNFILTERED track let the dolphins write the 2M-row cap full
    // (737 MB) before the family under investigation had a fair share. Empty
    // or unset means no filter - every watched family records, as before.
    inline const std::vector<std::string> &wr64MatrixTrackFamilyFilter() {
        static const std::vector<std::string> filter = [] {
            std::vector<std::string> f;
            const char *raw = std::getenv("WR64_MATRIX_TRACK_FAMILIES");
            if ((raw != nullptr) && (raw[0] != '\0')) {
                std::string current;
                for (const char *c = raw; ; c++) {
                    if ((*c == ',') || (*c == '\0')) {
                        if (!current.empty()) {
                            f.push_back(current);
                            current.clear();
                        }
                        if (*c == '\0') {
                            break;
                        }
                    }
                    else {
                        current.push_back(*c);
                    }
                }
            }
            return f;
        }();
        return filter;
    }

    inline bool wr64MatrixTrackFamilyPasses(const char *family) {
        const std::vector<std::string> &filter = wr64MatrixTrackFamilyFilter();
        if (filter.empty()) {
            return true;
        }
        for (const std::string &f : filter) {
            if (f == family) {
                return true;
            }
        }
        return false;
    }

    inline bool wr64MatrixSlotsArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64MatrixSlotsPath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[matrixslots] slot summary armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[matrixslots] watching %zu textures\n",
                    wr64MatrixWatchList().size()); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    inline bool wr64MatrixTrackArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64MatrixTrackPath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[matrixslots] per-frame track armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    inline bool wr64MatrixAnyArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        return wr64MatrixSlotsArmed() || wr64MatrixTrackArmed();
    }

    // ------------------------------------------------------------ slot summary --
    //
    // The texture set per slot is CAPPED. The gantry pool had 46 textures on one
    // slot, so 64 leaves headroom while bounding memory in the game's own
    // process. Anything past the cap still counts, so "shared with at least 64"
    // is never mistaken for "shared with exactly 64".
    static constexpr size_t Wr64MatrixSlotTextureCap = 64;
    static constexpr size_t Wr64MatrixSlotPhysCap = 16;

    // Rewrite the summary this often, measured in distinct frames seen. About
    // eight seconds at 30 Hz. The file is a few hundred rows so rewriting it
    // whole is cheaper than any incremental scheme, and it means a killed
    // session loses at most the last few seconds instead of everything.
    static constexpr uint64_t Wr64MatrixSummaryFrames = 240;

    struct Wr64MatrixSlot {
        uint64_t draws = 0;
        uint64_t frames = 0;
        uint64_t firstFrame = 0;
        uint64_t lastFrame = 0;
        bool seenAny = false;
        std::set<uint64_t> textures;
        uint64_t texturesDropped = 0;
        std::set<uint32_t> physAddresses;
        uint64_t physDropped = 0;
        // Which watched families ever landed on this slot. More than one name
        // here is the finding: it means the slot is shared between objects the
        // fix would have to tell apart.
        //
        // std::string, NOT const char *. The family name is a string literal
        // repeated once per texture in the watch list, and whether the compiler
        // merges identical literals into one address is up to it. A pointer set
        // would then hold six separate entries all spelling "dolphin" and the
        // verdict would report six slots where there is one.
        std::set<std::string> families;
        float xMin = 0.0f, xMax = 0.0f;
        float yMin = 0.0f, yMax = 0.0f;
        float zMin = 0.0f, zMax = 0.0f;
    };

    struct Wr64MatrixTrackRow {
        uint64_t frame;
        uint64_t texture;
        uint32_t worldIndex;
        uint32_t segAddress;
        uint32_t physAddress;
        uint32_t triangles;
        uint32_t combinerH, combinerL;
        uint32_t otherModeH, otherModeL;
        float x, y, z;
        float sx, sy, sz;
        // Record submitted rotation as well as translation to distinguish matrix-driven
        // rocking from mesh animation; a stationary center does not imply a rigid object.
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
        // R3, 2026-08-03: THE INTERPOLATED TRANSFORM AND THE GROUP'S OWN FLAGS.
        //
        // R1 and R2 both recorded what the GAME SUBMITTED. Two captures proved
        // the submitted data is healthy - addresses stable, rank pairing 100%,
        // rotation live at 0.45 deg/tick - and neither could say whether RT64
        // then interpolated any of it, because neither ever looked at RT64's
        // output. That is the gap.
        //
        // lx/ly/lz come from lerpWorldTransforms, the matrix actually drawn this
        // OUTPUT frame. The recorder runs per output frame while the game ticks
        // at 20 Hz, so a working interpolation writes SEVERAL DISTINCT lerp
        // positions per submission_frame and a broken one writes the same value
        // every time. Row count per (frame, buoy) is therefore the answer by
        // itself - no threshold, no interpretation.
        //
        // lerpOk distinguishes "not interpolated" from "index out of range".
        // Without it both look like a repeated value and the run says nothing.
        float lx, ly, lz;
        uint32_t lerpOk;
        // Record drawn rotation and vertex hashes to distinguish matrix interpolation
        // from mesh animation. Submitted rotation and drawn translation alone cannot
        // show whether angular motion reaches the rendered output.
        float lm00, lm01, lm02;
        float lm10, lm11, lm12;
        float lm20, lm21, lm22;
        // The mesh itself. If this hash is identical tick to tick then the buoy
        // is rigid, vertex interpolation had nothing to interpolate, and R4 was
        // always going to be a no-op no matter how correctly it was applied.
        uint32_t vtxCount;
        uint64_t vtxHash;
        // The group's own interpolation modes. If either of these reads
        // G_EX_COMPONENT_SKIP for a buoy then the search is over and no amount
        // of transform analysis would ever have found it.
        uint32_t posInterp, vtxInterp, matrixId;
        const char *family;
        // Compare authored and interpolated tile coordinates to observe texture-driven
        // motion independently of matrix and vertex animation.
        float tileUls, tileUlt;
        float lerpTileUls, lerpTileUlt;
        uint32_t tileLerpValid;
        // Hash per-vertex RGBA as well as positions. Color/alpha pose changes can animate
        // an otherwise rigid mesh and are not explained by transform interpolation.
        uint64_t colHash;
    };

    static constexpr size_t Wr64MatrixTrackMaxRows = 2000000;
    static constexpr size_t Wr64MatrixTrackFrameWindow = 16;

    struct Wr64MatrixState {
        // summary
        std::map<uint32_t, Wr64MatrixSlot> slots;
        uint64_t summaryFrames = 0;
        uint64_t lastSummaryFrame = 0;
        uint64_t lastSeenFrame = 0;
        bool sawAnyFrame = false;

        // track
        std::FILE *trackFile = nullptr;
        bool trackOpened = false;
        bool trackCapped = false;
        size_t trackWritten = 0;
        std::vector<Wr64MatrixTrackRow> trackPending;
        std::deque<std::pair<uint64_t, std::set<std::pair<uint32_t, uint64_t>>>> trackSeen;
    };

    // INTENTIONALLY LEAKED, and this is not laziness.
    //
    // The closer below is a function-local static whose destructor writes the
    // summary at exit. Function-local statics are destroyed in reverse order of
    // CONSTRUCTION, and the closer is constructed before the state it needs -
    // so with plain `static Wr64MatrixState s;` the state is torn down first and
    // the closer then walks a destroyed std::map of std::sets. That is not a
    // theoretical hazard: the first version of this header segfaulted at exit on
    // the very first self-test.
    //
    // Heap objects that are never deleted have no destructor to order, so the
    // closer can always touch them. The process is ending; the memory is going
    // back regardless.
    inline std::mutex &wr64MatrixMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    inline Wr64MatrixState &wr64MatrixState() {
        static Wr64MatrixState *s = new Wr64MatrixState();
        return *s;
    }

    // Rewrites the whole summary file. Called on a frame cadence and once more
    // at exit.
    inline void wr64MatrixWriteSummaryLocked() {
        if (!wr64MatrixSlotsArmed()) {
            return;
        }

        Wr64MatrixState &s = wr64MatrixState();
        std::FILE *f = std::fopen(wr64MatrixSlotsPath(), "wb");
        if (f == nullptr) {
            std::fprintf(stderr, "[matrixslots] could not open %s for writing\n",
                wr64MatrixSlotsPath());
            std::fflush(stderr);
            return;
        }

        std::fprintf(f, "# WR64 matrix slot summary. One row per SEGMENTED matrix address,\n");
        std::fprintf(f, "# covering every draw in the session - not only watched ones. A slot\n");
        std::fprintf(f, "# whose distinct_textures is large is a recycled scratch slot and\n");
        std::fprintf(f, "# CANNOT be used as an object identity. That is how this idea died for\n");
        std::fprintf(f, "# the start gantry: 27 slots, every one shared with 7 to 46 textures.\n");
        std::fprintf(f, "#\n");
        std::fprintf(f, "# watch_families lists the watched families that landed on the slot.\n");
        std::fprintf(f, "# One name and a small distinct_textures is the good case. Two names\n");
        std::fprintf(f, "# on one slot means address keying would merge two objects.\n");
        std::fprintf(f, "seg_addr,draws,frames,first_frame,last_frame,distinct_textures,"
                       "textures_capped,distinct_phys,phys_capped,watch_families,"
                       "x_min,x_max,y_min,y_max,z_min,z_max,textures\n");

        for (const auto &entry : s.slots) {
            const Wr64MatrixSlot &slot = entry.second;

            std::string familyList;
            for (const std::string &fam : slot.families) {
                if (!familyList.empty()) {
                    familyList += " ";
                }
                familyList += fam;
            }
            if (familyList.empty()) {
                familyList = "-";
            }

            std::string textureList;
            size_t textureShown = 0;
            for (uint64_t t : slot.textures) {
                if (textureShown >= 16) {
                    textureList += " ...";
                    break;
                }
                char buf[24];
                std::snprintf(buf, sizeof(buf), "%016llX", static_cast<unsigned long long>(t));
                if (!textureList.empty()) {
                    textureList += " ";
                }
                textureList += buf;
                textureShown++;
            }

            std::fprintf(f, "%08X,%llu,%llu,%llu,%llu,%zu,%llu,%zu,%llu,%s,"
                           "%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%s\n",
                entry.first,
                static_cast<unsigned long long>(slot.draws),
                static_cast<unsigned long long>(slot.frames),
                static_cast<unsigned long long>(slot.firstFrame),
                static_cast<unsigned long long>(slot.lastFrame),
                slot.textures.size(),
                static_cast<unsigned long long>(slot.texturesDropped),
                slot.physAddresses.size(),
                static_cast<unsigned long long>(slot.physDropped),
                familyList.c_str(),
                slot.xMin, slot.xMax, slot.yMin, slot.yMax, slot.zMin, slot.zMax,
                textureList.c_str());
        }

        std::fclose(f);
    }

    inline void wr64MatrixFlushTrackLocked() {
        Wr64MatrixState &s = wr64MatrixState();
        if (s.trackFile == nullptr) {
            return;
        }

        for (const Wr64MatrixTrackRow &r : s.trackPending) {
            std::fprintf(s.trackFile,
                "%llu,%u,%08X,%08X,%016llX,%s,%u,%08X,%08X,%08X,%08X,"
                "%.3f,%.3f,%.3f,%.4f,%.4f,%.4f,"
                "%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,"
                "%.4f,%.4f,%.4f,%u,%u,%u,%08X,"
                "%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,"
                "%u,%016llX,%.2f,%.2f,%.2f,%.2f,%u,%016llX\n",
                static_cast<unsigned long long>(r.frame),
                r.worldIndex, r.segAddress, r.physAddress,
                static_cast<unsigned long long>(r.texture),
                r.family,
                r.triangles,
                r.combinerH, r.combinerL, r.otherModeH, r.otherModeL,
                r.x, r.y, r.z, r.sx, r.sy, r.sz,
                // Six decimals, not three. A buoy rocking a couple of degrees a
                // tick moves a basis component by ~0.03; at three decimals a
                // slow roll would quantise to a staircase in the CSV and be
                // read as the very stepping this run is trying to find.
                r.m00, r.m01, r.m02,
                r.m10, r.m11, r.m12,
                r.m20, r.m21, r.m22,
                r.lx, r.ly, r.lz, r.lerpOk,
                r.posInterp, r.vtxInterp, r.matrixId,
                r.lm00, r.lm01, r.lm02,
                r.lm10, r.lm11, r.lm12,
                r.lm20, r.lm21, r.lm22,
                r.vtxCount, static_cast<unsigned long long>(r.vtxHash),
                r.tileUls, r.tileUlt, r.lerpTileUls, r.lerpTileUlt, r.tileLerpValid,
                static_cast<unsigned long long>(r.colHash));
        }

        s.trackPending.clear();
        std::fflush(s.trackFile);
    }

    // The verdict, printed where the user can read it without opening a CSV.
    // For each watched family: how many distinct slots it used, and the worst
    // sharing seen on any of them. One slot per object and a tiny texture count
    // is the result that makes address keying possible.
    inline void wr64MatrixPrintVerdictLocked() {
        Wr64MatrixState &s = wr64MatrixState();
        if (s.slots.empty()) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[matrixslots] no draws recorded.\n"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return;
        }

        std::map<std::string, std::pair<size_t, size_t>> perFamily;
        for (const auto &entry : s.slots) {
            const Wr64MatrixSlot &slot = entry.second;
            for (const std::string &fam : slot.families) {
                auto &acc = perFamily[fam];
                acc.first++;
                if (slot.textures.size() > acc.second) {
                    acc.second = slot.textures.size();
                }
            }
        }

        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "\n[matrixslots] ---- verdict ----\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[matrixslots] %zu distinct matrix slots seen this session.\n",
            s.slots.size()); }
        if (perFamily.empty()) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[matrixslots] NONE of the watched objects were drawn. Either they were\n"
                "[matrixslots] never on screen, or their textures have changed.\n"); }
        }
        else {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[matrixslots] %-12s %8s  %s\n",
                "family", "slots", "worst sharing (textures on one slot)"); }
            for (const auto &entry : perFamily) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[matrixslots] %-12s %8zu  %zu\n",
                    entry.first.c_str(), entry.second.first, entry.second.second); }
            }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[matrixslots]\n"
                "[matrixslots] Reading it: worst sharing of 1 means the slot belongs to that\n"
                "[matrixslots] object alone and the address IS its identity. A large number\n"
                "[matrixslots] means a recycled scratch pool - that is what killed this idea\n"
                "[matrixslots] for the start gantry, where one slot carried 46 textures.\n"); }
        }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    struct Wr64MatrixCloser {
        ~Wr64MatrixCloser() {
            std::lock_guard<std::mutex> lock(wr64MatrixMutex());
            wr64MatrixFlushTrackLocked();
            wr64MatrixWriteSummaryLocked();
            wr64MatrixPrintVerdictLocked();
        }
    };

    // Called for EVERY draw. The summary needs every draw to answer whether a
    // slot is shared; the track filters to watched textures on its own.
    inline void wr64MatrixSlotsRecord(uint64_t frame, uint32_t worldIndex,
        uint32_t segAddress, uint32_t physAddress, uint64_t texture,
        uint32_t triangles,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL,
        float x, float y, float z, float sx, float sy, float sz,
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22,
        float lx, float ly, float lz, uint32_t lerpOk,
        uint32_t posInterp, uint32_t vtxInterp, uint32_t matrixId,
        float lm00, float lm01, float lm02,
        float lm10, float lm11, float lm12,
        float lm20, float lm21, float lm22,
        uint32_t vtxCount, uint64_t vtxHash,
        float tileUls, float tileUlt,
        float lerpTileUls, float lerpTileUlt, uint32_t tileLerpValid,
        uint64_t colHash)
    {
        if (!wr64MatrixAnyArmed()) {
            return;
        }

        static Wr64MatrixCloser closer;
        (void)closer;

        const char *family = wr64MatrixWatchFamily(texture);
        if (family == nullptr) {
            // Untextured families (the wrong-way arrow, the pause cubes) are
            // named by full render state - the texture lookup cannot see them.
            family = wr64MatrixStateFamily(triangles, combinerH, combinerL,
                otherModeH, otherModeL);
        }
        if (family == nullptr) {
            // R9: the ring test the CLAIM uses (otherModeL floats - the
            // blender/fog word is course-tinted; Sunset Bay proved it), so
            // whatever the claim catches, this recorder records.
            if (wr64StuntRingState(triangles, combinerH, combinerL, otherModeH)) {
                family = "stunt_ring";
            }
            // Diagnostic net under that: ANY 48-triangle draw the tests
            // above did not name. If a course's rings differ in the
            // combiner too (not just the blender), they land here and the
            // capture hands us their exact state instead of another blind
            // zero-row round. Dormant unless "ring48" is in
            // WR64_MATRIX_TRACK_FAMILIES.
            else if (triangles == Wr64StuntRingTriangles) {
                family = "ring48";
            }
        }

        std::lock_guard<std::mutex> lock(wr64MatrixMutex());
        Wr64MatrixState &s = wr64MatrixState();

        // ---------------------------------------------------------- summary --
        if (wr64MatrixSlotsArmed()) {
            Wr64MatrixSlot &slot = s.slots[segAddress];
            if (!slot.seenAny) {
                slot.seenAny = true;
                slot.firstFrame = frame;
                slot.lastFrame = frame;
                slot.frames = 1;
                slot.xMin = slot.xMax = x;
                slot.yMin = slot.yMax = y;
                slot.zMin = slot.zMax = z;
            }
            else {
                if (frame != slot.lastFrame) {
                    slot.frames++;
                    slot.lastFrame = frame;
                }
                if (x < slot.xMin) { slot.xMin = x; }
                if (x > slot.xMax) { slot.xMax = x; }
                if (y < slot.yMin) { slot.yMin = y; }
                if (y > slot.yMax) { slot.yMax = y; }
                if (z < slot.zMin) { slot.zMin = z; }
                if (z > slot.zMax) { slot.zMax = z; }
            }

            slot.draws++;

            if (slot.textures.size() < Wr64MatrixSlotTextureCap) {
                slot.textures.insert(texture);
            }
            else if (slot.textures.find(texture) == slot.textures.end()) {
                slot.texturesDropped++;
            }

            if (slot.physAddresses.size() < Wr64MatrixSlotPhysCap) {
                slot.physAddresses.insert(physAddress);
            }
            else if (slot.physAddresses.find(physAddress) == slot.physAddresses.end()) {
                slot.physDropped++;
            }

            if (family != nullptr) {
                slot.families.insert(family);
            }

            if (!s.sawAnyFrame) {
                s.sawAnyFrame = true;
                s.lastSeenFrame = frame;
                s.lastSummaryFrame = frame;
            }
            else if (frame != s.lastSeenFrame) {
                s.lastSeenFrame = frame;
                s.summaryFrames++;
                if (s.summaryFrames >= Wr64MatrixSummaryFrames) {
                    s.summaryFrames = 0;
                    s.lastSummaryFrame = frame;
                    wr64MatrixWriteSummaryLocked();
                }
            }
        }

        // ------------------------------------------------------------ track --
        if (!wr64MatrixTrackArmed() || (family == nullptr) ||
            !wr64MatrixTrackFamilyPasses(family)) {
            return;
        }

        if (!s.trackOpened) {
            s.trackOpened = true;
            s.trackFile = std::fopen(wr64MatrixTrackPath(), "wb");
            if (s.trackFile != nullptr) {
                std::fprintf(s.trackFile,
                    "submission_frame,world_index,seg_addr,phys_addr,texture,family,"
                    "triangles,combiner_h,combiner_l,othermode_h,othermode_l,"
                    "x,y,z,scale_x,scale_y,scale_z,"
                    "m00,m01,m02,m10,m11,m12,m20,m21,m22,"
                    "lerp_x,lerp_y,lerp_z,lerp_ok,pos_interp,vtx_interp,matrix_id,"
                    "lm00,lm01,lm02,lm10,lm11,lm12,lm20,lm21,lm22,"
                    "vtx_count,vtx_hash,tile_uls,tile_ult,lerp_tile_uls,lerp_tile_ult,tile_lerp_valid,col_hash\n");
                std::fflush(s.trackFile);
            }
            else {
                std::fprintf(stderr, "[matrixslots] could not open %s for writing\n",
                    wr64MatrixTrackPath());
                std::fflush(stderr);
            }
        }

        if (s.trackFile == nullptr) {
            return;
        }

        if (s.trackWritten >= Wr64MatrixTrackMaxRows) {
            if (!s.trackCapped) {
                s.trackCapped = true;
                std::fprintf(s.trackFile,
                    "# CAPPED at %zu rows - recording stopped, later frames are ABSENT\n",
                    Wr64MatrixTrackMaxRows);
                std::fflush(s.trackFile);
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[matrixslots] TRACK CAPPED at %zu rows; later frames are NOT recorded.\n",
                    Wr64MatrixTrackMaxRows); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return;
        }

        // One row per (frame, transform, texture). Not per (frame, transform):
        // several pieces of one model can share a transform, and how many pieces
        // share it is itself part of the answer - if all seventeen whale layers
        // ride one transform then the whale needs one id, not seventeen.
        auto it = s.trackSeen.end();
        for (auto scan = s.trackSeen.begin(); scan != s.trackSeen.end(); ++scan) {
            if (scan->first == frame) { it = scan; break; }
        }
        if (it == s.trackSeen.end()) {
            s.trackSeen.emplace_back(frame, std::set<std::pair<uint32_t, uint64_t>>());
            it = std::prev(s.trackSeen.end());
            while (s.trackSeen.size() > Wr64MatrixTrackFrameWindow) {
                s.trackSeen.pop_front();
                it = std::prev(s.trackSeen.end());
            }
        }
        // R3: THE DEDUPE KEY NOW CARRIES THE INTERPOLATED POSITION.
        //
        // R1/R2 kept one row per (frame, transform, texture). The recorder runs
        // once per OUTPUT frame, so that collapsed all three of a tick's output
        // frames into a single row and threw away the only evidence that
        // distinguishes a smooth object from a stepping one.
        //
        // Folding the lerp position into the key keeps one row per DISTINCT
        // interpolated state instead. A buoy that is interpolating writes
        // several rows per submission_frame; one that is not writes exactly one,
        // because all three output frames carry the identical matrix. The row
        // count IS the measurement - there is no threshold to argue about.
        //
        // Bit patterns, not the float values: this is an identity test, and
        // memcpy is the defined way to read them. -0.0 and 0.0 hashing apart is
        // harmless here - it costs one duplicate row, never a missed one.
        uint32_t lxBits, lyBits, lzBits;
        std::memcpy(&lxBits, &lx, sizeof(lxBits));
        std::memcpy(&lyBits, &ly, sizeof(lyBits));
        std::memcpy(&lzBits, &lz, sizeof(lzBits));
        uint32_t lmBits[9];
        const float lmVals[9] = { lm00, lm01, lm02, lm10, lm11, lm12, lm20, lm21, lm22 };
        for (int i = 0; i < 9; i++) {
            std::memcpy(&lmBits[i], &lmVals[i], sizeof(uint32_t));
        }
        uint32_t tileBits[2];
        std::memcpy(&tileBits[0], &lerpTileUls, sizeof(uint32_t));
        std::memcpy(&tileBits[1], &lerpTileUlt, sizeof(uint32_t));
        uint64_t lerpHash = 1469598103934665603ULL;
        for (uint32_t bits : { lxBits, lyBits, lzBits, lerpOk,
                               lmBits[0], lmBits[1], lmBits[2],
                               lmBits[3], lmBits[4], lmBits[5],
                               lmBits[6], lmBits[7], lmBits[8],
                               tileBits[0], tileBits[1], tileLerpValid }) {
            lerpHash = (lerpHash ^ uint64_t(bits)) * 1099511628211ULL;
        }
        if (!it->second.insert(std::make_pair(worldIndex, texture ^ lerpHash)).second) {
            return;
        }

        s.trackPending.push_back(Wr64MatrixTrackRow{
            frame, texture, worldIndex, segAddress, physAddress, triangles,
            combinerH, combinerL, otherModeH, otherModeL,
            x, y, z, sx, sy, sz,
            m00, m01, m02, m10, m11, m12, m20, m21, m22,
            // ORDER FOLLOWS THE STRUCT, NOT THE CSV. This is an aggregate
            // initialiser, so every value is positional: R5 inserted lm00..lm22
            // and vtxCount/vtxHash between lerpOk and posInterp in the struct,
            // and leaving this line in CSV order silently fed posInterp into
            // lm00. Adding a field to Wr64MatrixTrackRow means fixing this line
            // in the SAME edit.
            lx, ly, lz, lerpOk,
            lm00, lm01, lm02, lm10, lm11, lm12, lm20, lm21, lm22,
            vtxCount, vtxHash,
            posInterp, vtxInterp, matrixId, family,
            tileUls, tileUlt, lerpTileUls, lerpTileUlt, tileLerpValid,
            colHash });
        s.trackWritten++;

        if (s.trackPending.size() >= 2048) {
            wr64MatrixFlushTrackLocked();
        }
    }
};
