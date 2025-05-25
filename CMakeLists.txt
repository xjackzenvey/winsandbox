CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(WinSandBox)


# 源代码

set (SRC_DIR src)
include_directories(${SRC_DIR}/include)

# Detours 导入
set (DETOURS_DIR D:/project/open-source/Detours-4.0.1)  
include_directories(${DETOURS_DIR}/include)
link_libraries(${DETOURS_DIR}/lib.X86/detours.lib)


# 测试
set (TEST_DIR tests)
add_executable(test_detours_base ${TEST_DIR}/test_detours_base.cpp)
add_test(NAME TEST_detours_base COMMAND test_detours_base)

add_executable(test_common ${TEST_DIR}/test_common.cpp)
add_test(NAME TEST_common COMMAND test_common)

enable_testing()