cmake_minimum_required (VERSION 3.1)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(AddDmpExecutable)

project (DESIGNING_MODERN_PROCESSORS CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# disable clang-tidy to avoid compilation issues
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(OpenMP)

option(CUBLAS "Enables cuBLAS matrix multiplication code" ON)

if(CUBLAS)
  find_package(cuBLAS)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-march=native -ftree-vectorize)
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(pi-taylor)
add_subdirectory(matrix-multiplication)
