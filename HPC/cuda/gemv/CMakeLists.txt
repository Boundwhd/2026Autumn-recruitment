cmake_minimum_required(VERSION 3.20)  # 设置 CMake 最低版本
project(GEMV_Project)  # 项目名称

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用 CUDA 支持
enable_language(CUDA)

file(GLOB_RECURSE SOURCES
    "source/*.cu"
)

# 添加 CUDA 头文件路径
include_directories(
    /usr/local/cuda-11.8/include
    include
)

# 添加可执行文件
add_executable(gemv_main
    demo/main.cpp
    ${SOURCES}
)

# 链接库配置
link_directories(
    /usr/local/cuda-11.8/lib64
)

# 链接 CUDA 和 cuBLAS 库
target_link_libraries(gemv_main
    cudart  # CUDA 运行时库
    cublas  # cuBLAS 库
)

# 设置 CUDA 编译选项
set_target_properties(gemv_main PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON  # 启用可分离编译
    CUDA_RESOLVE_DEVICE_SYMBOLS ON  # 解析设备符号
)

add_custom_target(clean_times
    COMMAND rm -f ${CMAKE_BINARY_DIR}/kernel_timings.txt
    COMMENT "Removing kernel timings file..."
)