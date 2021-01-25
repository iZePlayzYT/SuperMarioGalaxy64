#include "dynos.cpp.h"

extern DynosOption *DynOS_Opt_Loop(DynosOption *aOpt, DynosLoopFunc aFunc, void *aData);

static bool DynOS_Opt_GetConfig(DynosOption *aOpt, void *aData) {
    Pair<u8, String> _TypeAndName = *((Pair<u8, String> *) aData);
    return (aOpt->mType == _TypeAndName.first && aOpt->mConfigName == _TypeAndName.second);
}

void DynOS_Opt_LoadConfig(DynosOption *aMenu) {
    SysPath _Filename = fstring("%s/%s", sys_user_path(), DYNOS_CONFIG_FILENAME);
    FILE *_File = fopen(_Filename.c_str(), "rb");
    if (_File == NULL) {
        return;
    }

    while (true) {

        // Type and name
        Pair<u8, String> _ConfigTypeAndName = { DOPT_NONE, "" };
        _ConfigTypeAndName.first = ReadBytes<u8>(_File);
        _ConfigTypeAndName.second.Read(_File);
        if (_ConfigTypeAndName.first == DOPT_NONE) {
            break;
        }

        // Values
        s32 _Value0 = ReadBytes<s32>(_File);
        s32 _Value1 = ReadBytes<s32>(_File);
        s32 _Value2 = ReadBytes<s32>(_File);

        // Option
        DynosOption *_Opt = DynOS_Opt_Loop(aMenu, DynOS_Opt_GetConfig, (void *) &_ConfigTypeAndName);
        if (_Opt != NULL) {
            switch (_Opt->mType) {
                case DOPT_TOGGLE: *_Opt->mToggle.mTog    = (bool) _Value0; break;
                case DOPT_CHOICE: *_Opt->mChoice.mIndex  = (s32) _Value0; break;
                case DOPT_SCROLL: *_Opt->mScroll.mValue  = (s32) _Value0; break;
                case DOPT_BIND:    _Opt->mBind.mBinds[0] = (u32) _Value0;
                                   _Opt->mBind.mBinds[1] = (u32) _Value1;
                                   _Opt->mBind.mBinds[2] = (u32) _Value2; break;
            }
        }
    }
    fclose(_File);
}

static bool DynOS_Opt_SetConfig(DynosOption *aOpt, void *aData) {
    if (aOpt->mConfigName.Length() != 0 &&
        aOpt->mConfigName          != "null" &&
        aOpt->mConfigName          != "NULL") {
        FILE *_File = (FILE *) aData;
        s32 _Value0 = 0;
        s32 _Value1 = 0;
        s32 _Value2 = 0;

        // Option
        switch (aOpt->mType) {
            case DOPT_TOGGLE: _Value0 = (s32) *aOpt->mToggle.mTog; break;
            case DOPT_CHOICE: _Value0 = (s32) *aOpt->mChoice.mIndex; break;
            case DOPT_SCROLL: _Value0 = (s32) *aOpt->mScroll.mValue; break;
            case DOPT_BIND:   _Value0 = (s32) aOpt->mBind.mBinds[0];
                              _Value1 = (s32) aOpt->mBind.mBinds[1];
                              _Value2 = (s32) aOpt->mBind.mBinds[2]; break;
        }

        // Type and name
        WriteBytes<u8>(_File, aOpt->mType);
        aOpt->mConfigName.Write(_File);

        // Values
        WriteBytes<s32>(_File, _Value0);
        WriteBytes<s32>(_File, _Value1);
        WriteBytes<s32>(_File, _Value2);
    }
    return 0;
}

void DynOS_Opt_SaveConfig(DynosOption *aMenu) {
    SysPath _Filename = fstring("%s/%s", sys_user_path(), DYNOS_CONFIG_FILENAME);
    FILE *_File = fopen(_Filename.c_str(), "wb");
    if (!_File) {
        return;
    }

    DynOS_Opt_Loop(aMenu, DynOS_Opt_SetConfig, (void *) _File);
    fclose(_File);
}
