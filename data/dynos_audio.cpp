#include "dynos.cpp.h"
extern "C" {
#include "game/area.h"
}

#define AUDIO_BUFFER_SIZE	0x200
#define AUDIO_FREQUENCY		32000
#define AUDIO_FORMAT		AUDIO_S16SYS
#define MUSIC_CHANNELS		2
#define SOUND_CHANNELS		1
#define MUSIC_NO_LOOP		(-1)

//
// Audio
//

// Volume ranges from 0 to 1
// As lower bytes are treated as signed, this gives a 1/256 margin error
// on the mixed sample, but it's faster than treating endianess
extern u16 sAcousticReachPerLevel[];
void DynOS_Audio_Mix(u8 *aOutput, const u8 *aInput, s32 aLength, f32 aVolume, f32 aDistance) {
    f32 _MixVolume = aVolume * (aDistance == 0.f ? 1.f : sqr(1.f - MIN(1.f, absx(aDistance) / sAcousticReachPerLevel[gCurrLevelNum])));
    for (s32 i = 0; i != aLength; ++i) {
        aOutput[i] = (u8) ((s8) ((f32) ((s8) (aInput[i])) * _MixVolume));
    }
}

//
// Music
//

struct MusicData {
    String mName;
    u8 *mData;
    s32    mLength;
    s32    mLoop;
    s32    mCurrent;
    f32  mVolume;
};

STATIC_STORAGE(Array<MusicData *>, LoadedMusics);
#define sLoadedMusics __LoadedMusics()

STATIC_STORAGE(MusicData *, PlayingMusic);
#define sPlayingMusic __PlayingMusic()

static void DynOS_Music_Callback(UNUSED void *, u8 *aStream, s32 aLength) {
    bzero(aStream, aLength);
    if (sPlayingMusic == NULL) {
        return;
    }

    f32 _Volume = sPlayingMusic->mVolume * (configMasterVolume / 127.f) * (configMusicVolume / 127.f);
    s32 _LenTilEnd = sPlayingMusic->mLength - sPlayingMusic->mCurrent;
    if (_LenTilEnd < aLength) {
        DynOS_Audio_Mix(aStream, sPlayingMusic->mData + sPlayingMusic->mCurrent, _LenTilEnd, _Volume, 0);
        if (sPlayingMusic->mLoop != MUSIC_NO_LOOP) {
            DynOS_Audio_Mix(aStream + _LenTilEnd, sPlayingMusic->mData + sPlayingMusic->mLoop, aLength - _LenTilEnd, _Volume, 0);
            sPlayingMusic->mCurrent = sPlayingMusic->mLoop + (aLength - _LenTilEnd);
        } else {
            sPlayingMusic = NULL;
        }
    } else {
        DynOS_Audio_Mix(aStream, sPlayingMusic->mData + sPlayingMusic->mCurrent, aLength, _Volume, 0);
        sPlayingMusic->mCurrent += aLength;
    }
}

static SDL_AudioDeviceID DynOS_Music_GetDevice() {
    static SDL_AudioDeviceID sMusicDeviceId = 0;
    if (sMusicDeviceId) {
        return sMusicDeviceId;
    }

    // Init SDL2 Audio
    if (!SDL_WasInit(SDL_INIT_AUDIO)) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
            sys_fatal("DynOS_Music_GetDevice: Could not init SDL Audio.");
        }
    }

    // Open music device
    SDL_AudioSpec _Want, _Have;
    _Want.freq     = AUDIO_FREQUENCY;
    _Want.format   = AUDIO_FORMAT;
    _Want.channels = MUSIC_CHANNELS;
    _Want.samples  = AUDIO_BUFFER_SIZE;
    _Want.callback = DynOS_Music_Callback;
    _Want.userdata = NULL;
    sMusicDeviceId = SDL_OpenAudioDevice(NULL, 0, &_Want, &_Have, 0);
    if (sMusicDeviceId == 0) {
        sys_fatal("DynOS_Music_GetDevice: Could not open music device.");
    }
    SDL_PauseAudioDevice(sMusicDeviceId, 0);
    return sMusicDeviceId;
}

bool DynOS_Music_LoadRAW(const String &aName, const u8 *aData, s32 aLength, s32 aLoop, f32 aVolume) {
    if (sLoadedMusics.FindIf([&aName](const MusicData *aMusicData) { return aMusicData->mName == aName; }) != -1) {
        return false;
    }

    MusicData *_MusicData = New<MusicData>();
    _MusicData->mName     = aName;
    _MusicData->mData     = CopyBytes(aData, aLength * sizeof(u8));
    _MusicData->mLength   = aLength;
    _MusicData->mLoop     = aLoop * sizeof(s16) * MUSIC_CHANNELS;
    _MusicData->mCurrent  = 0;
    _MusicData->mVolume   = aVolume;
    sLoadedMusics.Add(_MusicData);
    return true;
}

bool DynOS_Music_LoadWAV(const String &aName, const SysPath &aFilename, s32 aLoop, f32 aVolume) {
    if (sLoadedMusics.FindIf([&aName](const MusicData *aMusicData) { return aMusicData->mName == aName; }) != -1) {
        return false;
    }

    SDL_AudioSpec _Spec;
    u8 *_Data;
    s32 _Length;
    if (!SDL_LoadWAV(aFilename.c_str(), &_Spec, &_Data, (u32 *) &_Length)) {
        sys_fatal("DynOS_Music_LoadWAV: Unable to load file %s.", aFilename.c_str());
        return false;
    }
    if (_Spec.freq != AUDIO_FREQUENCY) {
        sys_fatal("DynOS_Music_LoadWAV: From file %s, audio frequency should be %d, is %d.", aFilename.c_str(), AUDIO_FREQUENCY, _Spec.freq);
        return false;
    }
    if (_Spec.format != AUDIO_FORMAT) {
        sys_fatal("DynOS_Music_LoadWAV: From file %s, audio format is not Signed 16-bit PCM.", aFilename.c_str());
        return false;
    }
    if (_Spec.channels != MUSIC_CHANNELS) {
        sys_fatal("DynOS_Music_LoadWAV: From file %s, audio channel count should be %d, is %d.", aFilename.c_str(), MUSIC_CHANNELS, _Spec.channels);
        return false;
    }

    MusicData *_MusicData = New<MusicData>();
    _MusicData->mName     = aName;
    _MusicData->mData     = _Data;
    _MusicData->mLength   = _Length;
    _MusicData->mLoop     = aLoop * sizeof(s16) * MUSIC_CHANNELS;
    _MusicData->mCurrent  = 0;
    _MusicData->mVolume   = aVolume;
    sLoadedMusics.Add(_MusicData);
    return true;
}

void DynOS_Music_Play(const String& aName) {
    s32 _MusicDataIndex = sLoadedMusics.FindIf([&aName](const MusicData *aMusicData) { return aMusicData->mName == aName; });
    if (_MusicDataIndex == -1) {
        return;
    }

    SDL_LockAudioDevice(DynOS_Music_GetDevice());
    sPlayingMusic = sLoadedMusics[_MusicDataIndex];
    sPlayingMusic->mCurrent = 0;
    SDL_UnlockAudioDevice(DynOS_Music_GetDevice());
    SDL_PauseAudioDevice(DynOS_Music_GetDevice(), false);
}

void DynOS_Music_Stop() {
    SDL_LockAudioDevice(DynOS_Music_GetDevice());
    sPlayingMusic = NULL;
    SDL_UnlockAudioDevice(DynOS_Music_GetDevice());
    SDL_PauseAudioDevice(DynOS_Music_GetDevice(), true);
}

void DynOS_Music_Pause() {
    SDL_PauseAudioDevice(DynOS_Music_GetDevice(), TRUE);
}

void DynOS_Music_Resume() {
    SDL_PauseAudioDevice(DynOS_Music_GetDevice(), FALSE);
}

bool DynOS_Music_IsPlaying(const String& aName) {
    return (sPlayingMusic != NULL) && (aName.Empty() || sPlayingMusic->mName == aName);
}

//
// Sound
//

struct SoundData {
    String mName;
    u8 *mData[2];
    s32    mLength;
    f32  mVolume;
    u8  mPriority;
};

STATIC_STORAGE(Array<SoundData *>, LoadedSounds);
#define sLoadedSounds __LoadedSounds()

STATIC_STORAGE(SoundData *, PlayingSound);
#define sPlayingSound __PlayingSound()

static SDL_AudioDeviceID DynOS_Sound_GetDevice() {
    static SDL_AudioDeviceID sSoundDeviceId = 0;
    if (sSoundDeviceId) {
        return sSoundDeviceId;
    }

    // Init SDL2 Audio
    if (!SDL_WasInit(SDL_INIT_AUDIO)) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
            sys_fatal("DynOS_Sound_GetDevice: Could not init SDL Audio.");
        }
    }

    // Open sound device
    SDL_AudioSpec _Want, _Have;
    _Want.freq     = AUDIO_FREQUENCY;
    _Want.format   = AUDIO_FORMAT;
    _Want.channels = SOUND_CHANNELS;
    _Want.samples  = AUDIO_BUFFER_SIZE;
    _Want.callback = NULL;
    _Want.userdata = NULL;
    sSoundDeviceId = SDL_OpenAudioDevice(NULL, 0, &_Want, &_Have, 0);
    if (sSoundDeviceId == 0) {
        sys_fatal("DynOS_Sound_GetDevice: Could not open sound device.");
    }
    SDL_PauseAudioDevice(sSoundDeviceId, 0);
    return sSoundDeviceId;
}

bool DynOS_Sound_LoadRAW(const String& aName, const u8 *aData, s32 aLength, f32 aVolume, u8 aPriority) {
    if (sLoadedSounds.FindIf([&aName](const SoundData *aSoundData) { return aSoundData->mName == aName; }) != -1) {
        return false;
    }

    SoundData *_SoundData = New<SoundData>();
    _SoundData->mName     = aName;
    _SoundData->mData[0]  = CopyBytes(aData, aLength * sizeof(u8));
    _SoundData->mData[1]  = CopyBytes(aData, aLength * sizeof(u8));
    _SoundData->mLength   = aLength;
    _SoundData->mVolume   = aVolume;
    _SoundData->mPriority = aPriority;
    sLoadedSounds.Add(_SoundData);
    return true;
}

bool DynOS_Sound_LoadWAV(const String& aName, const SysPath& aFilename, f32 aVolume, u8 aPriority) {
    if (sLoadedSounds.FindIf([&aName](const SoundData *aSoundData) { return aSoundData->mName == aName; }) != -1) {
        return false;
    }

    SDL_AudioSpec _Spec;
    u8 *_Data;
    s32 _Length;
    if (!SDL_LoadWAV(aFilename.c_str(), &_Spec, &_Data, (u32 *) &_Length)) {
        sys_fatal("DynOS_Sound_LoadWAV: Unable to load file %s.", aFilename.c_str());
        return false;
    }
    if (_Spec.freq != AUDIO_FREQUENCY) {
        sys_fatal("DynOS_Sound_LoadWAV: From file %s, audio frequency should be %d, is %d.", aFilename.c_str(), AUDIO_FREQUENCY, _Spec.freq);
        return false;
    }
    if (_Spec.format != AUDIO_FORMAT) {
        sys_fatal("DynOS_Sound_LoadWAV: From file %s, audio format is not Signed 16-bit PCM.", aFilename.c_str());
        return false;
    }
    if (_Spec.channels != SOUND_CHANNELS) {
        sys_fatal("DynOS_Sound_LoadWAV: From file %s, audio channel count should be %d, is %d.", aFilename.c_str(), SOUND_CHANNELS, _Spec.channels);
        return false;
    }

    SoundData *_SoundData = New<SoundData>();
    _SoundData->mName     = aName;
    _SoundData->mData[0]  = _Data;
    _SoundData->mData[1]  = CopyBytes(_Data, _Length * sizeof(u8));
    _SoundData->mLength   = _Length;
    _SoundData->mVolume   = aVolume;
    _SoundData->mPriority = aPriority;
    sLoadedSounds.Add(_SoundData);
    return true;
}

void DynOS_Sound_Play(const String& aName, f32 *aPos) {
    s32 _SoundDataIndex = sLoadedSounds.FindIf([&aName](const SoundData *aSoundData) { return aSoundData->mName == aName; });
    if (_SoundDataIndex == -1) {
        return;
    }

    // Update playing sound
    if (SDL_GetQueuedAudioSize(DynOS_Sound_GetDevice()) == 0) {
        sPlayingSound = NULL;
    }

    // Don't overwrite playing sounds with higher aPriority
    // Sounds with equal aPriority cancel out each other
    SoundData *_SoundData = sLoadedSounds[_SoundDataIndex];
    if (sPlayingSound != NULL && sPlayingSound->mPriority > _SoundData->mPriority) {
        return;
    }

    f32 aVolume = _SoundData->mVolume * (configMasterVolume / 127.f) * (configSfxVolume / 127.f);
    f32 aDistance = (aPos == NULL ? 0 : vec3f_length(aPos));
    DynOS_Audio_Mix(_SoundData->mData[1], _SoundData->mData[0], _SoundData->mLength, aVolume, aDistance);
    SDL_ClearQueuedAudio(DynOS_Sound_GetDevice());
    SDL_QueueAudio(DynOS_Sound_GetDevice(), _SoundData->mData[1], _SoundData->mLength);
    sPlayingSound = _SoundData;
}

void DynOS_Sound_Stop() {
    SDL_ClearQueuedAudio(DynOS_Sound_GetDevice());
    sPlayingSound = NULL;
}

bool DynOS_Sound_IsPlaying(const String& aName) {
    return (SDL_GetQueuedAudioSize(DynOS_Sound_GetDevice()) != 0) && (aName.Empty() || sPlayingSound->mName == aName);
}
