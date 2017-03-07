#pragma once

#include "Instruction.h"
#include "program/Program.h"

class MachinePrototype;

class Parser {
private:
    MachinePrototype& machine;
public:
    Parser(MachinePrototype& machine);

    Instruction parseInstruction(const char* input);

    Program parseProgram(const char* input);
};
