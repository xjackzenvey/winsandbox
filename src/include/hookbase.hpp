# pragma once

#ifndef _HOOKBASE_HPP_
#define _HOOKBASE_HPP_

#include <Windows.h>
#include "detours.h"
#include <iostream>

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

# endif // _HOOKBASE_HPP_