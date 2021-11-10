#include "mario_cheats.h"
#include "data/r96/r96_c_includes.h"
#include "text/text-loader.h"
#include "actors/common0.h"
#include "actors/common1.h"
#include "actors/group0.h"
#include "actors/group1.h"
#include "actors/group2.h"
#include "actors/group3.h"
#include "actors/group4.h"
#include "actors/group5.h"
#include "actors/group6.h"
#include "actors/group7.h"
#include "actors/group8.h"
#include "actors/group9.h"
#include "actors/group10.h"
#include "actors/group11.h"
#include "actors/group12.h"
#include "actors/group13.h"
#include "actors/group14.h"
#include "actors/group15.h"
#include "actors/group16.h"
#include "actors/group17.h"
#include "levels/hmc/header.h"
#include "levels/ssl/header.h"
#include "geo_commands.h"

static const s32 sModifierValues[] = { 1, 2, 3, 4, 5 };
static const f32 sSizeValues[] = { 1.f, 2.f, 3.f, 4.f, 0.f, 0.25f, 0.5f, 0.75f };
static const char *sSpambaStrings[] = {
    "TEXT_OPT_CHEAT_SPAMBA_YELLOW_COIN",
    "TEXT_OPT_CHEAT_SPAMBA_RED_COIN",
    "TEXT_OPT_CHEAT_SPAMBA_BLUE_COIN",
    "TEXT_OPT_CHEAT_SPAMBA_MUSHROOM_1UP",
    "TEXT_OPT_CHEAT_SPAMBA_STAR_1",
    "TEXT_OPT_CHEAT_SPAMBA_STAR_2",
    "TEXT_OPT_CHEAT_SPAMBA_STAR_3",
    "TEXT_OPT_CHEAT_SPAMBA_STAR_4",
    "TEXT_OPT_CHEAT_SPAMBA_STAR_5",
    "TEXT_OPT_CHEAT_SPAMBA_STAR_6",
    "TEXT_OPT_CHEAT_SPAMBA_STAR_7",
    "TEXT_OPT_CHEAT_SPAMBA_WING_CAP",
    "TEXT_OPT_CHEAT_SPAMBA_VANISH_CAP",
    "TEXT_OPT_CHEAT_SPAMBA_METAL_CAP",
    "TEXT_OPT_CHEAT_SPAMBA_NORMAL_CAP",
    "TEXT_OPT_CHEAT_SPAMBA_RECOVERY_HEART",
    "TEXT_OPT_CHEAT_SPAMBA_GOOMBA",
    "TEXT_OPT_CHEAT_SPAMBA_GOOMBA_TRIPLET",
    "TEXT_OPT_CHEAT_SPAMBA_KOOPA",
    "TEXT_OPT_CHEAT_SPAMBA_KOOPA_SHELL",
    "TEXT_OPT_CHEAT_SPAMBA_BOBOMB",
    "TEXT_OPT_CHEAT_SPAMBA_BOBOMB_BUDDY",
    "TEXT_OPT_CHEAT_SPAMBA_CHAIN_CHOMP",
    "TEXT_OPT_CHEAT_SPAMBA_PIRANHA_PLANT",
    "TEXT_OPT_CHEAT_SPAMBA_PIRANHA_PLANT_FIRE",
    "TEXT_OPT_CHEAT_SPAMBA_WHOMP",
    "TEXT_OPT_CHEAT_SPAMBA_SPINDRIFT",
    "TEXT_OPT_CHEAT_SPAMBA_BOO",
    "TEXT_OPT_CHEAT_SPAMBA_MR_I",
    "TEXT_OPT_CHEAT_SPAMBA_BOOK",
    "TEXT_OPT_CHEAT_SPAMBA_SCUTTLEBUG",
    "TEXT_OPT_CHEAT_SPAMBA_SWOOP",
    "TEXT_OPT_CHEAT_SPAMBA_SNUFIT",
    "TEXT_OPT_CHEAT_SPAMBA_BULLY",
    "TEXT_OPT_CHEAT_SPAMBA_CHILL_BULLY",
    "TEXT_OPT_CHEAT_SPAMBA_MOTOS",
    "TEXT_OPT_CHEAT_SPAMBA_BLARGG",
    "TEXT_OPT_CHEAT_SPAMBA_POKEY",
    "TEXT_OPT_CHEAT_SPAMBA_FLYGUY",
    "TEXT_OPT_CHEAT_SPAMBA_MONEYBAG",
    "TEXT_OPT_CHEAT_SPAMBA_CHUCKYA",
    "TEXT_OPT_CHEAT_SPAMBA_SKEETER",
    "TEXT_OPT_CHEAT_SPAMBA_LAKITU",
    "TEXT_OPT_CHEAT_SPAMBA_SPINY",
    "TEXT_OPT_CHEAT_SPAMBA_BOWLING_BALL",
    "TEXT_OPT_CHEAT_SPAMBA_CLAM",
    "TEXT_OPT_CHEAT_SPAMBA_MR_BLIZZARD",
    "TEXT_OPT_CHEAT_SPAMBA_HAUNTED_CHAIR",
    "TEXT_OPT_CHEAT_SPAMBA_MAD_PIANO",
    "TEXT_OPT_CHEAT_SPAMBA_BIG_BOULDER",
    "TEXT_OPT_CHEAT_SPAMBA_FIRE_SPITTER",
    "TEXT_OPT_CHEAT_SPAMBA_FLAMETHROWER",
    "TEXT_OPT_CHEAT_SPAMBA_BOUNCING_FIREBALL",
    "TEXT_OPT_CHEAT_SPAMBA_CIRCLING_AMP",
    "TEXT_OPT_CHEAT_SPAMBA_HOMING_AMP",
    "TEXT_OPT_CHEAT_SPAMBA_HEAVE_HO",
    "TEXT_OPT_CHEAT_SPAMBA_KING_BOBOMB",
    "TEXT_OPT_CHEAT_SPAMBA_KING_WHOMP",
    "TEXT_OPT_CHEAT_SPAMBA_BIG_BOO",
    "TEXT_OPT_CHEAT_SPAMBA_BIG_BULLY",
    "TEXT_OPT_CHEAT_SPAMBA_BIG_CHILL_BULLY",
    "TEXT_OPT_CHEAT_SPAMBA_EYEROCK",
    "TEXT_OPT_CHEAT_SPAMBA_WIGGLER",
    "TEXT_OPT_CHEAT_SPAMBA_BOWSER",
    "TEXT_OPT_CHEAT_SPAMBA_HOOT",
    "TEXT_OPT_CHEAT_SPAMBA_PENGUIN",
    "TEXT_OPT_CHEAT_SPAMBA_MOTHER_PENGUIN",
    "TEXT_OPT_CHEAT_SPAMBA_KLEPTO",
    "TEXT_OPT_CHEAT_SPAMBA_UKIKI",
    "TEXT_OPT_CHEAT_SPAMBA_TOAD",
    "TEXT_OPT_CHEAT_SPAMBA_SIGNPOST",
    "TEXT_OPT_CHEAT_SPAMBA_CANNON",
    "TEXT_OPT_CHEAT_SPAMBA_BREAKABLE_BOX",
    "TEXT_OPT_CHEAT_SPAMBA_BREAKABLE_BOX_SMALL",
    "TEXT_OPT_CHEAT_SPAMBA_CRAZY_BOX",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_WING_CAP",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_METAL_CAP",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_VANISH_CAP",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_KOOPA_SHELL",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_ONE_COIN",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_THREE_COINS",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_TEN_COINS",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_MUSHROOM_1UP",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_STAR_1",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_STAR_2",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_STAR_3",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_STAR_4",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_STAR_5",
    "TEXT_OPT_CHEAT_SPAMBA_EXCLAMATION_BOX_STAR_6",
    "TEXT_OPT_CHEAT_SPAMBA_METAL_BOX",
    "TEXT_OPT_CHEAT_SPAMBA_THWOMP",
    "TEXT_OPT_CHEAT_SPAMBA_GRINDEL",
    "TEXT_OPT_CHEAT_SPAMBA_GRINDEL_HORIZONTAL",
    "TEXT_OPT_CHEAT_SPAMBA_SPINDEL",
    "TEXT_OPT_CHEAT_SPAMBA_TOX_BOX",
};

static s16 sButtonPressed = 0;
static s16 sButtonDown = 0;

s32 cheats_moon_jump(struct MarioState *m) {
#if !defined(OMM_DEFINES_H)
    if (Cheats.EnableCheats && Cheats.MoonJump) {
        if (sButtonDown & L_TRIG) {
            m->vel[1] = 25.f;
            return TRUE;
        }
    }
#endif
    return FALSE;
}

s32 cheats_moon_gravity(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.MoonGravity) {
        if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_AIRBORNE) {
            if (m->action == ACT_FREEFALL || m->action == ACT_LONG_JUMP) {
                m->vel[1] += 1.f;
            } else {
                m->vel[1] += 2.f;
            }
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_super_copter(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.SuperCopter) {
        if (sButtonDown & A_BUTTON) {
            m->vel[1] = 30.f;
            set_mario_action(m, ACT_TWIRLING, 0);
            return TRUE;
        }
        
        // You can break free by starting a groud pound with Z
        if (m->action == ACT_TWIRLING && (sButtonPressed & Z_TRIG)) {
            set_mario_action(m, ACT_GROUND_POUND, 0);
        }
    }
    return FALSE;
}

s32 cheats_debug_move(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.DebugMove) {
        set_mario_action(m, ACT_DEBUG_FREE_MOVE, 0);
        Cheats.DebugMove = false;
        return TRUE;
    }
    return FALSE;
}

s32 cheats_god_mode(struct MarioState *m) {
#if !defined(OMM_DEFINES_H)
    if (Cheats.EnableCheats && Cheats.GodMode) {
        m->health = 0x880;
        m->healCounter = 0;
        m->hurtCounter = 0;
        return TRUE;
    }
#endif
    return FALSE;
}

s32 cheats_infinite_lives(struct MarioState *m) {
#if !defined(OMM_DEFINES_H)
    if (Cheats.EnableCheats && Cheats.InfiniteLives) {
        m->numLives = 99;
    }
#endif
    return FALSE;
}

s32 cheats_responsive(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.Responsive) {
        m->faceAngle[1] = m->intendedYaw;
        return TRUE;
    }
    return FALSE;
}

s32 cheats_speed_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        return sModifierValues[Cheats.SpeedModifier];
    }
    return 1;
}

s32 cheats_jump_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        if (m->vel[1] > 0.f) {
            return sModifierValues[Cheats.JumpModifier];
        }
    }
    return 1;
}

s32 cheats_swim_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        return sModifierValues[Cheats.SwimModifier];
    }
    return 1;
}

s32 cheats_size_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        f32 size = sSizeValues[Cheats.SizeModifier];
        if (Cheats.PlayAs == 3 || Cheats.PlayAs == 5) {
            size *= 1.5f;
        }
        m->marioObj->header.gfx.scale[0] *= size;
        m->marioObj->header.gfx.scale[1] *= size;
        m->marioObj->header.gfx.scale[2] *= size;
        return TRUE;
    }
    return FALSE;
}

struct SpambaData {
    const BehaviorScript *behavior;
    const GeoLayout *geo;
    f32 relX, relY, relZ;
    s32 behParams;
    bool dropToFloor;
    bool faceMario;
    s32 model0, model1, model2;
};

static const struct SpambaData sSpambaData[] = {
    { bhvSpambaYellowCoin,          yellow_coin_geo,        0,   80,   0, 0x00000000, 0, 0 }, // SPAMBA_YELLOW_COIN,
    { bhvSpambaRedCoin,             red_coin_geo,           0,   80,   0, 0x00000000, 0, 0 }, // SPAMBA_RED_COIN,
    { bhvSpambaBlueCoin,            blue_coin_geo,          0,   80,   0, 0x00000000, 0, 0 }, // SPAMBA_BLUE_COIN,
    { bhvHidden1upInPole,           mushroom_1up_geo,       0,  200,   0, 0x00000000, 0, 0 }, // SPAMBA_MUSHROOM_1UP,
    { bhvSpawnedStarNoLevelExit,    star_geo,               0,  300,   0, 0x00000000, 0, 0 }, // SPAMBA_STAR_1,
    { bhvSpawnedStarNoLevelExit,    star_geo,               0,  300,   0, 0x01000000, 0, 0 }, // SPAMBA_STAR_2,
    { bhvSpawnedStarNoLevelExit,    star_geo,               0,  300,   0, 0x02000000, 0, 0 }, // SPAMBA_STAR_3,
    { bhvSpawnedStarNoLevelExit,    star_geo,               0,  300,   0, 0x03000000, 0, 0 }, // SPAMBA_STAR_4,
    { bhvSpawnedStarNoLevelExit,    star_geo,               0,  300,   0, 0x04000000, 0, 0 }, // SPAMBA_STAR_5,
    { bhvSpawnedStarNoLevelExit,    star_geo,               0,  300,   0, 0x05000000, 0, 0 }, // SPAMBA_STAR_6,
    { bhvSpawnedStarNoLevelExit,    star_geo,               0,  300,   0, 0x06000000, 0, 0 }, // SPAMBA_STAR_7,
    { bhvWingCap,                   marios_wing_cap_geo,    0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_WING_CAP,
    { bhvVanishCap,                 marios_cap_geo,         0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_VANISH_CAP,
    { bhvMetalCap,                  marios_metal_cap_geo,   0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_METAL_CAP,
    { bhvNormalCap,                 marios_cap_geo,         0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_NORMAL_CAP,
    { bhvRecoveryHeart,             heart_geo,              0,   80,   0, 0x00000000, 0, 0 }, // SPAMBA_RECOVERY_HEART,

    { bhvGoomba,                    goomba_geo,             0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_GOOMBA,
    { bhvGoombaTripletSpawner,      NULL,                   0,   40,   0, 0x00000000, 1, 0 }, // SPAMBA_GOOMBA_TRIPLET,
    { bhvKoopa,                     koopa_with_shell_geo,   0,   40, 300, 0x00010000, 1, 1, 1, 2, 3 }, // SPAMBA_KOOPA,
    { bhvKoopaShell,                koopa_shell_geo,        0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_KOOPA_SHELL,
    { bhvBobomb,                    black_bobomb_geo,       0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_BOBOMB,
    { bhvBobombBuddy,               bobomb_buddy_geo,       0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_BOBOMB_BUDDY,
    { bhvChainChomp,                chain_chomp_geo,        0,   40, 500, 0x00000000, 1, 1, 4, 5 }, // SPAMBA_CHAIN_CHOMP,
    { bhvPiranhaPlant,              piranha_plant_geo,      0,   40, 400, 0x00000000, 1, 1, 6, 7 }, // SPAMBA_PIRANHA_PLANT,
    { bhvFirePiranhaPlant,          piranha_plant_geo,      0,   40, 300, 0x00000000, 1, 1, 8 }, // SPAMBA_PIRANHA_PLANT_FIRE,
    { bhvSmallWhomp,                whomp_geo,              0,   40, 400, 0x00000000, 1, 1 }, // SPAMBA_WHOMP,
    { bhvSpindrift,                 spindrift_geo,          0,   40, 300, 0x00000000, 0, 1 }, // SPAMBA_SPINDRIFT,
    { bhvBoo,                       boo_geo,                0,   40, 300, 0x00000000, 0, 1, 9, 10 }, // SPAMBA_BOO,
    { bhvMrI,                       mr_i_geo,               0,   40, 300, 0x00000000, 1, 1, 11, 12 }, // SPAMBA_MR_I,
    { bhvFlyingBookend,             bookend_geo,            0,   40, 400, 0x00000000, 0, 1, 13 }, // SPAMBA_BOOK,
    { bhvScuttlebug,                scuttlebug_geo,         0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_SCUTTLEBUG,
    { bhvSwoop,                     swoop_geo,              0,  120, 300, 0x00000000, 0, 1 }, // SPAMBA_SWOOP,
    { bhvSnufit,                    snufit_geo,             0,  120, 300, 0x00000000, 0, 1, 14 }, // SPAMBA_SNUFIT,
    { bhvSmallBully,                bully_geo,              0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_BULLY,
    { bhvSmallBully,                chilly_chief_geo,       0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_CHILL_BULLY,
    { bhvMotos,                     motos_geo,              0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_MOTOS,
    { bhvFriendlyBlargg,            friendly_blargg_geo,    0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_BLARGG,
    { bhvPokey,                     NULL,                   0,   40, 300, 0x00000000, 1, 1, 15, 16 }, // SPAMBA_POKEY,
    { bhvFlyGuy,                    flyguy_geo,             0,   80, 300, 0x00000000, 0, 0, 8 }, // SPAMBA_FLYGUY,
    { bhvMoneybagHidden,            yellow_coin_geo,        0,   40, 300, 0x00000000, 1, 0, 17, 9 }, // SPAMBA_MONEYBAG,
    { bhvChuckya,                   chuckya_geo,            0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_CHUCKYA,
    { bhvSkeeter,                   skeeter_geo,            0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_SKEETER,
    { bhvEnemyLakitu,               enemy_lakitu_geo,       0,  120, 300, 0x00000000, 0, 1, 18, 19, 20 }, // SPAMBA_LAKITU,
    { bhvSpiny,                     spiny_geo,              0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_SPINY,
    
    { bhvFreeBowlingBall,           bowling_ball_geo,       0,   40, 400, 0x00000000, 0, 0 }, // SPAMBA_BOWLING_BALL,
    { bhvClamShell,                 clam_shell_geo,         0,   40, 400, 0x00000000, 1, 1, 21 }, // SPAMBA_CLAM,
    { bhvMrBlizzard,                mr_blizzard_geo,        0,   40, 300, 0x00000000, 1, 1, 22 }, // SPAMBA_MR_BLIZZARD,
    { bhvHauntedChair,              haunted_chair_geo,      0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_HAUNTED_CHAIR,
    { bhvMadPiano,                  mad_piano_geo,          0,   40, 400, 0x00000000, 1, 1 }, // SPAMBA_MAD_PIANO,
    { bhvBigBoulder,                hmc_geo_000548,         0,   40, 600, 0x00000000, 0, 0 }, // SPAMBA_BIG_BOULDER,
    { bhvFireSpitter,               bowling_ball_geo,       0,   40, 300, 0x00000000, 0, 1, 8 }, // SPAMBA_FIRE_SPITTER,
    { bhvFlamethrower,              NULL,                   0,   80, 300, 0x00000000, 0, 0, 23, 24 }, // SPAMBA_FLAMETHROWER,
    { bhvBouncingFireball,          NULL,                   0,   40, 300, 0x00000000, 0, 0, 23 }, // SPAMBA_BOUNCING_FIREBALL,
    { bhvCirclingAmp,               amp_geo,                0,   80, 400, 0x00000000, 0, 1 }, // SPAMBA_CIRCLING_AMP,
    { bhvHomingAmp,                 amp_geo,                0,   80, 300, 0x00000000, 0, 1 }, // SPAMBA_HOMING_AMP,
    { bhvHeaveHo,                   heave_ho_geo,           0,   40, 300, 0x00000000, 1, 0 }, // SPAMBA_HEAVE_HO,
    
    { bhvKingBobomb,                king_bobomb_geo,        0,   40, 600, 0x00000000, 1, 1 }, // SPAMBA_KING_BOBOMB,
    { bhvWhompKingBoss,             whomp_geo,              0,   40, 600, 0x01000000, 1, 1 }, // SPAMBA_KING_WHOMP,
    { bhvBalconyBigBoo,             boo_geo,                0,   40, 600, 0x02000000, 0, 1 }, // SPAMBA_BIG_BOO,
    { bhvBigBully,                  bully_boss_geo,         0,   40, 600, 0x03000000, 1, 1 }, // SPAMBA_BIG_BULLY,
    { bhvBigBully,                  chilly_chief_big_geo,   0,   40, 600, 0x04000000, 1, 1 }, // SPAMBA_BIG_CHILL_BULLY,
    { bhvEyerokBoss,                NULL,                   0,   40, 600, 0x05000000, 1, 1, 25, 26 }, // SPAMBA_EYEROCK,
    { bhvWigglerHead,               wiggler_head_geo,       0,   40, 600, 0x05000000, 1, 1, 27 }, // SPAMBA_WIGGLER,
    { bhvBowser,                    bowser_geo,             0,   40, 600, 0x00000000, 1, 1, 28, 29, 30 }, // SPAMBA_BOWSER,

    { bhvHoot,                      hoot_geo,               0,  200, 300, 0x00000000, 0, 1 }, // SPAMBA_HOOT,
    { bhvSmallPenguin,              penguin_geo,            0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_PENGUIN,
    { bhvTuxiesMother,              penguin_geo,            0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_MOTHER_PENGUIN,
    { bhvKlepto,                    klepto_geo,             0,  200, 300, 0x00000000, 0, 1 }, // SPAMBA_KLEPTO,
    { bhvUkiki,                     ukiki_geo,              0,   40, 300, 0x00010000, 1, 1 }, // SPAMBA_UKIKI,
    { bhvToadMessage,               toad_geo,               0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_TOAD,
    { bhvMessagePanel,              wooden_signpost_geo,    0,   40, 300, 0x00000000, 1, 1 }, // SPAMBA_SIGNPOST,

    { bhvCannon,                    NULL,                   0,  200,   0, 0x00000000, 0, 0, 31 }, // SPAMBA_CANNON,
    { bhvBreakableBox,              breakable_box_geo,      0, -200,   0, 0x00000000, 0, 0 }, // SPAMBA_BREAKABLE_BOX,
    { bhvBreakableBoxSmall,         breakable_box_geo,      0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_BREAKABLE_BOX_SMALL,
    { bhvJumpingBox,                breakable_box_geo,      0,   40, 300, 0x00000000, 0, 0 }, // SPAMBA_CRAZY_BOX,
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00000000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_WING_CAP, // 0
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00010000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_METAL_CAP, // 1
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00020000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_VANISH_CAP, // 2
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00030000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_KOOPA_SHELL, // 3
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00040000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_ONE_COIN, // 4 
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00050000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_THREE_COINS, // 5
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00060000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_TEN_COINS, // 6 
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00070000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_MUSHROOM_1UP, // 7
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x00080000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_1, // 8 
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x000A0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_2, // 10 
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x000B0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_3, // 11 
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x000C0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_4, // 12 
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x000D0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_5, // 13 
    { bhvExclamationBox,            exclamation_box_geo,    0,  300,   0, 0x000E0000, 0, 0, 32, 33, 34 }, // SPAMBA_EXCLAMATION_BOX_STAR_6, // 14
    { bhvPushableMetalBox,          metal_box_geo,          0, -307,   0, 0x00000000, 0, 0 }, // SPAMBA_METAL_BOX,
    { bhvThwomp,                    thwomp_geo,             0,   40, 400, 0x00000000, 1, 1 }, // SPAMBA_THWOMP,
    { bhvGrindel,                   ssl_geo_000734,         0,   40, 400, 0x00000000, 1, 1 }, // SPAMBA_GRINDEL,
    { bhvHorizontalGrindel,         ssl_geo_000734,         0,   40, 400, 0x00000000, 1, 0 }, // SPAMBA_GRINDEL_HORIZONTAL,
    { bhvSpindel,                   ssl_geo_000764,         0,  180, 300, 0x00010000, 0, 0 }, // SPAMBA_SPINDEL,
    { bhvToxBox,                    ssl_geo_000630,         0,    0, 300, 0x00000000, 0, 0 }, // SPAMBA_TOX_BOX,
};

// Exclamation point geo layout
static const GeoLayout exclamation_point_geo[] = {
    GEO_NODE_START(),
    GEO_OPEN_NODE(),
        GEO_DISPLAY_LIST(LAYER_ALPHA, exclamation_box_outline_seg8_dl_08025F08),
    GEO_CLOSE_NODE(),
    GEO_END(),
};

static void cheats_spamba_load_model_graph_node(s32 model) {
    const GeoLayout *geo = NULL;
    if (model != 0) {
        s32 modelId = 0xFF;
        switch (model) {
            case  1: modelId = MODEL_KOOPA_WITHOUT_SHELL;       geo = koopa_without_shell_geo; break;
            case  2: modelId = MODEL_KOOPA_WITH_SHELL;          geo = koopa_with_shell_geo; break;
            case  3: modelId = MODEL_KOOPA_SHELL;               geo = koopa_shell_geo; break;
            case  4: modelId = MODEL_METALLIC_BALL;             geo = metallic_ball_geo; break;
            case  5: modelId = MODEL_WOODEN_POST;               geo = wooden_post_geo; break;
            case  6: modelId = MODEL_BUBBLE;                    geo = bubble_geo; break;
            case  7: modelId = MODEL_PURPLE_MARBLE;             geo = purple_marble_geo; break;
            case  8: modelId = MODEL_RED_FLAME_SHADOW;          geo = red_flame_shadow_geo; break;
            case  9: modelId = MODEL_YELLOW_COIN;               geo = yellow_coin_geo; break;
            case 10: modelId = MODEL_BLUE_COIN;                 geo = blue_coin_geo; break;
            case 11: modelId = MODEL_MR_I;                      geo = mr_i_geo; break;
            case 12: modelId = MODEL_MR_I_IRIS;                 geo = mr_i_iris_geo; break;
            case 13: modelId = MODEL_BOOKEND_PART;              geo = bookend_part_geo; break;
            case 14: modelId = MODEL_BOWLING_BALL;              geo = bowling_ball_geo; break;
            case 15: modelId = MODEL_POKEY_HEAD;                geo = pokey_head_geo; break;
            case 16: modelId = MODEL_POKEY_BODY_PART;           geo = pokey_body_part_geo; break;
            case 17: modelId = MODEL_MONEYBAG;                  geo = moneybag_geo; break;
            case 18: modelId = MODEL_MIST;                      geo = mist_geo; break;
            case 19: modelId = MODEL_SPINY_BALL;                geo = spiny_ball_geo; break;
            case 20: modelId = MODEL_SPINY;                     geo = spiny_geo; break;
            case 21: modelId = MODEL_BUBBLE;                    geo = bubble_geo; break;
            case 22: modelId = MODEL_WHITE_PARTICLE;            geo = white_particle_geo; break;
            case 23: modelId = MODEL_RED_FLAME;                 geo = red_flame_geo; break;
            case 24: modelId = MODEL_BLUE_FLAME;                geo = blue_flame_geo; break;
            case 25: modelId = MODEL_EYEROK_LEFT_HAND;          geo = eyerok_left_hand_geo; break;
            case 26: modelId = MODEL_EYEROK_RIGHT_HAND;         geo = eyerok_right_hand_geo; break;
            case 27: modelId = MODEL_WIGGLER_BODY;              geo = wiggler_body_geo; break;
            case 28: modelId = MODEL_BOWSER_BOMB_CHILD_OBJ;     geo = bowser_bomb_geo; break;
            case 29: modelId = MODEL_BOWSER_FLAMES;             geo = bowser_flames_geo; break;
            case 30: modelId = MODEL_BOWSER_WAVE;               geo = invisible_bowser_accessory_geo; break;
            case 31: modelId = MODEL_CANNON_BARREL;             geo = cannon_barrel_geo; break;
            case 32: modelId = MODEL_EXCLAMATION_BOX;           geo = exclamation_box_geo; break;
            case 33: modelId = MODEL_EXCLAMATION_BOX_OUTLINE;   geo = exclamation_box_outline_geo; break;
            case 34: modelId = MODEL_EXCLAMATION_POINT;         geo = exclamation_point_geo; break;
        }
        gLoadedGraphNodes[modelId] = dynos_geo_get_graph_node(geo, true);
    }
}

s32 cheats_spamba(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.Spamba) {
        u32 keyPressed = controller_get_raw_key();
        if (keyPressed != VK_INVALID) {

            // Select previous object
            if (keyPressed == CheatsControls.SpambaControls[0]) {
                Cheats.SpambaIndex = (Cheats.SpambaIndex + SPAMBA_COUNT - 1) % SPAMBA_COUNT;
                play_sound(SOUND_MENU_CHANGE_SELECT, gDefaultSoundArgs);
            }

            // Select next object
            if (keyPressed == CheatsControls.SpambaControls[1]) {
                Cheats.SpambaIndex = (Cheats.SpambaIndex + SPAMBA_COUNT + 1) % SPAMBA_COUNT;
                play_sound(SOUND_MENU_CHANGE_SELECT, gDefaultSoundArgs);
            }

            // Spawn selected object
            if (keyPressed == CheatsControls.SpambaControls[2]) {
                struct Object *obj = spawn_object_relative(0,
                    sSpambaData[Cheats.SpambaIndex].relX,
                    sSpambaData[Cheats.SpambaIndex].relY,
                    sSpambaData[Cheats.SpambaIndex].relZ,
                    m->marioObj, MODEL_NONE,
                    sSpambaData[Cheats.SpambaIndex].behavior
                );
                obj->oBehParams = sSpambaData[Cheats.SpambaIndex].behParams;
                obj->oBehParams2ndByte = ((sSpambaData[Cheats.SpambaIndex].behParams >> 16) & 0xFF);
                obj->header.gfx.sharedChild = dynos_geo_get_graph_node(sSpambaData[Cheats.SpambaIndex].geo, true);
                if (sSpambaData[Cheats.SpambaIndex].faceMario) {
                    obj_set_angle(obj, 0, m->faceAngle[1] + 0x8000, 0);
                } else {
                    obj_set_angle(obj, 0, m->faceAngle[1], 0);
                }
                if (sSpambaData[Cheats.SpambaIndex].dropToFloor) {
                    obj->oPosY = find_floor_height(obj->oPosX, obj->oPosY + 160.f, obj->oPosZ);
                    obj->oMoveFlags |= OBJ_MOVE_ON_GROUND;
                }
                cheats_spamba_load_model_graph_node(sSpambaData[Cheats.SpambaIndex].model0);
                cheats_spamba_load_model_graph_node(sSpambaData[Cheats.SpambaIndex].model1);
                cheats_spamba_load_model_graph_node(sSpambaData[Cheats.SpambaIndex].model2);
                
                switch (Cheats.SpambaIndex) {
                    case SPAMBA_YELLOW_COIN:
                    case SPAMBA_RED_COIN:
                    case SPAMBA_BLUE_COIN: {
                        obj->oForwardVel = random_float() * 15.f;
                        obj->oVelY = random_float() * 30.f + 20.f;
                        obj->oMoveAngleYaw = random_u16();
                    } break;

                    case SPAMBA_STAR_1:
                    case SPAMBA_STAR_2:
                    case SPAMBA_STAR_3:
                    case SPAMBA_STAR_4:
                    case SPAMBA_STAR_5:
                    case SPAMBA_STAR_6:
                    case SPAMBA_STAR_7: {
                        obj->oHomeX = obj->oPosX;
                        obj->oHomeY = obj->oPosY;
                        obj->oHomeZ = obj->oPosZ;
                        obj->oInteractionSubtype = INT_SUBTYPE_NO_EXIT;
                    } break;

                    case SPAMBA_WING_CAP: {
                        if (isLuigi()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(luigis_wing_cap_geo, true);
                        if (isWario()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(warios_wing_cap_geo, true);
                    } break;

                    case SPAMBA_VANISH_CAP:
                    case SPAMBA_NORMAL_CAP: {
                        if (isLuigi()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(luigis_cap_geo, true);
                        if (isWario()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(warios_cap_geo, true);
                    } break;

                    case SPAMBA_METAL_CAP: {
                        if (isLuigi()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(luigis_metal_cap_geo, true);
                        if (isWario()) obj->header.gfx.sharedChild = dynos_geo_get_graph_node(warios_metal_cap_geo, true);
                    } break;
                    
                    case SPAMBA_BOBOMB_BUDDY:
                    case SPAMBA_SIGNPOST: {
                        obj->oBehParams2ndByte = (u8) (random_u16() % DIALOG_COUNT);
                        obj->oBehParams = obj->oBehParams2ndByte << 16;
                    } break;

                    case SPAMBA_PIRANHA_PLANT_FIRE: {
                        obj->oTimer = 100;
                    } break;

                    case SPAMBA_HAUNTED_CHAIR:
                    case SPAMBA_SPINY: {
                        obj->parentObj = obj;
                    } break;
                    
                    // Init Bowser here to prevent triggering the cutscene (and setting other params)
                    case SPAMBA_BOWSER: {
                        obj->hitboxRadius = 400;
                        obj->hitboxHeight = 400;
                        obj->oWallHitboxRadius = 100;
                        obj->oInteractType = INTERACT_DAMAGE; // Grabbing and releasing him crashes the game (there is no bomb outside Bowser stages anyway)
                        obj->oFlags = (OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO | OBJ_FLAG_HOLDABLE | OBJ_FLAG_ACTIVE_FROM_AFAR | OBJ_FLAG_COMPUTE_DIST_TO_MARIO | OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE);
                        obj->oHomeX = obj->oPosX;
                        obj->oHomeY = obj->oPosY;
                        obj->oHomeZ = obj->oPosZ;
                        obj->oAnimations = (struct Animation **) bowser_seg6_anims_06057690;
                        obj->oGravity = -4.f;
                        obj->oBounciness = -0.7f;
                        obj->oDragStrength = 10.f;
                        obj->oFriction = 10.f;
                        obj->oBuoyancy = 2.f;
                        obj->oBowserUnk110 = 1;
                        obj->oOpacity = 0xFF;
                        obj->oBowserUnk1AC = 0xFF;
                        obj->oBehParams2ndByte = 2;
                        obj->oBowserUnk1B2 = 0;
                        obj->oHealth = 3;
                        obj->oAction = 0;
                        obj->oBowserUnk1AE = 0;
                        obj->oBowserEyesShut = 0;
                        obj->curBhvCommand = bhvBowser + 27;
                        spawn_object(obj, MODEL_NONE, bhvBowserBodyAnchor);
                        spawn_object(obj, MODEL_NONE, bhvBowserTailAnchor);
                    } break;

                    // Init Hoot here to skip the dialog and make it directly visible and tangible (no need for a tree)
                    case SPAMBA_HOOT: {
                        obj->hitboxRadius = 75;
                        obj->hitboxHeight = 75;
                        obj->oWallHitboxRadius = 25;
                        obj->oIntangibleTimer = 0;
                        obj->oInteractType = INTERACT_HOOT;
                        obj->oHootAvailability = HOOT_AVAIL_READY_TO_FLY;
                        obj->oHootMarioReleaseTime = 0;
                        obj->oFlags = (OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW | OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE);
                        obj->oHomeX = obj->oPosX;
                        obj->oHomeY = obj->oPosY;
                        obj->oHomeZ = obj->oPosZ;
                        obj->oAnimations = (struct Animation **) hoot_seg5_anims_05005768;
                        geo_obj_init_animation(&obj->header.gfx, &obj->oAnimations[0]);
                        obj->curBhvCommand = bhvHoot + 9;
                        m->usedObj = obj; // It's needed to not crash
                    } break;
                    
                    case SPAMBA_TOAD: {
                        obj->oBehParams = (random_u16() % DIALOG_COUNT) << 24;
                    } break;
                    
                    case SPAMBA_CANNON: {
                        obj->oBehParams2ndByte = (u8) ((m->faceAngle[1] - 0x4000) >> 8);
                        obj->oBehParams = obj->oBehParams2ndByte << 16;
                    } break;

                    case SPAMBA_TOX_BOX: {
                        obj->oBehParams2ndByte = (u8) (random_u16() % 3);
                        obj->oBehParams = obj->oBehParams2ndByte << 16;
                    } break;
                }
            }
        }

        // Display selected object
        const u8 *str64 = get_key_string(sSpambaStrings[Cheats.SpambaIndex]);
        char text[256] = "SPAMBA ";
        for (s32 i = 0; str64[i] != 0xFF; ++i) {
            u8 c = str64[i];
            if (c < 10) {
                text[7 + i] = '0' + c;
            } else if (c < 36) {
                text[7 + i] = 'A' + (c - 10);
            } else {
                text[7 + i] = ' ';
            }
        }
        print_text(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), 8, text);
        return TRUE;
    }
    return FALSE;
}

s32 cheats_hurt_mario(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.HurtMario != 0) {
        if ((sButtonDown & L_TRIG) && (sButtonPressed & A_BUTTON)) {
            switch (Cheats.HurtMario) {
                
                // Knockbacks
                case 1: {
                    spawn_object(m->marioObj, MODEL_EXPLOSION, bhvExplosion);
                    play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION | 0xFF00, m->marioObj->header.gfx.cameraToObject);
                    if (m->action & ACT_FLAG_AIR) {
                        drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_HARD_FORWARD_AIR_KB : ACT_HARD_BACKWARD_AIR_KB, 1);
                    } else if (m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
                        drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_FORWARD_WATER_KB : ACT_BACKWARD_WATER_KB, 1);
                    } else {
                        drop_and_set_mario_action(m, (random_u16() & 1) ? ACT_HARD_FORWARD_GROUND_KB : ACT_HARD_BACKWARD_GROUND_KB, 1);
                    }
                } break;
                
                // Shocked
                case 2: {
                    if (m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) {
                        drop_and_set_mario_action(m, ACT_WATER_SHOCKED, 0);
                    } else {
                        u32 actionArg = (m->action & (ACT_FLAG_AIR | ACT_FLAG_ON_POLE | ACT_FLAG_HANGING)) == 0;
                        drop_and_set_mario_action(m, ACT_SHOCKED, actionArg);
                    }
                } break;

                // Burnt
                case 3: {
                    if (!(m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER))) {
                        m->marioObj->oMarioBurnTimer = 0;
                        update_mario_sound_and_camera(m);
                        r96_play_character_sound(m, R96_MARIO_ON_FIRE, R96_LUIGI_ON_FIRE, R96_WARIO_ON_FIRE);
                        if ((m->action & ACT_FLAG_AIR) && m->vel[1] <= 0.f) {
                            drop_and_set_mario_action(m, ACT_BURNING_FALL, 1);
                        } else {
                            drop_and_set_mario_action(m, ACT_BURNING_JUMP, 1);
                        }
                    }
                } break;
                
                // Lava boost
                case 4: {
                    if (!(m->action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER))) {
                        drop_and_set_mario_action(m, ACT_LAVA_BOOST, 0);
                    }
                } break;
                
                // Squished
                case 5: {
                    drop_and_set_mario_action(m, ACT_SQUISHED, 0);
                    r96_play_character_sound(m, R96_MARIO_ATTACKED, R96_LUIGI_ATTACKED, R96_WARIO_ATTACKED);
                    vec3f_set(m->marioObj->header.gfx.scale, 1.8f, 0.05f, 1.8f);
                    m->particleFlags |= PARTICLE_MIST_CIRCLE;
                    m->squishTimer = 0xFF;
                    m->actionState = 1;
                } break;
                
                // Stuck
                case 6: {
                    switch (random_u16() % 3) {
                        case 0: drop_and_set_mario_action(m, ACT_HEAD_STUCK_IN_GROUND, 0); break;
                        case 1: drop_and_set_mario_action(m, ACT_BUTT_STUCK_IN_GROUND, 0); break;
                        case 2: drop_and_set_mario_action(m, ACT_FEET_STUCK_IN_GROUND, 0); break;
                    }
                    r96_play_character_sound(m, R96_MARIO_OOOF, R96_LUIGI_OOOF, R96_WARIO_OOOF);
                    m->particleFlags |= PARTICLE_MIST_CIRCLE;
                } break;

                // 1 HP
                case 7: {
                    m->health = 0x180;
                    m->healCounter = 0;
                    m->hurtCounter = 0;
                } break;
            }
        }
        return TRUE;
    }
    return FALSE;
}

s32 cheats_blj_anywhere(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.BLJAnywhere) {
        if (m->forwardVel < 1.f) {
            if (m->action == ACT_LONG_JUMP_LAND && Cheats.BLJAnywhere >= 7 && (sButtonDown & A_BUTTON)) {
                set_jumping_action(m, ACT_LONG_JUMP, 0);
            } else if (m->action == ACT_LONG_JUMP && m->pos[1] - 50.f < m->floorHeight) {
                if (Cheats.BLJAnywhere < 7) {
                    if (sButtonPressed & A_BUTTON) {
                        m->forwardVel -= (Cheats.BLJAnywhere - 1) * 2.5f;
                        m->vel[1] = -50.f;
                    }
                } else if (sButtonDown & A_BUTTON) {
                    m->forwardVel -= (Cheats.BLJAnywhere - 7) * 2.5f;
                    m->vel[1] = -50.f;
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_swim_anywhere(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.SwimAnywhere) {
        m->waterLevel = m->pos[1] + 300;
        return TRUE;
    }
    return FALSE;
}

s32 cheats_exit_anywhere(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.ExitAnywhere) {
        return TRUE;
    }
    return FALSE;
}

s32 cheats_cap_modifier(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.CapModifier) {
        if (sButtonDown & L_TRIG) {
            switch (sButtonPressed & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {

                // Wing cap
                case U_JPAD: {
                    m->flags |= MARIO_WING_CAP;
                    m->capTimer = 0;
                    r96_play_cap_music(R96_EVENT_CAP_WING);
                } break;

                // Vanish cap
                case L_JPAD: {
                    m->flags |= MARIO_VANISH_CAP;
                    m->capTimer = 0;
                    r96_play_cap_music(R96_EVENT_CAP_VANISH);
                } break;

                // Metal cap
                case R_JPAD: {
                    m->flags |= MARIO_METAL_CAP;
                    m->capTimer = 0;
                    r96_play_cap_music(R96_EVENT_CAP_METAL);
                } break;

                // Normal cap
                case D_JPAD: {
                    m->flags &= ~(MARIO_WING_CAP | MARIO_VANISH_CAP | MARIO_METAL_CAP | MARIO_CAP_IN_HAND);
                    m->flags |= (MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD);
                    m->capTimer = 0;
                    r96_stop_cap_music();
                } break;
            }
        }
    }
    return FALSE;
}

s32 cheats_super_wing_cap(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.SuperWingCap) {
        if (m->action == ACT_FLYING) {
            if (m->forwardVel < 40.f) {
                m->forwardVel += 2.f;
            }
            if (sButtonDown & A_BUTTON) {
                m->particleFlags |= PARTICLE_SPARKLES;
                if (m->forwardVel < 80.f) {
                    m->forwardVel += 4.f;
                }
            }
        }
    }
    return FALSE;
}

s32 cheats_auto_wall_kick(struct MarioState *m) {
#if defined(OMM_DEFINES_H)
    if (OMM_MOVESET_ODYSSEY) {
        return FALSE;
    }
#endif
    if (Cheats.EnableCheats && Cheats.AutoWallKick) {
        if (m->action == ACT_AIR_HIT_WALL) {
            m->vel[1] = 52.f;
            m->faceAngle[1] += 0x8000;
            m->wallKickTimer = 0;
            set_mario_action(m, ACT_WALL_KICK_AIR, 0);
            set_mario_animation(m, MARIO_ANIM_START_WALLKICK);
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_walk_on_hazards(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.WalkOnHazards) {
        return TRUE;
    }
    return FALSE;
}

s32 cheats_no_death_barrier(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.NoDeathBarrier) {
        return TRUE;
    }
    return FALSE;
}

s32 cheats_no_bounds(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.NoBounds) {
        if (gCurrentObject == m->marioObj) {
            return TRUE;
        }
    }
    return FALSE;
}

s32 cheats_no_hold_heavy(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.NoHoldHeavy) {
        if (m->action == ACT_HOLD_HEAVY_IDLE) {
            set_mario_action(m, ACT_HOLD_IDLE, 0);
        } else if (m->action == ACT_HOLD_HEAVY_WALKING) {
            set_mario_action(m, ACT_HOLD_WALKING, 0);
        }
        return TRUE;
    }
    return FALSE;
}

void mario_attract_nearby_coins(struct MarioState *m, f32 range) {
    if (!(gTimeStopState & TIME_STOP_ENABLED)) {
        for (s32 list = OBJ_LIST_GENACTOR; list <= OBJ_LIST_LEVEL; ++list) {
            struct Object *head = (struct Object *) &gObjectLists[list];
            for (struct Object *obj = (struct Object *) head->header.next; obj != head; obj = (struct Object *) obj->header.next) {
                if (obj->oIntangibleTimer == 0 && obj->oInteractType == INTERACT_COIN) {
                    Vec3f dv = {
                        obj->oPosX - m->pos[0],
                        obj->oPosY - m->pos[1] - 60.f,
                        obj->oPosZ - m->pos[2],
                    };
                    f32 distToObj = vec3f_length(dv);
                    if (distToObj > 0.f && distToObj < range) {
                        vec3f_normalize(dv);
                        obj->oPosX -= dv[0] * 40.f;
                        obj->oPosY -= dv[1] * 40.f;
                        obj->oPosZ -= dv[2] * 40.f;
                    }
                }
            }
        }
    }
}

s32 cheats_coins_magnet(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.CoinsMagnet) {
        mario_attract_nearby_coins(m, 1000.f);
        return TRUE;
    }
    return FALSE;
}

s32 cheats_time_stop(struct MarioState *m) {
    static u32 sPrevTimeStopState = 0;
    static bool sPrevTimeStopEnabled = false;

    // Button shortcut
    u32 keyPressed = controller_get_raw_key();
    if (keyPressed != VK_INVALID && (
        keyPressed == CheatsControls.TimeStopButton[0] ||
        keyPressed == CheatsControls.TimeStopButton[1] ||
        keyPressed == CheatsControls.TimeStopButton[2])) {
        Cheats.TimeStop = !Cheats.TimeStop;
    }
    
    // Time stop is enabled, back-up the current state
    if (Cheats.EnableCheats && Cheats.TimeStop) {
        if (!sPrevTimeStopEnabled) {
            sPrevTimeStopEnabled = true;
            sPrevTimeStopState = gTimeStopState;
            gTimeStopState |= TIME_STOP_ENABLED;
        }
        return TRUE;
    }
    
    // Time stop is disabled, retrieve the saved state
    if (sPrevTimeStopEnabled) {
        sPrevTimeStopEnabled = false;
        gTimeStopState = sPrevTimeStopState;
        sPrevTimeStopState = 0;
    }
    return FALSE;
}

s32 cheats_quick_ending(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.QuickEnding) {
        level_trigger_warp(m, WARP_OP_CREDITS_START);
        Cheats.QuickEnding = false;
        save_file_do_save(gCurrSaveFileNum - 1);
        return TRUE;
    }
    return FALSE;
}

s32 cheats_water_control(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        static u32 sPrevCheatWaterLevel = 0;
        static s16 *sDefaultWaterLevels = NULL;
        if (!sDefaultWaterLevels) {
            sDefaultWaterLevels = calloc(LEVEL_COUNT * 8 * 8 * 6, sizeof(16));
            memset(sDefaultWaterLevels, 0xFF, LEVEL_COUNT * 8 * 8 * 6 * sizeof(s16));
        }

        s16 *p = gEnvironmentRegions;
        if (p != NULL) {
            s32 n = p[0];
            for (s32 i = 0; i != n && i < 8; ++i) {
                s16 *env = &p[1 + (i * 6)];
                s16 *def = &sDefaultWaterLevels[((((gCurrLevelNum * 8) + gCurrAreaIndex) * 8) + i) * 6];

                // Init default environment data
                if (def[0] == (s16) 0xFFFF) {
                    memcpy(def, env, 6 * sizeof(s16));
                }

                // Change environment level
                switch (Cheats.WaterLevel) {

                    // Default
                    case 0: {
                        if (sPrevCheatWaterLevel != 0) {
                            memcpy(env, def, 6 * sizeof(s16));
                        } else {
                            memcpy(def, env, 6 * sizeof(s16));
                        }
                    } break;
                    
                    // Drained
                    case 1: {
                        if (env[0] < 50 && sPrevCheatWaterLevel != 1) {
                            set_mario_action(m, ACT_FREEFALL, 0);
                            m->waterLevel = -0x3FFF;
                            m->prevAction = m->action;
                        }
                        env[1] = -0x7FFF;
                        env[2] = -0x7FFF;
                        env[3] = +0x7FFF;
                        env[4] = +0x7FFF;
                        env[5] = -0x3FFF;
                    } break;

                    // Flooded
                    case 2: {
                        if (env[0] < 50 && sPrevCheatWaterLevel != 2) {
                            set_mario_action(m, ACT_WATER_IDLE, 0);
                            m->waterLevel = +0x3FFF;
                            m->prevAction = m->action;
                        }
                        env[1] = -0x7FFF;
                        env[2] = -0x7FFF;
                        env[3] = +0x7FFF;
                        env[4] = +0x7FFF;
                        env[5] = +0x3FFF;
                    } break;
                }
            }
        }
        sPrevCheatWaterLevel = Cheats.WaterLevel;
    }
    return FALSE;
}

s32 cheats_speed_display(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.SpeedDisplay) {
        f32 hSpeed = m->forwardVel;
        f32 ySpeed = m->vel[1];
        if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) {
            hSpeed *= (f32) sModifierValues[Cheats.SwimModifier];
            ySpeed *= (f32) sModifierValues[Cheats.SwimModifier];
        } else {
            hSpeed *= (f32) sModifierValues[Cheats.SpeedModifier];
            if (ySpeed > 0.f) {
                ySpeed *= (f32) sModifierValues[Cheats.JumpModifier];
            }
        }
        print_text_fmt_int(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), 44, "H SPD %d", (s32) hSpeed);
        print_text_fmt_int(GFX_DIMENSIONS_FROM_LEFT_EDGE(8), 28, "Y SPD %d", (s32) ySpeed);
        return TRUE;
    }
    return FALSE;
}

static void cheats_play_as_set_model_and_anims(struct MarioState *m, s32 modelId, const void *anim) {
    m->marioObj->header.gfx.sharedChild = gLoadedGraphNodes[modelId];
    if (modelId == MODEL_PLAYER) {
        if (isLuigi())      gMarioState->animation = (struct MarioAnimation *) &Data_LuigiAnims;
        else if (isWario()) gMarioState->animation = (struct MarioAnimation *) &Data_WarioAnims;
        else                gMarioState->animation = (struct MarioAnimation *) &Data_MarioAnims;
    } else {
        m->marioObj->header.gfx.curAnim.curAnim = (struct Animation *) anim;
    }
}

s32 cheats_play_as(struct MarioState *m) {
#if !defined(OMM_DEFINES_H)
    if (Cheats.EnableCheats) {
        switch(Cheats.PlayAs) {
            case 0: cheats_play_as_set_model_and_anims(m, MODEL_PLAYER, NULL); break;
            case 1: cheats_play_as_set_model_and_anims(m, MODEL_BLACK_BOBOMB, bobomb_seg8_anims_0802396C[0]); break;
            case 2: cheats_play_as_set_model_and_anims(m, MODEL_BOBOMB_BUDDY, bobomb_seg8_anims_0802396C[0]); break;
            case 3: cheats_play_as_set_model_and_anims(m, MODEL_GOOMBA, goomba_seg8_anims_0801DA4C[0]); break;
            case 4: cheats_play_as_set_model_and_anims(m, MODEL_KOOPA_SHELL, amp_seg8_anims_08004034[0]); break;
            case 5: cheats_play_as_set_model_and_anims(m, MODEL_CHUCKYA, chuckya_seg8_anims_0800C070[0]); break;
            case 6: cheats_play_as_set_model_and_anims(m, MODEL_FLYGUY, flyguy_seg8_anims_08011A64[0]); break;
            case 7: {
                switch (gCurrLevelNum) {
                    case LEVEL_BOB: cheats_play_as_set_model_and_anims(m, MODEL_KOOPA_WITH_SHELL, koopa_seg6_anims_06011364[0]); break;
                    case LEVEL_WF: cheats_play_as_set_model_and_anims(m, MODEL_WHOMP, whomp_seg6_anims_06020A04[0]); break;
                    case LEVEL_JRB: cheats_play_as_set_model_and_anims(m, MODEL_CLAM_SHELL, clam_shell_seg5_anims_05001744[0]); break;
                    case LEVEL_CCM: cheats_play_as_set_model_and_anims(m, MODEL_PENGUIN, penguin_seg5_anims_05008B74[0]); break;
                    case LEVEL_BBH: cheats_play_as_set_model_and_anims(m, MODEL_MAD_PIANO, mad_piano_seg5_anims_05009B14[0]); break;
                    case LEVEL_HMC: cheats_play_as_set_model_and_anims(m, MODEL_HMC_ROLLING_ROCK, NULL); break;
                    case LEVEL_LLL: cheats_play_as_set_model_and_anims(m, MODEL_BULLY, bully_seg5_anims_0500470C[0]); break;
                    case LEVEL_SSL: cheats_play_as_set_model_and_anims(m, MODEL_KLEPTO, klepto_seg5_anims_05008CFC[0]); break;
                    case LEVEL_DDD: cheats_play_as_set_model_and_anims(m, MODEL_SUSHI, sushi_seg5_anims_0500AE54[0]); break;
                    case LEVEL_SL: cheats_play_as_set_model_and_anims(m, MODEL_SPINDRIFT, spindrift_seg5_anims_05002D68[0]); break;
                    case LEVEL_WDW: cheats_play_as_set_model_and_anims(m, MODEL_SKEETER, skeeter_seg6_anims_06007DE0[0]); break;
                    case LEVEL_TTM: cheats_play_as_set_model_and_anims(m, MODEL_UKIKI, ukiki_seg5_anims_05015784[0]); break;
                    case LEVEL_THI: cheats_play_as_set_model_and_anims(m, MODEL_SPINY, spiny_seg5_anims_05016EAC[0]); break;
                    case LEVEL_TTC: cheats_play_as_set_model_and_anims(m, MODEL_THWOMP, NULL); break;
                    case LEVEL_RR: cheats_play_as_set_model_and_anims(m, MODEL_ENEMY_LAKITU, lakitu_enemy_seg5_anims_050144D4[0]); break;
                    case LEVEL_BITDW: cheats_play_as_set_model_and_anims(m, MODEL_GOOMBA, goomba_seg8_anims_0801DA4C[0]); break;
                    case LEVEL_BITFS: cheats_play_as_set_model_and_anims(m, MODEL_BULLY, bully_seg5_anims_0500470C[0]); break;
                    case LEVEL_BITS: cheats_play_as_set_model_and_anims(m, MODEL_WHOMP, whomp_seg6_anims_06020A04[0]); break;
                    case LEVEL_TOTWC: cheats_play_as_set_model_and_anims(m, MODEL_EXCLAMATION_BOX, NULL); break;
                    case LEVEL_VCUTM: cheats_play_as_set_model_and_anims(m, MODEL_RED_FLAME, NULL); break;
                    case LEVEL_COTMC: cheats_play_as_set_model_and_anims(m, MODEL_SNUFIT, NULL); break;
                    case LEVEL_PSS: cheats_play_as_set_model_and_anims(m, MODEL_WOODEN_SIGNPOST, NULL); break;
                    case LEVEL_SA: cheats_play_as_set_model_and_anims(m, MODEL_MANTA_RAY, manta_seg5_anims_05008EB4[0]); break;
                    case LEVEL_WMOTR: cheats_play_as_set_model_and_anims(m, MODEL_STAR, manta_seg5_anims_05008EB4[0]); break;
                    case LEVEL_CASTLE_GROUNDS: cheats_play_as_set_model_and_anims(m, MODEL_YOSHI, yoshi_seg5_anims_05024100[0]); break;
                    case LEVEL_CASTLE: cheats_play_as_set_model_and_anims(m, MODEL_TOAD, toad_seg6_anims_0600FB58[6]); break;
                    case LEVEL_CASTLE_COURTYARD: cheats_play_as_set_model_and_anims(m, MODEL_BOO, NULL); break;
                    default: cheats_play_as_set_model_and_anims(m, MODEL_PLAYER, NULL); break;
                }
            } break;
        }
        if (Cheats.PlayAs > 0) {

            // Prevent a softlock when dying
            if (m->action == ACT_STANDING_DEATH) {
                level_trigger_warp(m, WARP_OP_DEATH);
                m->numLives += 1;
            }

            // F*ck doors. Make them explode. Thanks s4ys.
            if (m->collidedObjInteractTypes & INTERACT_DOOR) {
                obj_mark_for_deletion(m->usedObj);
                spawn_object(m->marioObj, MODEL_SMOKE, bhvBobombBullyDeathSmoke);
                play_sound(SOUND_GENERAL2_BOBOMB_EXPLOSION, m->marioObj->header.gfx.cameraToObject);
                m->particleFlags |= PARTICLE_TRIANGLE;
            }
        }
    }
#endif
    return FALSE;
}

s32 cheats_jukebox(struct MarioState *m) {
    if (Cheats.EnableCheats && Cheats.Jukebox) {
        return Cheats.JukeboxMusic;
    }
    return -1;
}

s32 cheats_instant_death(struct MarioState *m) {
    if ((sButtonDown & (A_BUTTON | B_BUTTON | L_TRIG | Z_TRIG)) == (A_BUTTON | B_BUTTON | L_TRIG | Z_TRIG)) {
        level_trigger_warp(m, WARP_OP_DEATH);
        return TRUE;
    }
    return FALSE;
}

s32 cheats_chaos_mode(struct MarioState *m) {
    if (Cheats.EnableCheats) {
        sButtonPressed = gPlayer1Controller->buttonPressed;
        sButtonDown = gPlayer1Controller->buttonDown;
        if (Cheats.ChaosMode) {

            // TODO
            // - call randomly cheats
            // - object magnet (not only coins)
            // - green demon
            // - floor is lava/quicksand
        }
    } else {
        sButtonPressed = 0;
        sButtonDown = 0;
    }
    return FALSE;
}
