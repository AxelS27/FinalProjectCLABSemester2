//=====[[ C Library ]]=====
#include <windows.h>
#include <stdio.h>

//=====[[ Custom Library ]]=====
#include "../library/sound_manager.h"

//=====[[ Windows's utility for sound ]]=====
typedef BOOL (WINAPI *PlaySoundFunc)(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);

//=====[[ Play wav function ]]=====
void play_wav(const char *filename, int async) {
    HMODULE hWinMM = LoadLibraryA("winmm.dll");
    if (hWinMM == NULL) {
        return;
    }

    PlaySoundFunc dynPlaySound = (PlaySoundFunc)GetProcAddress(hWinMM, "PlaySoundA");
    if (!dynPlaySound) {
        FreeLibrary(hWinMM);
        return;
    }

    DWORD flags = SND_FILENAME;
    flags |= (async ? SND_ASYNC : SND_SYNC);

    dynPlaySound(filename, NULL, flags);
    FreeLibrary(hWinMM);
}
