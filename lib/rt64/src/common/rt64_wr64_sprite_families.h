//
// WR64 sprite families — give named scenery objects a stable identity so RT64
// stops guessing which one is which between frames.
//
// The problem, in one paragraph
// ----------------------------
// The game hands RT64 a picture 30 times a second and RT64 shows 60. To fill the
// gap it must know which object in this picture is the same object as in the
// last one. WR64 emits no G_EX_MATRIXGROUP anywhere, so every transform carries
// G_EX_ID_AUTO, GameFrame::buildTransformIdMap skips it, and the pairing falls to
// a heuristic. For a lone object the heuristic usually copes. For several
// near-identical copies it does not.
//
// WHY THESE OBJECTS AND NOT THE OTHERS
// ------------------------------------
// Measured across five courses on 2026-07-30, against true nearest-neighbour
// pairing (sound here: members sit hundreds of units apart and move tens):
//
//     object                n   moves/frame  group shape change  order correct
//     Port Blue barrels     2         0.00                0.00          100.0%
//     Sunny Beach seagulls  5        29.83                0.84          100.0%
//     Sunset Bay dolphins   3        43.49                3.96           94.7%
//     Drake Lake fish      12         8.33                5.54           45.4%
//
// The deciding column is the third, not the second. What breaks the drawing
// order is not speed and not member count - it is whether the group HOLDS ITS
// SHAPE. Barrels are anchored and can never overtake each other. Seagulls fly
// fast but in formation. Dolphins drift apart and back. Drake Lake's fish mill
// about inside the school, so the game reorders them and the order stops meaning
// anything.
//
// Only families whose order is reliable are listed here. The dolphins at 94.7%
// are deliberately EXCLUDED: they sit 853 units apart, so the 5% of frames where
// the order lies would slide an animal most of a screen once interpolation is
// forced on. That is the R1 buoy-arrow failure, and a wrong fix applied
// confidently is worse than a known bug.
//
// ★ TWO RULES THIS TABLE LEARNED THE HARD WAY, R1 -> R2
//
// 1. AN "ORDER CORRECT" FIGURE MEANS NOTHING WITHOUT THE HOLD FIGURE BESIDE IT.
//    The Port Blue barrels scored 100% and were shipped. They flickered. Their
//    member count is 1, 2, 3, 4, 5, 6 or 7 - it holds in 28% of frames - and the
//    100% had been computed ONLY over frames where the count matched, so it had
//    excluded every failing case by construction. A count that changes reshuffles
//    the ranks and the ids flip. The barrels are now BANNED, not merely absent.
//
// 2. A FAMILY IS CLAIMED WHOLE OR NOT AT ALL. R1 named one of the Marine Fortress
//    birds' three pieces, because the other two are never an object's first draw
//    and the census is blind to them. The named piece interpolated, the other two
//    did not, and the birds warped in flight. Half a family is worse than none.
//
// Identity comes from the DRAW, not from the matrix address - the gantry work
// proved address keying tells RT64 that a banner and a traffic light are the
// same object because they shared a scratch slot.
//
// The id is the transform's RANK among the family's claimed transforms,
// ascending by transform index. That is the gantry's scheme, and it needs no
// contiguity. For a single-instance family - the helicopter, the newspaper - it
// is correct by construction: one claimed transform always ranks 0.
//
// TRIANGLE COUNT IS NOT PART OF THE KEY. The newspaper sheet was observed with
// 6, 12, 18 and 24 triangles in one session. Requiring an exact count would have
// claimed it only sometimes, which is the worst possible outcome: a member that
// is named in some frames and not others cannot pair with itself.
//
// This is a fix, so it is compiled in and always on. There is no enable variable.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace RT64 {
    // ------------------------------------------------------------ families --
    //
    // Base 0x57600000 is clear of every id already in use: 0x57000000 articulated
    // limbs, 0x57100000 watercraft selector, 0x57200000 course map, 0x57400000
    // gantry, 0x57500000 tropical fish, 0x57524300 sky. Each family reserves
    // 0x10000, far more than any of them needs.
    static constexpr uint32_t Wr64SpriteFamilyBase   = 0x57600000u;
    static constexpr uint32_t Wr64SpriteFamilyStride = 0x00010000u;
    static constexpr uint32_t Wr64SpriteFamilyCap    = 256u;

    enum Wr64SpriteFamilyId : uint32_t {
        Wr64FamilyHelicopter = 0,   // Port Blue. ONE of them, drawn in ten pieces.
        Wr64FamilyNewspaper,        // Port Blue. One sheet, triangle count varies.
        Wr64FamilySeagulls,         // Sunny Beach and Marine Fortress. Formation flight.
        Wr64SpriteFamilyCount
    };

    inline const char *wr64SpriteFamilyName(uint32_t family) {
        switch (family) {
        case Wr64FamilyHelicopter: return "helicopter";
        case Wr64FamilyNewspaper:  return "newspaper";
        case Wr64FamilySeagulls:   return "seagulls";
        default:                   return "?";
        }
    }

    struct Wr64SpriteFamilyEntry {
        uint64_t texture;
        uint32_t combinerH, combinerL;
        uint32_t otherModeH, otherModeL;
        uint32_t family;
    };

    // Composer displays combiner/other-mode pairs as (L << 32) | H; constants below
    // already use callDesc's split order. Birds and tropical fish share render state,
    // so texture identity must lead the family claim.
    inline const Wr64SpriteFamilyEntry *wr64SpriteFamilyTable(size_t &count) {
        static const Wr64SpriteFamilyEntry table[] = {
            // -- Port Blue helicopter: nine body pieces, one shared state ------
            { 0x8679101BFE87295FULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            { 0x5BA82B0E2FFF5B28ULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            { 0x98491F2086F450A4ULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            { 0x2E3AB02EC7746780ULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            { 0x907BF66EE55AA996ULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            { 0x846549D3ADF3C7C6ULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            { 0xF2AF851DFF467FBFULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            { 0x6BD1A280D751F5EFULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            { 0x646F98E1B4D4CA58ULL, 0xFFFFF238u, 0xFC127FFFu, 0x00183CFFu, 0x0C192078u, Wr64FamilyHelicopter },
            // the tenth piece carries a different state - the rotor, by its
            // position in the draw order and its separate blend mode
            { 0x9066CDBFFC1B1740ULL, 0xFFFCF238u, 0xFCFFFFFFu, 0x00183CFFu, 0x0C1849D8u, Wr64FamilyHelicopter },

            // -- Port Blue newspaper sheet -------------------------------------
            { 0x1F26C4530C35D5B7ULL, 0xFFFCF279u, 0xFCFFFFFFu, 0x00083CFFu, 0x00552230u, Wr64FamilyNewspaper },

            // -- Birds ---------------------------------------------------------
            //
            // Sunny Beach uses the first two; Marine Fortress uses the last two
            // PLUS 8730DC..., which is why it is here once and covers both. The
            // courses never coexist, so one family is correct.
            //
            // R2: the two Marine Fortress pieces were missing in R1 and the birds
            // WARPED - the named piece was smoothed while the unnamed two were
            // not, and the model came apart in flight. A family must be claimed
            // whole or not at all; half is worse than none. Those two are never an
            // object's first layer, so the census cannot see them and they were
            // found with the Composer.
            { 0xE0DE60C30E0CA4C1ULL, 0xFFFFF238u, 0xFC127FFFu, 0x00182CFFu, 0xC8113078u, Wr64FamilySeagulls },
            { 0x8730DC2C936F608AULL, 0xFFFFF238u, 0xFC127FFFu, 0x00182CFFu, 0xC8113078u, Wr64FamilySeagulls },
            { 0xA7A7757A4556102EULL, 0xFFFFF238u, 0xFC127FFFu, 0x00182CFFu, 0xC8113078u, Wr64FamilySeagulls },
            { 0x257AFC2EEA156C98ULL, 0xFFFFF238u, 0xFC127FFFu, 0x00182CFFu, 0xC8113078u, Wr64FamilySeagulls },
            // The wing draw uses a different combiner from the body and is not a transform's
            // first draw, so a first-draw census omits it. This claim aligns its motion with
            // the bird; visibility and color/alpha animation require separate treatment.
            { 0xACAC918D3A8DA899ULL, 0xFFFFF3F8u, 0xFC11FE04u, 0x00182CFFu, 0xC8113078u, Wr64FamilySeagulls },
        };
        count = sizeof(table) / sizeof(table[0]);
        return table;
    }

    // Returns the family, or -1. Triangle count is deliberately not consulted.
    inline int32_t wr64SpriteFamilyClaim(uint64_t tmemHash,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        size_t count = 0;
        const Wr64SpriteFamilyEntry *table = wr64SpriteFamilyTable(count);
        for (size_t i = 0; i < count; i++) {
            const Wr64SpriteFamilyEntry &e = table[i];
            if (e.texture != tmemHash) {
                continue;
            }
            if ((e.combinerH != combinerH) || (e.combinerL != combinerL) ||
                (e.otherModeH != otherModeH) || (e.otherModeL != otherModeL))
            {
                continue;
            }
            return int32_t(e.family);
        }
        return -1;
    }

    // Returns 0 when the family produced more members than its reserved space.
    // The caller must then leave that transform at G_EX_ID_AUTO rather than wrap
    // it onto an id belonging to a different member.
    inline uint32_t wr64SpriteFamilyRankedId(uint32_t family, uint32_t rank) {
        if ((family >= uint32_t(Wr64SpriteFamilyCount)) || (rank >= Wr64SpriteFamilyCap)) {
            return 0;
        }
        return Wr64SpriteFamilyBase + (family * Wr64SpriteFamilyStride) + rank;
    }

    // --------------------------------- R4: seagulls by TRAJECTORY --
    //
    // R3 named the birds by their segment-6 matrix address, and the R3
    // capture then proved the address is not the bird either. The flock
    // is 35 persistent birds, and in 282 captured frames not one of
    // them was ever absent - yet the addresses churned: on nine frames
    // 6 to 28 addresses jumped together (median 144 units, maximum
    // 1971), each landing where another address had just been. The
    // game keeps a COMPACTED list of visible gulls and re-deals the
    // matrix slots whenever the roster or order changes - the fish
    // school's sliding block, on segment-6 addresses. Rank churned
    // there (R1) and the address churns there too (R3): both names
    // depend on the deal, not on the bird.
    //
    // What survives every re-deal is the trajectory. Replaying the
    // whole R3 capture against a persistent registry - match this
    // frame's birds to remembered ones by ascending distance, mint a
    // fresh name only when nothing is in reach - kept all 35 names
    // alive through every churn event with zero losses, and the
    // largest genuine per-frame step was 67 units. The radius is 120
    // per frame of absence (1.8x that measured maximum, and safely
    // under the re-deal jumps it must reject), capped at the carry
    // window.
    //
    // Two matrices ride each bird - a far sprite and the near
    // four-piece model, 5.5 units apart, closer than birds ever fly
    // to each other (~20). They never share a texture on one
    // transform (0 mixed in 8,974 samples), so the registry is split
    // by KIND - far sprite, near model - and the 5.5-unit pair can
    // never trade names. Within a kind, two birds inside 120 of each
    // other can in principle swap names on a bad frame (2% of stable
    // frames disagreed with the address in the replay); both names
    // stay on smooth nearby paths when it happens, which the eye
    // cannot tell apart, unlike the re-deal snap it replaces.
    //
    // A bird the game stops drawing - the top-edge cull - keeps its
    // registry entry for Wr64SeagullCarryFrames, and the stamp pass
    // appends a GHOST transform carrying its last matrix so the name
    // stays in the pairing map; when the bird returns it pairs with
    // its own last position and glides in instead of standing frozen
    // for a tick. Past the window the entry retires and a return is
    // the spawn it truly is.
    static constexpr float    Wr64SeagullHandoffUnitsPerFrame = 120.0f;
    static constexpr uint64_t Wr64SeagullCarryFrames          = 8;
    static constexpr uint32_t Wr64SpriteSeagullIdBase         = 0x57800000u;
    static constexpr uint64_t Wr64SeagullFarTexture           = 0xE0DE60C30E0CA4C1ULL;

    inline uint32_t wr64SeagullSerialId(uint32_t serial) {
        return Wr64SpriteSeagullIdBase | (serial & 0xFFFFu);
    }

    inline bool wr64SpriteFamilyIsOurs(uint32_t matrixId) {
        return (matrixId >= Wr64SpriteFamilyBase) &&
               (matrixId < (Wr64SpriteFamilyBase +
                            (uint32_t(Wr64SpriteFamilyCount) * Wr64SpriteFamilyStride)));
    }

    // Guard continuity for ranked families when culling reassigns an ordinal to a
    // different member. Seagulls now use the trajectory registry above. The historical
    // 2026-07-30 census measured a 29.83-unit maximum step; the 120-unit guard leaves
    // headroom below inter-member spacing. Preserve the ID and snap placement on a
    // breach while keeping vertex/tile animation. Single-instance families have no
    // rank reassignment.
    static constexpr float Wr64SpriteContinuityUnits = 120.0f;

    // --------------------------------------------------------------- notice --
    //
    // ALWAYS ON. Mirrors [gantryidentity] and [fishschool], both validated by eye.
    inline bool wr64SpriteFamilyEnabled() {
        static const bool announced = [] {
            size_t count = 0;
            wr64SpriteFamilyTable(count);
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[spritefamily] APPLYING (%zu textures, %u families, continuity guard, seagulls by trajectory, ghost carry)\n",
                count, uint32_t(Wr64SpriteFamilyCount)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return true;
        }();
        (void)announced;
        return true;
    }

    // One line per family the first time it is claimed, so a run where a family
    // never fired is distinguishable from one where it fired and changed nothing.
    // The gantry needed exactly this to catch a stamp that was wired in and dead.
    inline void wr64SpriteFamilyNote(uint32_t family, size_t stamped, size_t skipped, size_t snapped) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if ((stamped == 0) || (family >= uint32_t(Wr64SpriteFamilyCount))) {
            return;
        }

        static bool announced[Wr64SpriteFamilyCount] = {};
        if (!announced[family]) {
            announced[family] = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[spritefamily] %s: stamped %zu on first hit\n",
                wr64SpriteFamilyName(family), stamped); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // R4: the seagulls no longer pass through here - the trajectory
        // registry names them and never snaps, so this sentence belongs to
        // the RANKED families alone, where it still means a rank changed
        // hands. Said out loud the first time so a pop is never read as
        // the guard failing.
        static bool snapAnnounced[Wr64SpriteFamilyCount] = {};
        if ((snapped > 0) && !snapAnnounced[family]) {
            snapAnnounced[family] = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[spritefamily] %s: %zu kept their name and snapped: the rank was handed to a different member\n",
                wr64SpriteFamilyName(family), snapped); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        static bool overflowed[Wr64SpriteFamilyCount] = {};
        if ((skipped > 0) && !overflowed[family]) {
            overflowed[family] = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[spritefamily] %s: %zu beyond the reserved ids left unnamed\n",
                wr64SpriteFamilyName(family), skipped); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
    }
};
