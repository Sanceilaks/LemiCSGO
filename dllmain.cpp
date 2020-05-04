#include "framework.h" 

//объяснение хуков интерфейса в CEngineClient

DWORD __stdcall HackStart(HMODULE dll)
{
    HackCore::GetInstance()->CoreInit(); //да-да синглтон

    HackCore::AddLog("Is init!");

    MessageBoxA(NULL, "Test", "Test", MB_OK);

    HackCore::GetInstance()->EngineClient->ExecuteClientCmd("echo HELLO");

    HackCore::GetInstance()->CoreUnload(dll);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {  
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HackStart, hModule, NULL, NULL);
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}