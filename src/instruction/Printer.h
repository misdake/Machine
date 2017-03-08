#pragma once

#include <string>

class MachinePrototype;
struct Instruction;
struct Program;

class Printer {
private:
    MachinePrototype& machine;
public:
    Printer(MachinePrototype& machine);
    ~Printer();

    std::string print(const Instruction& instruction);
    std::string print(const Program& program);
};
