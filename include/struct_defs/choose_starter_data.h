#ifndef POKEPLATINUM_STRUCT_020425E0_H
#define POKEPLATINUM_STRUCT_020425E0_H

#include "game_options.h"
#include "legal_shiny.h"

#define CHOOSE_STARTER_NUM_OPTIONS 3

typedef struct ChooseStarterData {
    int species;
    const Options *options;
    // Fork: each starter is rolled when the briefcase opens, so the scene can show a shiny one
    // and the chosen starter is given with exactly this PID/IVs. Order: Turtwig, Chimchar, Piplup.
    u32 otID;
    LegalFrame frames[CHOOSE_STARTER_NUM_OPTIONS];
} ChooseStarterData;

#endif // POKEPLATINUM_STRUCT_020425E0_H
