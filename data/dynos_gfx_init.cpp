#include "dynos.cpp.h"

Array<ActorGfx> &DynOS_Gfx_GetActorList() {
    static Array<ActorGfx> sActorGfxList;
    return sActorGfxList;
}

// Not recommended because Array uses memcpy to copy its data,
// but safe since this particular array is only get by reference
Array<SysPath> &DynOS_Gfx_GetPackFolders() {
    static Array<SysPath> sPackFolders;
    return sPackFolders;
}

Array<String> DynOS_Gfx_Init() {

    // Alloc and init the actors gfx list
    Array<ActorGfx> &pActorGfxList = DynOS_Gfx_GetActorList();
    pActorGfxList.Resize(DynOS_Geo_GetActorCount());
    for (s32 i = 0; i != DynOS_Geo_GetActorCount(); ++i) {
        pActorGfxList[i].mPackIndex = -1;
        pActorGfxList[i].mGfxData   = NULL;
        pActorGfxList[i].mGraphNode = (GraphNode *) DynOS_Geo_GetGraphNode(DynOS_Geo_GetActorLayout(i), false);
    }

    // Scan the DynOS packs folder
    Array<SysPath> &pDynosPacks = DynOS_Gfx_GetPackFolders();
    SysPath _DynosPacksFolder = fstring("%s/%s", DYNOS_EXE_FOLDER, DYNOS_PACKS_FOLDER);
    DIR *_DynosPacksDir = opendir(_DynosPacksFolder.c_str());
    if (_DynosPacksDir) {
        struct dirent *_DynosPacksEnt = NULL;
        while ((_DynosPacksEnt = readdir(_DynosPacksDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_DynosPacksEnt->d_name) == ".") continue;
            if (SysPath(_DynosPacksEnt->d_name) == "..") continue;

            // If pack folder exists, add it to the pack list
            SysPath _PackFolder = fstring("%s/%s", _DynosPacksFolder.c_str(), _DynosPacksEnt->d_name);
            if (fs_sys_dir_exists(_PackFolder.c_str())) {
                pDynosPacks.Add(_PackFolder);

                // Scan folder for subfolders to convert into .bin files
                DynOS_Gfx_GeneratePack(_PackFolder);
            }
        }
        closedir(_DynosPacksDir);
    }

    // Return a list of pack names
    Array<String> _PackNames;
    for (const auto& _Pack : pDynosPacks) {
        u64 _DirSep1 = _Pack.find_last_of('\\') + 1; // Add 1 here to overflow string::npos to 0
        u64 _DirSep2 = _Pack.find_last_of('/') + 1;  // Add 1 here to overflow string::npos to 0
        SysPath _DirName = _Pack.substr(MAX(_DirSep1, _DirSep2));
        _PackNames.Add(_DirName.c_str());
    }
    return _PackNames;
}
