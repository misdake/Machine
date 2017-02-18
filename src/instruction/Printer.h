#pragma once

#include <string>

class Machine;
class Instruction;
class Program;

class Printer {
private:
    Machine& machine;
public:
    Printer(Machine& machine);
    ~Printer();

    std::string print(const Instruction& instruction);
    std::string print(const Program& program);
};
