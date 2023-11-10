// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <thread>
#include "XAntiDebug/XAntiDebug.h"

unsigned __stdcall CheckDebugger(void* arg);
int GetRandNumber(const int low, const int high);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        unsigned int uiThreadID = 0;
        _beginthreadex(NULL, 0, CheckDebugger, (void*)NULL, 0, &uiThreadID);
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

unsigned __stdcall CheckDebugger(void* arg)
{
    XAD_STATUS		status;
    XAntiDebug		antiDbg(GetModuleHandle(NULL), FLAG_FULLON);
    BOOL			result;

    //
    // 在程序最早的时候初始化 如 WinMain 或 DllMain
    //
    status = antiDbg.XAD_Initialize();
    if (status != XAD_OK)
    {
        printf("initialize error. %d\n", status);
        return 0;
    }

    srand(time(0));
    while (true)
    {
        DWORD st = ::GetTickCount();
        if (::GetTickCount() - st > 10)
        {
            int n = GetRandNumber(2, 10);
            for (size_t i = 0; i < n; i++)
            {
                Sleep(1000);
            }
            exit(0);
        }
        result = antiDbg.XAD_ExecuteDetect();
        if (::GetTickCount() - st > 10)
        {
            int n = GetRandNumber(2, 10);
            for (size_t i = 0; i < n; i++)
            {
                Sleep(1000);
            }
            exit(0);
        }

        //printf("result = %s\n", result ? "true" : "false");

        if (result)
        {
            int n = GetRandNumber(2, 10);
            for (size_t i = 0; i < n; i++)
            {
                Sleep(1000);
            }
            exit(0);
        }

        Sleep(5000);
    }
    return 0;
}

/*
 * 获取随机数
 * return : 随机数
 */
int GetRandNumber(const int low, const int high)
{
    int randNum = 0;
    //生成随机数
    randNum = rand() % (high - low + 1) + low;

    return randNum;
}
