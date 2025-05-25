#pragma once

#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

DWORD GetProcessIdByName(LPCSTR processName) {
    /*
        // 根据进程名获取 PID
        // param processName [LPCSTR | const char*]: 进程名
        // return: 进程 ID [DWORD | unsigned long] ，如果未找到则返回 0
    */

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (strcmp(pe32.szExeFile, processName) == 0) {
                CloseHandle(hSnapshot);
                return pe32.th32ProcessID;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    CloseHandle(hSnapshot);
    return 0; // 未找到进程
}


DWORD InjectDll(DWORD pid, LPCSTR dllPath) {
    /*
        // 注入 DLL 到指定进程
        // param pid [DWORD | unsigned long]: 目标进程 ID
        // param dllPath [LPCSTR | const char*]: DLL 路径
        // return: void
        warning: 该函数需要管理员权限运行
    */

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == NULL) {
        std::cerr << "Failed to open process with ID: " << pid << std::endl;
        return -1;
    }

    // 分配内存空间用于 DLL 路径
    LPVOID pRemoteMem = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    WriteProcessMemory(hProcess, pRemoteMem, (LPVOID)dllPath, strlen(dllPath) + 1, NULL);

    // 获取 LoadLibraryA 函数地址, 将其作为远程线程的入口点
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pRemoteMem, 0, NULL);
    if (hThread == NULL) {
        std::cerr << "Failed to create remote thread in process with ID: " << pid << std::endl;
        VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return -1;
    }
    WaitForSingleObject(hThread, INFINITE);
    VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);

    #ifdef _DEBUG
        std::cout << "DLL injected successfully into process with ID: " << pid << std::endl;
    #endif

    return 0;
}

#endif
