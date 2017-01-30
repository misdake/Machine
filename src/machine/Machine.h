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

    Data* registers;

    std::vector<InstructionDefinition> defs;
    std::map<std::string, OpCode> nameMap;
    OpCode next;

public:
    Machine(unsigned int registerCount) {
        registers = new Data[registerCount];
        next = 0;
    }

    ~Machine() {
        delete[] registers;
    }

    OpCode getOpCode(const char* name) {
        auto iterator = nameMap.find(name);
        if (iterator == nameMap.end()) {
            std::cout << "unknown instruction '" << name << "'" << std::endl;
            return -1;
        }
        return iterator->second;
    }

    void define(const std::string& name, OpType opType, std::function<jumpdiff(Machine&, const Instruction&)> function) {
        auto iterator = nameMap.find(name);
        if (iterator == nameMap.end()) {
            OpCode opCode = nameMap[name] = next++;
            defs.push_back(InstructionDefinition{name, opCode, opType, function});
            std::cout << "define instruction '" << name << "'" << std::endl;
        } else {
            OpCode opCode = nameMap[name];
            defs[opCode] = InstructionDefinition{name, opCode, opType, function};
            std::cout << "redefine instruction '" << name << "'" << std::endl;
        }
    }

    void defineN(const std::string& name, FunctionN&& function);

    void defineR(const std::string& name, FunctionR&& function);

    void defineI(const std::string& name, FunctionI&& function);

    void defineRR(const std::string& name, FunctionRR&& function);

    void defineRI(const std::string& name, FunctionRI&& function);

    void defineIR(const std::string& name, FunctionIR&& function);

    void defineII(const std::string& name, FunctionII&& function);

    void defineRRR(const std::string& name, FunctionRRR&& function);

    void defineRRI(const std::string& name, FunctionRRI&& function);

    void defineRIR(const std::string& name, FunctionRIR&& function);

    void defineRII(const std::string& name, FunctionRII&& function);

    void defineIRR(const std::string& name, FunctionIRR&& function);

    void defineIRI(const std::string& name, FunctionIRI&& function);

    void defineIIR(const std::string& name, FunctionIIR&& function);

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

    void run(const Program& program) {
        int min = 0, max = program.instructions.size() - 1;
        int pointer = 0;
        while (pointer <= max) {
            jumpdiff i = run(program.instructions[pointer]);
            pointer += i + 1;
            if (pointer < min) pointer = min;
        }
    }

    jumpdiff run(const Instruction& instruction) {
        if (instruction.opCode >= 0) {
            InstructionDefinition& def = defs[instruction.opCode];
            return def.function(*this, instruction);
        }
        return 0;
    }
};


