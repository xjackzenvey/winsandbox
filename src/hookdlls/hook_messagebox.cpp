#include <Windows.h>
#include "hookbase.hpp"

static int (WINAPI *OriginalMessageBoxW) (HWND, LPCWSTR, LPCWSTR, UINT) = MessageBoxW;
static int (WINAPI *OriginalMessageBoxA) (HWND, LPCSTR, LPCSTR, UINT) = MessageBoxA;

int WINAPI MyMessageBoxW(HWND hwnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) {
    // 在这里可以修改 MessageBoxW 的行为
    return OriginalMessageBoxW(hwnd, L"hooked!", L"Success", MB_OK);
}

int WINAPI MyMessageBoxA(HWND hwnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType) {
    // 在这里可以修改 MessageBoxA 的行为
    return OriginalMessageBoxA(hwnd, "hooked!", "Success", MB_OK);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // 安装钩子
        HOOK_install_Local((void**)&OriginalMessageBoxW, (void*)MyMessageBoxW);
        HOOK_install_Local((void**)&OriginalMessageBoxA, (void*)MyMessageBoxA);
    }else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        // 移除钩子
        HOOK_remove_local((void**)&OriginalMessageBoxW, (void*)MyMessageBoxW);
        HOOK_remove_local((void**)&OriginalMessageBoxA, (void*)MyMessageBoxA);
    }
}