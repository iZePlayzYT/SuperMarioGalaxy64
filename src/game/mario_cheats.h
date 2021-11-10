#ifndef MARIO_CHEATS_H
#define MARIO_CHEATS_H

#include "types.h"

enum {
    SPAMBA_YELLOW_COIN,
    SPAMBA_RED_COIN,
    SPAMBA_BLUE_COIN,
    SPAMBA_MUSHROOM_1UP,
    SPAMBA_STAR_1,
    SPAMBA_STAR_2,
    SPAMBA_STAR_3,
    SPAMBA_STAR_4,
    SPAMBA_STAR_5,
    SPAMBA_STAR_6,
    SPAMBA_STAR_7,
    SPAMBA_WING_CAP,
    SPAMBA_VANISH_CAP,
    SPAMBA_METAL_CAP,
    SPAMBA_NORMAL_CAP,
    SPAMBA_RECOVERY_HEART,

    SPAMBA_GOOMBA,
    SPAMBA_GOOMBA_TRIPLET,
    SPAMBA_KOOPA,
    SPAMBA_KOOPA_SHELL,
    SPAMBA_BOBOMB,
    SPAMBA_BOBOMB_BUDDY,
    SPAMBA_CHAIN_CHOMP,
    SPAMBA_PIRANHA_PLANT,
    SPAMBA_PIRANHA_PLANT_FIRE,
    SPAMBA_WHOMP,
    SPAMBA_SPINDRIFT,
    SPAMBA_BOO,
    SPAMBA_MR_I,
    SPAMBA_BOOK,
    SPAMBA_SCUTTLEBUG,
    SPAMBA_SWOOP,
    SPAMBA_SNUFIT,
    SPAMBA_BULLY,
    SPAMBA_CHILL_BULLY,
    SPAMBA_MOTOS,
    SPAMBA_BLARGG,
    SPAMBA_POKEY,
    SPAMBA_FLYGUY,
    SPAMBA_MONEYBAG,
    SPAMBA_CHUCKYA,
    SPAMBA_SKEETER,
    SPAMBA_LAKITU,
    SPAMBA_SPINY,
    
    SPAMBA_BOWLING_BALL,
    SPAMBA_CLAM,
    SPAMBA_MR_BLIZZARD,
    SPAMBA_HAUNTED_CHAIR,
    SPAMBA_MAD_PIANO,
    SPAMBA_BIG_BOULDER,
    SPAMBA_FIRE_SPITTER,
    SPAMBA_FLAMETHROWER,
    SPAMBA_BOUNCING_FIREBALL,
    SPAMBA_CIRCLING_AMP,
    SPAMBA_HOMING_AMP,
    SPAMBA_HEAVE_HO,
    
    SPAMBA_KING_BOBOMB,
    SPAMBA_KING_WHOMP,
    SPAMBA_BIG_BOO,
    SPAMBA_BIG_BULLY,
    SPAMBA_BIG_CHILL_BULLY,
    SPAMBA_EYEROCK,
    SPAMBA_WIGGLER,
    SPAMBA_BOWSER,

    SPAMBA_HOOT,
    SPAMBA_PENGUIN,
    SPAMBA_MOTHER_PENGUIN,
    SPAMBA_KLEPTO,
    SPAMBA_UKIKI,
    SPAMBA_TOAD,
    SPAMBA_SIGNPOST,
    
    SPAMBA_CANNON,
    SPAMBA_BREAKABLE_BOX,
    SPAMBA_BREAKABLE_BOX_SMALL,
    SPAMBA_CRAZY_BOX,
    SPAMBA_EXCLAMATION_BOX_WING_CAP, // 0
    SPAMBA_EXCLAMATION_BOX_METAL_CAP, // 1
    SPAMBA_EXCLAMATION_BOX_VANISH_CAP, // 2
    SPAMBA_EXCLAMATION_BOX_KOOPA_SHELL, // 3
    SPAMBA_EXCLAMATION_BOX_ONE_COIN, // 4 
    SPAMBA_EXCLAMATION_BOX_THREE_COINS, // 5
    SPAMBA_EXCLAMATION_BOX_TEN_COINS, // 6 
    SPAMBA_EXCLAMATION_BOX_MUSHROOM_1UP, // 7
    SPAMBA_EXCLAMATION_BOX_STAR_1, // 8 
    SPAMBA_EXCLAMATION_BOX_STAR_2, // 10 
    SPAMBA_EXCLAMATION_BOX_STAR_3, // 11 
    SPAMBA_EXCLAMATION_BOX_STAR_4, // 12 
    SPAMBA_EXCLAMATION_BOX_STAR_5, // 13 
    SPAMBA_EXCLAMATION_BOX_STAR_6, // 14
    SPAMBA_METAL_BOX,
    SPAMBA_THWOMP,
    SPAMBA_GRINDEL,
    SPAMBA_GRINDEL_HORIZONTAL,
    SPAMBA_SPINDEL,
    SPAMBA_TOX_BOX,

    SPAMBA_COUNT
};

s32 cheats_moon_jump(struct MarioState *m);
s32 cheats_moon_gravity(struct MarioState *m);
s32 cheats_super_copter(struct MarioState *m);
s32 cheats_debug_move(struct MarioState *m);
s32 cheats_god_mode(struct MarioState *m);
s32 cheats_infinite_lives(struct MarioState *m);
s32 cheats_responsive(struct MarioState *m);
s32 cheats_speed_modifier(struct MarioState *m);
s32 cheats_jump_modifier(struct MarioState *m);
s32 cheats_swim_modifier(struct MarioState *m);
s32 cheats_size_modifier(struct MarioState *m);
s32 cheats_spamba(struct MarioState *m);
s32 cheats_hurt_mario(struct MarioState *m);
s32 cheats_blj_anywhere(struct MarioState *m);
s32 cheats_swim_anywhere(struct MarioState *m);
s32 cheats_exit_anywhere(struct MarioState *m);
s32 cheats_cap_modifier(struct MarioState *m);
s32 cheats_super_wing_cap(struct MarioState *m);
s32 cheats_auto_wall_kick(struct MarioState *m);
s32 cheats_walk_on_hazards(struct MarioState *m);
s32 cheats_no_death_barrier(struct MarioState *m);
s32 cheats_no_bounds(struct MarioState *m);
s32 cheats_no_hold_heavy(struct MarioState *m);
s32 cheats_coins_magnet(struct MarioState *m);
s32 cheats_time_stop(struct MarioState *m);
s32 cheats_quick_ending(struct MarioState *m);
s32 cheats_water_control(struct MarioState *m);
s32 cheats_speed_display(struct MarioState *m);
s32 cheats_play_as(struct MarioState *m);
s32 cheats_jukebox(struct MarioState *m);
s32 cheats_instant_death(struct MarioState *m);
s32 cheats_chaos_mode(struct MarioState *m);

#endif // MARIO_CHEATS_H
