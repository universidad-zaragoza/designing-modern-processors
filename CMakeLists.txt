cmake_minimum_required (VERSION 3.25)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(AddDmpExecutable)
include(CheckCXXCompilerFlag)

project (DESIGNING_MODERN_PROCESSORS VERSION 0.1 LANGUAGES CXX)

# Set C++ standard using cache variables for user override
set(CMAKE_CXX_STANDARD 11 CACHE STRING "C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(OpenMP)

option(CUBLAS "Enables cuBLAS matrix multiplication code" ON)

if(CUBLAS)
  find_package(cuBLAS REQUIRED)
endif()

# Compiler feature checks (use generator expressions for modern CMake)
include(CheckCXXCompilerFlag)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  check_cxx_compiler_flag("-march=native" CF_MARCH_NATIVE)
  if(CF_MARCH_NATIVE)
    add_compile_options(-march=native)
  endif()
  check_cxx_compiler_flag("-ftree-vectorize" CF_FTREE_VECTORIZE)
  if(CF_FTREE_VECTORIZE)
    add_compile_options(-ftree-vectorize)
  endif()
endif()

add_subdirectory(pi-taylor)
add_subdirectory(matrix-multiplication)

# Configuration summary
message(STATUS "=== Configuration Summary ===")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "cuBLAS enabled: ${CUBLAS}")
message(STATUS "Eigen3: ${Eigen3_DIR}")
message(STATUS "Threads: ${Threads_FOUND}")
message(STATUS "OpenMP: ${OpenMP_FOUND}")
message(STATUS "=============================")
