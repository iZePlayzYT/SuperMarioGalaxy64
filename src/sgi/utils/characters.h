#ifndef CHARACTERS_UTIL
#define CHARACTERS_UTIL
#include "include/types.h"

#define MARIO 0
#define LUIGI 1

void set_notification_status(s8 newState);
s8 get_notification_status();

s32 getCharacterType();
void setCharacterModel(s32 type);
f32 getCharacterMultiplier();
void playCharacterSound(s32 actionSound, s32 characterSound);
void triggerLuigiNotification();
//Todo: To be removed
s32 isLuigi();
s32 isWario();

#endif