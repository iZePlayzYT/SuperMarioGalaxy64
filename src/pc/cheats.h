#ifndef _CHEATS_H
#define _CHEATS_H

#include <stdbool.h>
typedef unsigned int uint;

struct CheatList {
    bool EnableCheats;

    // Classic cheats
    bool MoonJump;
    bool GodMode;
    bool InfiniteLives;
    bool Responsive;
    bool MoonGravity;
    bool DebugMove;
    bool SuperCopter;
    bool AutoWallKick;
    bool NoHoldHeavy;

    // Modifiers
    uint SpeedModifier;
    uint JumpModifier;
    uint SwimModifier;
    uint SizeModifier;
    bool CapModifier;
    bool SuperWingCap;
    uint PlayAs;
    bool Jukebox;
    uint JukeboxMusic;
    bool SpeedDisplay;

    // Time-Space
    uint BLJAnywhere;
    bool SwimAnywhere;
    bool ExitAnywhere;
    bool WalkOnHazards;
    bool NoDeathBarrier;
    bool NoBounds;
    uint WaterLevel;
    bool CoinsMagnet;
    bool TimeStop;
    bool QuickEnding;
    uint HurtMario;

    // Spamba
    bool Spamba;
    uint SpambaIndex;

    // Chaos
    bool ChaosMode;
};

struct CheatControls {
    uint TimeStopButton[3];
    uint SpambaControls[3]; // 0 is previous object, 1 is next object, 2 is spawn object
};

extern struct CheatList Cheats;
extern struct CheatControls CheatsControls;
extern const char **CheatJukeboxMusics[];

#endif // _CHEATS_H
