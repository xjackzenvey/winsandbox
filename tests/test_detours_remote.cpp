#include "hookbase.hpp"
#include "detours.h"
#define _DEBUG

void TEST_NORMAL_launch(){
    LPCSTR lpApplicationPath = "D:/test.exe";
    STARTUPINFO si = {0};
    si.cb = sizeof(STARTUPINFO);
    PROCESS_INFORMATION pi;
    BOOL result = CreateProcessA(
        lpApplicationPath, 
        NULL,     // 命令行参数
        NULL, NULL,
        FALSE, // 不继承句柄
        CREATE_DEFAULT_ERROR_MODE,
        NULL,   // 环境变量
        NULL,   // 工作目录
        &si, &pi
    );
    if (!result) {
        DWORD errorCode = GetLastError();
        std::cerr << "CreateProcessA Error. Error Code: " << errorCode << std::endl;
    } else {
        std::cout << "Process launched successfully." << std::endl;
    }
}

void TEST_HOOK_attach_LAUNCH_remote_MessageBox(){
    LPCSTR lpApplicationPath = "D:/project/open-source/WinSandBox/build/Debug/test.exe";
    LPCSTR lpDllPath = "D:/project/open-source/WinSandBox/build/Debug/hook_messagebox.dll";
    HOOK_attach_LAUNCH_remote(lpApplicationPath, lpDllPath);
}

void TEST_HOOK_attach_existed_remote_MessageBox(){
    LPCSTR lpApplicationName = "wall.exe";
    LPCSTR lpDllPath = "D:/project/open-source/WinSandBox/build/Debug/hook_messagebox.dll";
    HOOK_attach_EXISTED_remote(lpApplicationName, NULL, lpDllPath);
}

int main() {
    //TEST_HOOK_attach_LAUNCH_remote_MessageBox();
    TEST_HOOK_attach_existed_remote_MessageBox();
    return 0;
}