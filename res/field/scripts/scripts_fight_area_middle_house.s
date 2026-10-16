#include "macros/scrcmd.inc"
#include "res/text/bank/fight_area_middle_house.h"


    ScriptEntry FightAreaMiddleHouse_PokefanM
    ScriptEntry FightAreaMiddleHouse_SchoolKidM
    ScriptEntry FightAreaMiddleHouse_Youngster
    ScriptEntry FightAreaMiddleHouse_BasePointFanatic
    ScriptEntryEnd

FightAreaMiddleHouse_PokefanM:
    NPCMessage FightAreaMiddleHouse_Text_SeePeakMtCoronet
    End

FightAreaMiddleHouse_SchoolKidM:
    NPCMessage FightAreaMiddleHouse_Text_FanaticalAboutBattling
    End

FightAreaMiddleHouse_Youngster:
    NPCMessage FightAreaMiddleHouse_Text_CheckOutGlobalTerminal
    End

FightAreaMiddleHouse_BasePointFanatic:
    LockAll
    FacePlayer
    PlaySE SE_CONFIRM_sseq_3
    Message pl_msg_00000197_BasePointsFanatic_Intro
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, FightAreaMiddleHouse_DeclinedBasePointsFanatic
    Message pl_msg_00000197_BasePointsFanatic_AskSelectPokemon
    WaitButton
    CloseMessage
    FadeScreenOut COLOR_BLACK
    WaitFadeScreen
    SelectMoveTutorPokemon
    GetSelectedPartySlot VAR_0x8000
    ReturnToField
    FadeScreenIn COLOR_BLACK
    WaitFadeScreen
    GoToIfEq VAR_0x8000, PARTY_SLOT_NONE, FightAreaMiddleHouse_DeclinedBasePointsFanatic
    BufferPartyMonNickname 0, VAR_0x8000
    Message pl_msg_00000197_BasePointsFanatic_Confirm
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, FightAreaMiddleHouse_DeclinedBasePointsFanatic
    CloseMessage
    ResetEVs VAR_0x8000, VAR_RESULT
    GoToIfEq VAR_RESULT, FALSE, FightAreaMiddleHouse_ZeroEvs
    FadeScreenOut COLOR_BLACK
    WaitFadeScreen
    PlayFanfare SEQ_FANFA2_sseq
    WaitFanfare
    FadeScreenIn COLOR_BLACK
    WaitFadeScreen
    Message pl_msg_00000197_BasePointsFanatic_Finished
    GoTo _EndDialogue

FightAreaMiddleHouse_DeclinedBasePointsFanatic:
    Message pl_msg_00000197_BasePointsFanatic_Declined
    GoTo _EndDialogue

FightAreaMiddleHouse_ZeroEvs:
    Message pl_msg_00000197_BasePointsFanatic_ZeroEvs
    GoTo _EndDialogue

_EndDialogue:
    WaitButton
    CloseMessage
    ReleaseAll
    End

    .balign 4, 0
