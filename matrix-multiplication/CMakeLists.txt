include_directories(${CMAKE_CURRENT_SOURCE_DIR}) # for constants.h

ADD_DMP_EXECUTABLE(TARGET naive_matrix_multiplication SOURCES naive_matrix_multiplication.cc)
target_include_directories(naive_matrix_multiplication PRIVATE ${EIGEN3_INCLUDE_DIR})

ADD_DMP_EXECUTABLE(TARGET eigen_matrix_multiplication SOURCES eigen_matrix_multiplication.cc)
target_include_directories(eigen_matrix_multiplication PRIVATE ${EIGEN3_INCLUDE_DIR})

ADD_DMP_EXECUTABLE(TARGET eigen_parallel_matrix_multiplication SOURCES eigen_matrix_multiplication.cc)
target_compile_options(eigen_parallel_matrix_multiplication PUBLIC "-fopenmp")
target_include_directories(eigen_parallel_matrix_multiplication PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(eigen_parallel_matrix_multiplication ${OpenMP_CXX_LIBRARIES})

if(CUBLAS_FOUND)
  ADD_DMP_EXECUTABLE(TARGET cublas_parallel_matrix_multiplication SOURCES cublas_matrix_multiplication.cc)
  target_include_directories(cublas_parallel_matrix_multiplication PRIVATE ${CUBLAS_INCLUDE_DIRS})
  target_include_directories(cublas_parallel_matrix_multiplication PRIVATE "${CMAKE_SOURCE_DIR}/external/include/cublas")
  target_link_libraries(cublas_parallel_matrix_multiplication ${CUBLAS_LIBRARIES} ${CUDA_LIBRARIES})
endif(CUBLAS_FOUND)
