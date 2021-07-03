include_directories(${EIGEN3_INCLUDE_DIR})

ADD_DMP_EXECUTABLE(TARGET naive_matrix_multiplication SOURCES naive_matrix_multiplication.cc)
# target_link_libraries(naive_matrix_multiplication Eigen3::Eigen)
