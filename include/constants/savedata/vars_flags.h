#ifndef POKEPLATINUM_CONSTANTS_VARS_AND_FLAGS_H
#define POKEPLATINUM_CONSTANTS_VARS_AND_FLAGS_H

#include "generated/vars_flags.h"

#define NUM_VARS (VARS_END - VARS_START)

// Flags reused by this fork. FLAG_UNUSED_* flags are never read or written by vanilla Platinum,
// so saves stay fully compatible. Flags 0x4000-0x403F live in RAM only and are never saved.
#define FLAG_QOL_QUICK_BATTLE_INTRO   FLAG_UNUSED_0x0168 // Options menu: BATTLE INTRO = QUICK
#define FLAG_QOL_PORTABLE_PC          0x403F             // RAM-only; set only while the start-menu PC is open

#endif // POKEPLATINUM_CONSTANTS_VARS_AND_FLAGS_H
