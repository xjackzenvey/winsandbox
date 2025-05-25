# pragma once

#ifndef _HOOKBASE_HPP_
#define _HOOKBASE_HPP_

#include <Windows.h>
#include "detours.h"
#include <iostream>
#include "common.hpp"

# pragma comment(lib, "detours.lib")

// 安装本地钩子
void HOOK_install_Local(void** OriginFunc, void* HookedFunc) {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach((PVOID*)OriginFunc, HookedFunc);
    if (DetourTransactionCommit() != NO_ERROR) {
        #ifdef _DEBUG
            std::cout << "Error when installing Hook. Exit." << std::endl;
        #endif
        exit(EXIT_FAILURE);
    }

    #ifdef _DEBUG
        std::cout << "Hook installed successfully." << std::endl;
    #endif
    
}

// 移除本地钩子
void HOOK_remove_local(void** OriginFunc, void* HookedFunc){
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach((PVOID*)OriginFunc, HookedFunc);
    if (DetourTransactionCommit() != NO_ERROR) {
        #ifdef _DEBUG
            std::cout << "Error when removing Hook. Exit." << std::endl;
        #endif
        exit(EXIT_FAILURE);
    }

    #ifdef _DEBUG
        std::cout << "Hook removed successfully." << std::endl;
    #endif
}

DWORD HOOK_attach_LAUNCH_remote(LPCSTR lpApplicationPath, LPCSTR lpDllPath) {
    // 将钩子安装在还未运行的进程中，并启动进程
    // param [LPCSTR | const char*] lpApplicationPath 要注入的进程路径
    // param [LPCSTR | const char*] lpDllPath 带钩子的 dll 路径

    STARTUPINFO si = {0};
    si.cb = sizeof(STARTUPINFO);
    PROCESS_INFORMATION pi;
    DWORD _ATTACH = DetourCreateProcessWithDllExA(
        lpApplicationPath, 
        NULL,     // 命令行参数
        NULL, NULL,
        FALSE, // 不继承句柄
        CREATE_DEFAULT_ERROR_MODE,
        NULL,   // 环境变量
        NULL,   // 工作目录
        &si, &pi,
        lpDllPath,
        NULL       // 回调函数
    );


    if (_ATTACH != TRUE) {
        DWORD errorCode = GetLastError();
        std::cerr << "HOOK_install_LAUNCH_remote -> DetourCreateProcessWithDllA Error. Error Code: " << errorCode << std::endl;
        return 1;
    }

    DetourFinishHelperProcess(reinterpret_cast<HWND>(pi.hProcess), reinterpret_cast<HINSTANCE>(pi.hThread), NULL, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;

}


DWORD HOOK_attach_EXISTED_remote(LPCSTR lpApplicationName, DWORD PID, LPCSTR dllPath) {
    // 将带有钩子的 dll 注入到已经启动的进程
    // param [LPCSTR | const char*] lpApplicationName 进程名
    // param [DWORD | unsigned long] PID 进程ID
    // param  [LPCSTR | const char*] dllPath dll路径
    // 如果 PID 为 NULL 才使用进程名查找

    DWORD ProcessID;
    if (PID != NULL) {ProcessID = PID;}
    else {ProcessID = GetProcessIdByName(lpApplicationName);}

    if (ProcessID == NULL) {
        std::cerr << "HOOK_install_EXISTED_remote: cannot find the process." << std::endl;
        return 1;
    }else {
        std::cout << "HOOK_install_EXISTED_remote: Process ID is " << ProcessID << std::endl;
    }

    if (InjectDll(ProcessID, dllPath) != 0) {
        std::cerr << "HOOK_install_EXISTED_remote: InjectDll Error." << std::endl;
        return 1;
    }

    return 0;
}

# endif // _HOOKBASE_HPP_