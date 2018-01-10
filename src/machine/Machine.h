#pragma once

#include <iostream>
#include <map>
#include <string>
#include <cassert>
#include <memory>
#include "program/Program.h"
#include "instruction/Instruction.h"

class MachinePrototype;
class Machine;

typedef std::function<jumpdiff(Machine&, const Instruction&)> InstructionFunction;

struct InstructionDefinition {
    std::string name;
    std::string format;
    OpCode opCode;
    OpType opType;
    InstructionFunction function;
};

class MachinePrototype {
private:
    std::vector<InstructionDefinition> defs;
    std::map<std::string, OpCode> nameMap;
    OpCode next;

public:
    const int32_t registerCount;
    const int32_t paramCount;

    MachinePrototype(int32_t registerCount, int32_t paramCount)
            : registerCount(registerCount), paramCount(paramCount) {
        next = 0;
    }

    ~MachinePrototype() {
    }

    const std::vector<InstructionDefinition>& getDefinitions() const {
        return defs;
    }

    OpCode getOpCode(const char* name);

    const std::string& opCodeName(OpCode opCode);
    const std::string& opCodeForamt(OpCode opCode);
    OpType opCodeType(OpCode opCode);

    void define(const std::string& name, const std::string& format, OpType opType, InstructionFunction function);

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

    void defineN(const std::string& name, const std::string& format, FunctionN&& function);
    void defineR(const std::string& name, const std::string& format, FunctionR&& function);
    void defineI(const std::string& name, const std::string& format, FunctionI&& function);
    void defineRR(const std::string& name, const std::string& format, FunctionRR&& function);
    void defineRI(const std::string& name, const std::string& format, FunctionRI&& function);
    void defineII(const std::string& name, const std::string& format, FunctionII&& function);
    void defineRRR(const std::string& name, const std::string& format, FunctionRRR&& function);
    void defineRRI(const std::string& name, const std::string& format, FunctionRRI&& function);
    void defineRII(const std::string& name, const std::string& format, FunctionRII&& function);
    void defineIII(const std::string& name, const std::string& format, FunctionIII&& function);

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
};

class Machine {
public:
    const int32_t registerCount;
    const int32_t paramCount;
protected:
    std::unique_ptr<Data[]> registers;
    std::unique_ptr<Data[]> params;
    const std::vector<InstructionDefinition>& defs;

public:
    Machine(const MachinePrototype& prototype)
            : registerCount(prototype.registerCount),
              paramCount(prototype.paramCount),
              defs(prototype.getDefinitions()),
              registers(new Data[registerCount]),
              params(new Data[paramCount]) {
    }

    ~Machine() {
    }

    Data& reg(int32_t addr) {
        if (addr < 0) addr = 0;
        if (addr >= registerCount) addr = registerCount - 1;
        return registers.get()[addr];
    }

    Data& param(int32_t addr) {
        if (addr < 0) addr = 0;
        if (addr >= paramCount) addr = paramCount - 1;
        return params.get()[addr];
    }

    virtual void run(const Program& program) {
        size_t min = 0, max = program.instructions.size() - 1;
        size_t pointer = 0;
        while (pointer <= max) {
            jumpdiff i = run(program.instructions[pointer]);
            pointer += i + 1;
            if (pointer < min) pointer = min;
        }
    }

    jumpdiff run(const Instruction& instruction) {
        if (instruction.opCode >= 0) {
            const InstructionDefinition& def = defs.at((unsigned int) instruction.opCode);
            return def.function(*this, instruction);
        }
        return 0;
    }

    void printReg() {
        for (int i = 0; i != registerCount; i++) {
            std::cout << "r" << (i < 10 ? "0" : "") << i << ": " << registers.get()[i].i << "\n";
        }
    }
};


