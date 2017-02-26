cmake_minimum_required(VERSION 3.6)
project(Machine)

set(CMAKE_CXX_STANDARD 11)

# library files
FILE(GLOB_RECURSE LIB_SOURCE src/*.cpp)
FILE(GLOB_RECURSE LIB_HEADER src/*.h)

# example files
FILE(GLOB_RECURSE EXAMPLE_SOURCE example/*.cpp)
FILE(GLOB_RECURSE EXAMPLE_HEADER example/*.h)

#add static library target and example target
add_library(Machine STATIC ${LIB_SOURCE} ${LIB_HEADER})
include_directories(Machine "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable(MachineExample ${EXAMPLE_SOURCE} ${EXAMPLE_HEADER})
target_link_libraries(MachineExample Machine)

# build include/library directories
SET(BUILD_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/include")
SET(BUILD_LIBRARY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/lib")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${BUILD_INCLUDE_DIRECTORY})
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${BUILD_LIBRARY_DIRECTORY})

IF (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    # copy headers to BUILD_INCLUDE_DIRECTORY after build
    add_custom_command(TARGET Machine POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E make_directory
            ${BUILD_INCLUDE_DIRECTORY})
    FILE(GLOB_RECURSE RELATIVE_LIB_HEADER RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
    foreach (FILENAME ${RELATIVE_LIB_HEADER})
        #    MESSAGE("${CMAKE_CURRENT_SOURCE_DIR}/src/${FILENAME} => ${BUILD_INCLUDE_DIRECTORY}/${FILENAME}")
        set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/${FILENAME}")
        set(DST "${BUILD_INCLUDE_DIRECTORY}/${FILENAME}")

        add_custom_command(TARGET Machine POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy ${SRC} ${DST})
    endforeach (FILENAME)

    # copy library to BUILD_LIBRARY_DIRECTORY after build
    add_custom_command(TARGET Machine POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E make_directory
            ${BUILD_LIBRARY_DIRECTORY})
    add_custom_command(TARGET Machine POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy
            "$<TARGET_FILE:Machine>"
            ${BUILD_LIBRARY_DIRECTORY})
ENDIF (${CMAKE_BUILD_TYPE} STREQUAL "Release")