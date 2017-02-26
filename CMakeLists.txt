cmake_minimum_required(VERSION 3.6)
project(Machine)

set(CMAKE_CXX_STANDARD 11)

FILE(GLOB_RECURSE LIB_SOURCE src/*.cpp)
FILE(GLOB_RECURSE LIB_HEADER src/*.h)

FILE(GLOB_RECURSE EXAMPLE_SOURCE example/*.cpp)
FILE(GLOB_RECURSE EXAMPLE_HEADER example/*.h)


add_library(Machine ${LIB_SOURCE} ${LIB_HEADER})
add_executable(MachineExample ${EXAMPLE_SOURCE} ${EXAMPLE_HEADER})
target_link_libraries(MachineExample Machine)