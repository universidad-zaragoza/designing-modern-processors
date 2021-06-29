macro(ADD_DMP_EXECUTABLE)
    set(options "")
    set(oneValueArgs TARGET)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(ADD_DMP_EXECUTABLE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    add_executable("${ADD_DMP_EXECUTABLE_TARGET}" ${ADD_DMP_EXECUTABLE_SOURCES})
    target_link_libraries("${ADD_DMP_EXECUTABLE_TARGET}"  Threads::Threads)
    if (MSVC)
      target_compile_options("${ADD_DMP_EXECUTABLE_TARGET}" PRIVATE /W4 /WX)
    else()
      target_compile_options("${ADD_DMP_EXECUTABLE_TARGET}" PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endmacro(ADD_DMP_EXECUTABLE)
