#include "main.h"
#include "filters/MuteChannel/MuteChannel.h"

extern "C" __declspec(dllexport)
IAudioFilter* CreateFilter(const size_t& nameHash)
{
    if(nameHash == IAudioFilter::hash("MuteChannel"))
        return new MuteChannel();

    return nullptr;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}