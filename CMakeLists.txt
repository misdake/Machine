cmake_minimum_required(VERSION 3.6)
project(Machine)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        example/main.cpp

        src/machine/Machine.cpp src/machine/Machine.h
        src/program/Program.cpp src/program/Program.h
        src/instruction/Instruction.cpp src/instruction/Instruction.h
        src/machine/Data.cpp src/machine/Data.h

        src/isa/all.h
        src/isa/arithmetic.cpp src/isa/arithmetic.h
        src/isa/logic.cpp src/isa/logic.h
        src/isa/memory.cpp src/isa/memory.h
        src/isa/jump.h src/isa/jump.cpp)
add_executable(Machine ${SOURCE_FILES})