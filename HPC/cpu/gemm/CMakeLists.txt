cmake_minimum_required(VERSION 3.20)  # 设置 CMake 最低版本
project(GEMM_CPU_Project)  # 项目名称

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|Intel")
    add_compile_options(-mavx512f)
endif()

# 查找 OpenBLAS 库
find_package(OpenBLAS REQUIRED)

# 设置源代码文件
file(GLOB_RECURSE SOURCES
    "source/*.cpp"
)

# 添加头文件路径
include_directories(
    include
    ${OpenBLAS_INCLUDE_DIRS}  # 添加 OpenBLAS 头文件路径
)

# 添加可执行文件
add_executable(gemm_main
    demo/main.cpp
    ${SOURCES}
)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|Intel")
    # 定义针对 version7.cpp 的优化选项
    set_source_files_properties(source/version7.cpp
        PROPERTIES
            COMPILE_OPTIONS "-O3;-ffast-math;-march=native"  # 启用 O3 优化和快速数学
    )
endif()

# 链接 OpenBLAS 库
target_link_libraries(gemm_main
    ${OpenBLAS_LIBRARIES}  # 链接 OpenBLAS 库
)

# 自定义清理目标
add_custom_target(clean_times
    COMMAND rm -f ${CMAKE_BINARY_DIR}/kernel_timings.txt
    COMMENT "Removing kernel timings file..."
)