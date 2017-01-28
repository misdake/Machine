cmake_minimum_required(VERSION 3.6)
project(Machine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES example/main.cpp src/machine/Machine.cpp src/machine/Machine.h src/program/Program.cpp src/program/Program.h src/instruction/Instruction.cpp src/instruction/Instruction.h)
add_executable(Machine ${SOURCE_FILES})