#include "framework.h" 
#include <Lmcons.h>
#include "TextColor.h"

//объяснение хуков интерфейса в CEngineClient

DWORD __stdcall HackStart(HMODULE dll)
{
    HackCore::GetInstance()->CoreInit(); //да-да синглтон

    TCHAR username[UNLEN + 1];
    DWORD size = UNLEN + 1;

    GetUserName((TCHAR*)username, &size);

    std::cout << "Hello, " << red << username << white << "\n";

    HackCore::GetInstance()->EngineClient->ExecuteClientCmd("echo HELLO");

    while (HackCore::GetInstance()->isWork)
    {
        if (GetAsyncKeyState(VK_END))
            HackCore::GetInstance()->isWork = false;
        //std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    HackCore::GetInstance()->CoreUnload(dll);
    
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {  
    case DLL_PROCESS_ATTACH:
    {
        try
        {
            DisableThreadLibraryCalls(hModule);
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HackStart, hModule, NULL, NULL);
        }
        catch (...)
        {
            printf("ERROR !!!!!!!!\n");
            HackCore::GetInstance()->CoreUnload(hModule);
        }
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}