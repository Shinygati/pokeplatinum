#ifndef POKEPLATINUM_LEGAL_SHINY_H
#define POKEPLATINUM_LEGAL_SHINY_H

#ifdef LEGAL_SHINY_HOST
#include "legal_shiny_host.h"
#else
#include <nitro.h>
#endif

// Shiny odds (1 in N). Change these to retune the whole game.
#define SHINY_ODDS_BASE   4096 // wild, static/legendary, honey tree
#define SHINY_ODDS_GIFT   4096  // script gifts (starters, fossils, Eevee, ...) and gift eggs
#define SHINY_ODDS_EGG    512  // daycare eggs, regardless of parent languages
#define SHINY_ODDS_ROAMER 100  // Mesprit, Cresselia, Articuno, Zapdos, Moltres

#define LEGAL_SHINY_NATURE_ANY (-1)

// How PKHeX checks the RNG calls that come before the PID.
enum LegalFrameType {
    LEGAL_FRAME_METHOD1 = 0, // statics, gifts, roamers: only PID -> IVs must be consecutive
    LEGAL_FRAME_GRASS, // Method J: slot -> [lead] -> nature -> PID -> IVs
    LEGAL_FRAME_SURF, // Method J: slot -> level -> [lead] -> nature -> PID -> IVs
    LEGAL_FRAME_OLD_ROD, // Method J: hook -> [Coronet B1F tile] -> slot -> level -> ...
    LEGAL_FRAME_GOOD_ROD,
    LEGAL_FRAME_SUPER_ROD,
    LEGAL_FRAME_HONEY_TREE, // Method J: level -> [lead] -> nature -> PID -> IVs
};

#define LEGAL_FRAME_MAX_SLOTS 12

typedef struct LegalFrameSpec {
    u8 type; // enum LegalFrameType
    u8 level; // final level of the mon (== met level)
    u8 numSlots;
    u8 rodRate; // hook succeeds when rand / 656 < rodRate
    u8 coronetFeebasArea; // Mt. Coronet B1F: one extra rand between hook and slot
    u8 isFeebas; // that extra rand must have passed (rand >> 15 == 1)
    u8 minLevel; // lowest level allowed if a shiny search has to re-roll the level (Repel), else 0
    u16 species;
    u16 slotSpecies[LEGAL_FRAME_MAX_SLOTS];
    u8 slotMinLevel[LEGAL_FRAME_MAX_SLOTS];
    u8 slotMaxLevel[LEGAL_FRAME_MAX_SLOTS];
} LegalFrameSpec;

typedef struct LegalFrame {
    u32 personality;
    u32 pidSeed; // LCRNG state right after the PID's second call: the next two calls are the IVs
    u8 level; // level the frame's level/slot call produced (== spec level unless relaxed)
} LegalFrame;

// MT-based roll so it never touches the LCRNG calls PKHeX checks.
BOOL LegalShiny_Roll(u32 odds);
BOOL LegalShiny_IsShiny(u32 otID, u32 personality);

// Builds a shiny PID directly (TSV xor), reverse-solves the LCRNG seed that outputs it, and keeps
// the seed only if its untouched IVs give 2x31 and, for wild types, the calls before the PID form a
// valid Method J frame for this species + level. If the budget runs out it next allows any level a
// slot of this species can roll (out->level), then 2x25+ IVs, then any IVs.
// nature: LEGAL_SHINY_NATURE_ANY or a fixed nature (Synchronize). syncLead selects the Synchronize
// frame layout for wild types. Returns FALSE only if every budget ran out (practically never).
BOOL LegalShiny_FindShinyFrame(const LegalFrameSpec *spec, u32 otID, int nature, BOOL syncLead, LegalFrame *out);

// Non-shiny wild frame with a 100% Synchronize proc. Walks forward from preSlotSeed (LCRNG state
// right before the slot call, i.e. right after the hook call when fishing) one call at a time and
// returns the first frame that is a normal vanilla frame for the same species + level, with the
// Synchronize check passing (if syncNature >= 0) and a non-shiny PID. The first candidate is the
// vanilla frame itself, so without Synchronize this is usually exactly what the game would do.
BOOL LegalShiny_FindNormalFrame(const LegalFrameSpec *spec, u32 preSlotSeed, u32 otID, int syncNature, LegalFrame *out);

// Non-shiny Method 1 from the live LCRNG: PID pairs until the nature matches and the PID is not
// shiny; the IVs come from the very next two calls.
void LegalShiny_RollNormalMethod1(u32 otID, int nature, LegalFrame *out);

// Points the LCRNG at the frame's IV calls; call Pokemon_InitWith(..., INIT_IVS_RANDOM, TRUE,
// frame.personality, ...) right after so the IVs (and later held item / Unown form calls) line up.
void LegalShiny_ApplyFrame(const LegalFrame *frame);

// Eggs have no PID/IV correlation in Gen 4. Returns a PID with the same nature, gender byte,
// ability bit and EGG_GENDER_MALE bit that is shiny (or guaranteed not shiny) for otID.
u32 LegalShiny_AdjustEggPersonality(u32 personality, u32 otID, BOOL shiny);

#ifndef LEGAL_SHINY_HOST
#include "struct_defs/pokemon.h"

// Replacement for Pokemon_InitWith(mon, species, level, INIT_IVS_RANDOM, FALSE, 0, OTID_NOT_SET, 0)
// for gifts: rolls 1/odds against otID; a shiny gets a legal Method 1 PID with 2x31 IVs, otherwise
// a normal Method 1 PID that is never shiny.
void Pokemon_InitGiftWithLegalShinyOdds(Pokemon *mon, int species, int level, u32 otID, u32 odds);

// The roll Pokemon_InitGiftWithLegalShinyOdds makes, exposed so a gift can be decided early
// (the starter briefcase shows the result before the Pokémon is given).
void LegalShiny_RollGiftFrame(u32 otID, u32 odds, LegalFrame *out);

// A pre-rolled frame for the next script gift of this species. Pokemon_InitGiftWithLegalShinyOdds
// uses (and clears) it instead of rolling. Kept in RAM only, never in the save.
void LegalShiny_SetPendingGift(u16 species, const LegalFrame *frame);
void LegalShiny_ClearPendingGift(void);
#endif

#endif // POKEPLATINUM_LEGAL_SHINY_H
