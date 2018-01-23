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

    std::string gen(const Instruction& instruction) const;
    std::string gen(const Program& program) const;
    void print(const Instruction& instruction) const;
    void print(const Program& program) const;
};
