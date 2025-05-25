#include <Windows.h>
#include "detours.h"
#include "hookbase.hpp"
#ifndef _DEBUG
#define _DEBUG
#endif

# pragma comment(lib, "detours.lib")

// MessageBoxW 的原始函数指针
static int (WINAPI *OriginalMessageBoxW) (HWND, LPCWSTR, LPCWSTR, UINT) = MessageBoxW;

// 自定义函数进行修改
int WINAPI MyMessageBoxW(HWND hwnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
    return OriginalMessageBoxW(hwnd, L"hooked!", L"Success", MB_OK);
}


int main() {
    // 还未拦截的 MessageBoxW 调用
    MessageBoxW(NULL, L"Hello, World!", L"Original", MB_OK);

    // 安装钩子
    HOOK_install_Local((void**)&OriginalMessageBoxW, (void*)MyMessageBoxW);

    // 再次调用 MessageBoxW，应该会被拦截
    MessageBoxW(NULL, L"Hello, World!", L"Original", MB_OK);
    
    // 移除钩子
    HOOK_remove_local((void**)&OriginalMessageBoxW, (void*)MyMessageBoxW);

    // 再次调用 MessageBoxW，应该不会被拦截
    MessageBoxW(NULL, L"Hello, World!", L"Original", MB_OK);

    return 0;
}