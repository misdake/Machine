#pragma once

#include <iostream>
#include <map>
#include <string>
#include <cassert>
#include "../program/Program.h"
#include "../instruction/Instruction.h"

class Machine;

typedef std::function<jumpdiff(Machine&, const Instruction&)> InstructionFunction;

class Machine {
private:
    struct InstructionDefinition {
        std::string name;
        OpCode opCode;
        OpType opType;
        InstructionFunction function;
    };

    int32_t registerCount;
    Data* registers;

    std::vector<InstructionDefinition> defs;
    std::map<std::string, OpCode> nameMap;
    OpCode next;

public:
    Machine(unsigned int registerCount);

    ~Machine();

    OpCode getOpCode(const char* name);

    void define(const std::string& name, OpType opType, std::function<jumpdiff(Machine&, const Instruction&)> function);

    void defineN(const std::string& name, FunctionN&& function);

    void defineR(const std::string& name, FunctionR&& function);

    void defineI(const std::string& name, FunctionI&& function);

    void defineRR(const std::string& name, FunctionRR&& function);

    void defineRI(const std::string& name, FunctionRI&& function);

    void defineII(const std::string& name, FunctionII&& function);

    void defineRRR(const std::string& name, FunctionRRR&& function);

    void defineRRI(const std::string& name, FunctionRRI&& function);

    void defineRII(const std::string& name, FunctionRII&& function);

    void defineIII(const std::string& name, FunctionIII&& function);

    Instruction instruction(const char* name) {
        return Instruction(getOpCode(name));
    }

    Instruction instruction(const char* name, int32_t d0) {
        return Instruction(getOpCode(name), d0);
    }

    Instruction instruction(const char* name, int32_t d0, int32_t d1) {
        return Instruction(getOpCode(name), d0, d1);
    }

    Instruction instruction(const char* name, int32_t d0, int32_t d1, int32_t d2) {
        return Instruction(getOpCode(name), d0, d1, d2);
    }

    Data& reg(int32_t addr);

    void run(const Program& program);

    jumpdiff run(const Instruction& instruction);

    void printReg() {
        for (int i = 0; i != registerCount; i++) {
            std::cout << "r" << (i < 10 ? "0" : "") << i << ": " << registers[i].i << "\n";
        }
    }
};


