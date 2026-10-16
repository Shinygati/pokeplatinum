#include "scrcmd_item.h"

#include <nitro.h>
#include <string.h>

#include "constants/heap.h"

#include "field/field_system.h"

#include "bag.h"
#include "field_script_context.h"
#include "inlines.h"
#include "item.h"
#include "unk_0205DFC4.h"
#include "constants/items.h"
#include "special_encounter.h"

BOOL ScrCmd_AddItem(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 item = ScriptContext_GetVar(ctx);
    u16 count = ScriptContext_GetVar(ctx);
    u16 *destVar = ScriptContext_GetVarPointer(ctx);

    *destVar = Bag_TryAddItem(SaveData_GetBag(fieldSystem->saveData), item, count, HEAP_ID_FIELD1);
    return FALSE;
}

BOOL ScrCmd_RemoveItem(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 item = ScriptContext_GetVar(ctx);
    u16 count = ScriptContext_GetVar(ctx);
    u16 *destVar = ScriptContext_GetVarPointer(ctx);

    *destVar = Bag_TryRemoveItem(SaveData_GetBag(fieldSystem->saveData), item, count, HEAP_ID_FIELD1);
    return FALSE;
}

BOOL ScrCmd_CanFitItem(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 item = ScriptContext_GetVar(ctx);
    u16 count = ScriptContext_GetVar(ctx);
    u16 *destVar = ScriptContext_GetVarPointer(ctx);

    *destVar = Bag_CanFitItem(SaveData_GetBag(fieldSystem->saveData), item, count, HEAP_ID_FIELD1);
    return FALSE;
}

BOOL ScrCmd_CheckItem(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 item = ScriptContext_GetVar(ctx);
    u16 count = ScriptContext_GetVar(ctx);
    u16 *destVar = ScriptContext_GetVarPointer(ctx);

    *destVar = Bag_CanRemoveItem(SaveData_GetBag(fieldSystem->saveData), item, count, HEAP_ID_FIELD2);
    return FALSE;
}

BOOL ScrCmd_GetItemQuantity(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 item = ScriptContext_GetVar(ctx);
    u16 *destVar = ScriptContext_GetVarPointer(ctx);

    *destVar = Bag_GetItemQuantity(SaveData_GetBag(fieldSystem->saveData), item, HEAP_ID_FIELD2);
    return FALSE;
}

BOOL ScrCmd_IsItemTMHM(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 item = ScriptContext_GetVar(ctx);
    u16 *destVar = ScriptContext_GetVarPointer(ctx);

    *destVar = Item_IsTMHM(item);
    return FALSE;
}

BOOL ScrCmd_GetItemPocket(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    u16 item = ScriptContext_GetVar(ctx);
    u16 *pocket = ScriptContext_GetVarPointer(ctx);

    *pocket = (u16)Item_LoadParam(item, ITEM_PARAM_FIELD_POCKET, HEAP_ID_FIELD2);
    return FALSE;
}

BOOL ScrCmd_Dummy081(ScriptContext *ctx)
{
    return FALSE;
}

BOOL ScrCmd_Dummy082(ScriptContext *ctx)
{
    return FALSE;
}


BOOL ScrCmd_UseStrongestRepel(ScriptContext *ctx)
{
    FieldSystem *fieldSystem = ctx->fieldSystem;
    SaveData *saveData = fieldSystem->saveData;
    Bag *bag = SaveData_GetBag(saveData);
    u16 item = ITEM_NONE;
    u16 *result = ScriptContext_GetVarPointer(ctx);
    u8 *repelSteps;

    if (Bag_CanRemoveItem(bag, ITEM_MAX_REPEL, 1, HEAP_ID_FIELD1)) {
        item = ITEM_MAX_REPEL;
    } else if (Bag_CanRemoveItem(bag, ITEM_SUPER_REPEL, 1, HEAP_ID_FIELD1)) {
        item = ITEM_SUPER_REPEL;
    } else if (Bag_CanRemoveItem(bag, ITEM_REPEL, 1, HEAP_ID_FIELD1)) {
        item = ITEM_REPEL;
    }

    if (item == ITEM_NONE) {
        *result = FALSE;
        return FALSE;
    }

    if (Bag_TryRemoveItem(bag, item, 1, HEAP_ID_FIELD1) == FALSE) {
        *result = FALSE;
        return FALSE;
    }

    repelSteps = SpecialEncounter_GetRepelSteps(
        SaveData_GetSpecialEncounters(saveData));

    *repelSteps = (u8)Item_LoadParam(
        item, ITEM_PARAM_EFFECT_PARAM, HEAP_ID_FIELD1);

    *result = TRUE;
    return FALSE;
}
