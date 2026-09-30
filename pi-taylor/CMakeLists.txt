ADD_DMP_EXECUTABLE(TARGET pi_taylor_sequential SOURCES pi_taylor_sequential.cc)
ADD_DMP_EXECUTABLE(TARGET pi_taylor_parallel SOURCES pi_taylor_parallel.cc)

set(MY_BINARY_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "-> ${CMAKE_CURRENT_BINARY_DIR} <-")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/launch_pi_taylor_template.sh.in
    ${CMAKE_CURRENT_BINARY_DIR}/launch_pi_taylor.sh
    @ONLY
)

file(CHMOD ${CMAKE_BINARY_DIR}/launch_pi_taylor.sh
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                GROUP_READ GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE
)

