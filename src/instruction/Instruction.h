#pragma once

#include <functional>
#include "../machine/Data.h"

typedef uint16_t Opcode;

struct Instruction {
    Opcode opcode;
    Data oprand0;
    Data oprand1;
};

class Machine;
typedef std::function<void(Machine&, const Instruction&)> InstructionFunction;

struct InstructionDefinition {
    Opcode opcode;
    const char* name;
    InstructionFunction function;
};