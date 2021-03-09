#include "dynos.cpp.h"
extern "C" {
#include "level_commands.h"
#include "game/game_init.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
#include "levels/intro/header.h"
}

//
// Data
//

static bool sDynosIsLevelEntry = false;
static s32  sDynosEndingTimer  = -1;

//
// Routines
//

static Array<void (*)(void)> &DynOS_GetRoutines(u8 aType) {
    static Array<void (*)(void)> sDynosRoutines[3];
    return sDynosRoutines[aType];
}

static void DynOS_ExecuteRoutines(u8 aType) {
    Array<void (*)(void)> &_Routines = DynOS_GetRoutines(aType);
    for (auto _Routine : _Routines) {
        _Routine();
    }
}

void DynOS_AddRoutine(u8 aType, void *aRoutine) {
    Array<void (*)(void)> &_Routines = DynOS_GetRoutines(aType);
    for (auto _Routine : _Routines) {
        if (_Routine == aRoutine) {
            return;
        }
    }
    _Routines.Add((void (*)(void)) aRoutine);
}

//
// Level Command stuff
//

static void *DynOS_CheckLevelEntry(void *aCmd) {
    static const uintptr_t sLevelEntryCmd[] = { CALL(0, lvl_init_or_update) };
    sDynosIsLevelEntry |= (memcmp(aCmd, sLevelEntryCmd, sizeof(sLevelEntryCmd)) == 0);
    return NULL;
}

static void *DynOS_CheckReturnToMainMenu(void *aCmd) {
    static const uintptr_t sEndingMarioThankCmd[] = { CALL(0, lvl_play_the_end_screen_sound) };
    static const uintptr_t sReturnToMainMenuCmd[] = { EXECUTE(0x14, _introSegmentRomStart, _introSegmentRomEnd, level_intro_2) };
    if ((sDynosEndingTimer == -1) && (memcmp(aCmd, sEndingMarioThankCmd, sizeof(sEndingMarioThankCmd)) == 0)) {
        sDynosEndingTimer = 450;
    } else if (sDynosEndingTimer == 0) {
        sDynosEndingTimer = -1;
        return (void *) sReturnToMainMenuCmd;
    }
    return NULL;
}

static void DynOS_EndingReturnToMainMenu() {
    if (sDynosEndingTimer == 150) {
        if ((gPlayer1Controller->buttonPressed & A_BUTTON) || (gPlayer1Controller->buttonPressed & START_BUTTON)) {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 90, 0x00, 0x00, 0x00);
            sDynosEndingTimer = 149;
        }
    } else if (sDynosEndingTimer > 0) {
        sDynosEndingTimer--;
    }
}

//
// Init
//

AT_STARTUP void DynOS_Init() {
    DynOS_Opt_Init();
}

//
// Update
//

void DynOS_UpdateOpt(void *aPad) {
    if (sDynosIsLevelEntry) {
        DynOS_Warp_SetParam(gCurrLevelNum, -1);
        DynOS_ExecuteRoutines(DYNOS_ROUTINE_LEVEL_ENTRY);
        sDynosIsLevelEntry = false;
    }
    DynOS_Opt_Update((OSContPad *) aPad);
    DynOS_ExecuteRoutines(DYNOS_ROUTINE_OPT_UPDATE);
    gPrevFrameObjectCount = 0;
}

void *DynOS_UpdateCmd(void *aCmd) {
    void *_Cmd = NULL;
    if (!_Cmd) _Cmd = DynOS_CheckLevelEntry(aCmd);
    if (!_Cmd) _Cmd = DynOS_Warp_Update(aCmd, sDynosIsLevelEntry);
    if (!_Cmd) _Cmd = DynOS_CheckReturnToMainMenu(aCmd);
    return _Cmd;
}

void DynOS_UpdateGfx() {
    DynOS_Gfx_Update();
    DynOS_ExecuteRoutines(DYNOS_ROUTINE_GFX_UPDATE);
    DynOS_EndingReturnToMainMenu();
}
