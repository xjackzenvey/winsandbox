CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(WinSandBox)


# 源代码

set (SRC_DIR src)
include_directories(${SRC_DIR}/include)

# Detours 导入
set (DETOURS_DIR D:/project/open-source/Detours-4.0.1)  
include_directories(${DETOURS_DIR}/include)
link_libraries(${DETOURS_DIR}/lib.X64/detours.lib)


# 将 src/hookdlls 里的所有源文件打包为 dll
set (HOOK_DLLS_DIR ${SRC_DIR}/hookdlls)
add_library(hook_messagebox SHARED ${HOOK_DLLS_DIR}/hook_messagebox.cpp)
add_library(hook_filesystem SHARED ${HOOK_DLLS_DIR}/hook_filesystem.cpp)


# 测试
set (TEST_DIR tests)
add_executable(test_detours_base ${TEST_DIR}/test_detours_base.cpp)
add_test(NAME TEST_detours_base COMMAND test_detours_base)

add_executable(test_common ${TEST_DIR}/test_common.cpp)
add_test(NAME TEST_common COMMAND test_common)

add_executable(test_destours_remote ${TEST_DIR}/test_detours_remote.cpp)
add_test(NAME TEST_detours_remote COMMAND test_destours_remote)

enable_testing()


# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release/lib)