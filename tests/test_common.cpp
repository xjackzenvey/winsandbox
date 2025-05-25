#include "common.hpp"

void Test_GetProcessIdByName() {
    const char* processName = "adb.exe"; // 示例进程名
    DWORD pid = GetProcessIdByName(processName);

    if (pid != 0) {
        std::cout << "Process ID of " << processName << ": " << pid << std::endl;
    } else {
        std::cout << "Process " << processName << " not found." << std::endl;
    }
}

int main() {
    Test_GetProcessIdByName();
    return 0;
}