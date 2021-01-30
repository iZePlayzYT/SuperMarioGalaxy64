#ifndef DYNOS_H
#define DYNOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <dirent.h>
#include <SDL2/SDL.h>
#ifdef __cplusplus
#include <new>
#include <utility>
#include <string>
extern "C" {
#endif
#include "types.h"
#include "config.h"
#include "engine/math_util.h"
#include "pc/configfile.h"
#include "pc/fs/fs.h"
#undef STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#ifdef __cplusplus
}
#endif

//
// DynOS specs
//

#define DYNOS_FOLDER            "dynos"
#define DYNOS_GFX_FOLDER        DYNOS_FOLDER "/gfx"
#define DYNOS_AUDIO_FOLDER      DYNOS_FOLDER "/audio"
#define DYNOS_PACKS_FOLDER      DYNOS_FOLDER "/packs"
#define DYNOS_CONFIG_FILENAME   "DynOSconfig.cfg"

//
// Utils
//

#define AT_STARTUP              __attribute__((constructor))
#define AT_EXIT                 __attribute__((destructor))
#define EXPAND(...)             __VA_ARGS__

//
// Routines
//

enum {
    DYNOS_ROUTINE_OPT_UPDATE,  // Executed once per frame, before running the level script
    DYNOS_ROUTINE_GFX_UPDATE,  // Executed once per frame, before rendering the scene
    DYNOS_ROUTINE_LEVEL_ENTRY, // Executed at the very start of a level
};
typedef void (*DynosRoutine)(void *);

//
// Level Script
//

enum {
    DYNOS_LEVEL_SCRIPT_CONTINUE,
    DYNOS_LEVEL_SCRIPT_NEXT_CMD,
    DYNOS_LEVEL_SCRIPT_RETURN,
    DYNOS_LEVEL_SCRIPT_STOP,
};

//
// Cross-compatibility
// There are different function/struct names and values between Ex-Alo, Ex-Nightly and Render96
//

#ifdef __cplusplus
extern "C" {
#endif

//
// Repos/Branches
//

#if defined(CHEATS_ACTIONS) /* Ex-Alo */

// Files
#include "sounds.h"
#include "game/cheats.h"

// Macros
#define UKIKI_TYPE_CAP                  UKIKI_CAP

// Levels
#define level_intro_1                   level_intro_splash_screen
#define level_intro_2                   level_intro_mario_head_regular
#define level_intro_3                   level_intro_mario_head_dizzy

// Animation
#define AnimInfoStruct                  AnimInfo
#define mAreaIndex                      areaIndex
#define mActiveAreaIndex                activeAreaIndex
#define mAnimInfo                       animInfo
#define mAnimYTransDivisor              animYTransDivisor
#define mStartFrame                     startFrame
#define mLoopStart                      loopStart
#define mLoopEnd                        loopEnd
#define mUnusedBoneCount                unusedBoneCount

// Audio
#define gGlobalSoundArgs                gGlobalSoundSource
#define sAcousticReachPerLevel          sLevelAcousticReaches
#define music_fade_out                  seq_player_fade_out
#define music_lower_volume              seq_player_lower_volume
#define music_unlower_volume            seq_player_unlower_volume
#define music_soften()                  seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40)
#define music_unsoften()                seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60)
#define audio_mute                      set_audio_muted
#define sound_stop                      stop_sound
#define sound_stop_from_source          stop_sounds_from_source
#define sound_stop_in_continuous_banks  stop_sounds_in_continuous_banks
#define sound_set_moving_speed          set_sound_moving_speed

#else /* Ex-Nightly, Render96ex-Alpha */

// Files
#include "audio_defines.h"
#include "pc/cheats.h"

// Macros
#define UKIKI_TYPE_CAP                  UKIKI_HAT

// Levels
#define level_intro_1                   level_intro_entry_1
#define level_intro_2                   level_intro_entry_2
#define level_intro_3                   level_intro_entry_3

// Animation
#define AnimInfoStruct                  GraphNodeObject_sub
#define mAreaIndex                      unk18
#define mActiveAreaIndex                unk19
#define mAnimInfo                       unk38
#define mAnimYTransDivisor              unk02
#define mStartFrame                     unk04
#define mLoopStart                      unk06
#define mLoopEnd                        unk08
#define mUnusedBoneCount                unk0A

// Audio
#define gGlobalSoundArgs                gDefaultSoundArgs
#define sAcousticReachPerLevel          D_80332028
#define music_fade_out                  sequence_player_fade_out
#define music_lower_volume              func_8031FFB4
#define music_unlower_volume            sequence_player_unlower
#define music_soften()                  func_8031FFB4(SEQ_PLAYER_LEVEL, 60, 40)
#define music_unsoften()                sequence_player_unlower(SEQ_PLAYER_LEVEL, 60)
#define audio_mute                      set_sound_disabled
#define sound_stop                      func_803205E8
#define sound_stop_from_source          func_803206F8
#define sound_stop_in_continuous_banks  func_80320890
#define sound_set_moving_speed          func_80320A4C

#endif

//
// Luigi custom code
//

#ifdef RENDER_96_LUIGI

#define IS_PLAYER_LUIGI                 (getCharacterType() == LUIGI)
#define HUD_DISPLAY_FLAG_LUIGI_KEYS     HUD_DISPLAY_FLAG_KEYS
#define MODEL_ID_LUIGIS_CAP             MODEL_LUIGIS_CAP
#define MODEL_ID_LUIGIS_METAL_CAP       MODEL_LUIGIS_METAL_CAP
#define MODEL_ID_LUIGIS_WING_CAP        MODEL_LUIGIS_WING_CAP
#define MODEL_ID_LUIGIS_WING_METAL_CAP  MODEL_LUIGIS_WINGED_METAL_CAP

#define IS_PLAYER_WARIO                 (getCharacterType() == WARIO)
#define MODEL_ID_WARIOS_CAP             MODEL_WARIOS_CAP
#define MODEL_ID_WARIOS_METAL_CAP       MODEL_WARIOS_METAL_CAP
#define MODEL_ID_WARIOS_WING_CAP        MODEL_WARIOS_WING_CAP
#define MODEL_ID_WARIOS_WING_METAL_CAP  MODEL_WARIOS_WINGED_METAL_CAP

#define GET_PLAYER                      (IS_PLAYER_LUIGI ? 1 : (IS_PLAYER_WARIO ? 2 : 0))
#define GET_PLAYERS_NORMAL_CAP          (IS_PLAYER_LUIGI ? MODEL_ID_LUIGIS_CAP : (IS_PLAYER_WARIO ? MODEL_ID_WARIOS_CAP : MODEL_MARIOS_CAP))
#define GET_PLAYERS_METAL_CAP           (IS_PLAYER_LUIGI ? MODEL_ID_LUIGIS_METAL_CAP : (IS_PLAYER_WARIO ? MODEL_ID_WARIOS_METAL_CAP : MODEL_MARIOS_METAL_CAP))
#define GET_PLAYERS_WING_CAP            (IS_PLAYER_LUIGI ? MODEL_ID_LUIGIS_WING_CAP : (IS_PLAYER_WARIO ? MODEL_ID_WARIOS_WING_CAP : MODEL_MARIOS_WING_CAP))
#define GET_PLAYERS_WING_METAL_CAP      (IS_PLAYER_LUIGI ? MODEL_ID_LUIGIS_WING_METAL_CAP : (IS_PLAYER_WARIO ? MODEL_ID_WARIOS_WING_METAL_CAP : MODEL_MARIOS_WINGED_METAL_CAP))
#define GET_PLAYERS_CAP(metal, wing)    ((metal) ? ((wing) ? GET_PLAYERS_WING_METAL_CAP : GET_PLAYERS_METAL_CAP) : ((wing) ? GET_PLAYERS_WING_CAP : GET_PLAYERS_NORMAL_CAP))

#else

#define IS_PLAYER_LUIGI                 (0)
#define HUD_DISPLAY_FLAG_LUIGI_KEYS     0
#define MODEL_ID_LUIGIS_CAP             0xFF
#define MODEL_ID_LUIGIS_METAL_CAP       0xFF
#define MODEL_ID_LUIGIS_WING_CAP        0xFF
#define MODEL_ID_LUIGIS_WING_METAL_CAP  0xFF

#define IS_PLAYER_WARIO                 (0)
#define MODEL_ID_WARIOS_CAP             0xFF
#define MODEL_ID_WARIOS_METAL_CAP       0xFF
#define MODEL_ID_WARIOS_WING_CAP        0xFF
#define MODEL_ID_WARIOS_WING_METAL_CAP  0xFF

#define GET_PLAYER                      (0)
#define GET_PLAYERS_NORMAL_CAP          (MODEL_MARIOS_CAP)
#define GET_PLAYERS_METAL_CAP           (MODEL_MARIOS_METAL_CAP)
#define GET_PLAYERS_WING_CAP            (MODEL_MARIOS_WING_CAP)
#define GET_PLAYERS_WING_METAL_CAP      (MODEL_MARIOS_WINGED_METAL_CAP)
#define GET_PLAYERS_CAP(metal, wing)    ((metal) ? ((wing) ? GET_PLAYERS_WING_METAL_CAP : GET_PLAYERS_METAL_CAP) : ((wing) ? GET_PLAYERS_WING_CAP : GET_PLAYERS_NORMAL_CAP))

#endif

//
// Extended bounds
//

#define MAX_CELLS       ((2 * LEVEL_BOUNDARY_MAX) / CELL_SIZE)
#define CELL_BITS       (MAX_CELLS - 1)
#define FLOOR_DEFAULT   -11000.f
#define CEIL_DEFAULT    +20000.f

//
// Some QoL changes
//

// How are we supposed to open the DynOS menu with this shit on?
#ifdef Z_TRIG_EXTRA_ACT
#undef Z_TRIG_EXTRA_ACT
#define Z_TRIG_EXTRA_ACT 0
#endif

#ifdef __cplusplus
}
#endif

#endif