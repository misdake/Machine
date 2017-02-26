#pragma once

#include "Instruction.h"
#include "program/Program.h"

class Machine;

class Parser {
private:
    Machine& machine;
public:
    Parser(Machine& machine);

    Instruction parseInstruction(const char* input);

    Program parseProgram(const char* input);
};
