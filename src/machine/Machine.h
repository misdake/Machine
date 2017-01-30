#pragma once

#include <map>
#include <cassert>
#include "../program/Program.h"
#include "../instruction/Instruction.h"

class Machine {
private:
    Data* registers;

    std::map<OpCode, InstructionDefinition> defs;

    void define(const char* name, OpCode opCode, OpType opType, std::function<void(Machine&, const Instruction&)>&& function) {
        //TODO check correctness
        defs.emplace(std::make_pair(opCode, InstructionDefinition{name, opCode, opType, std::move(function)}));
    }

public:
    Machine(unsigned int registerCount) {
        registers = new Data[registerCount];
    }

    ~Machine() {
        delete[] registers;
    }

    void defineN(const char* name, OpCode opCode, FunctionN function);

    void defineR(const char* name, OpCode opCode, FunctionR function);

    void defineI(const char* name, OpCode opCode, FunctionI function);

    void defineRR(const char* name, OpCode opCode, FunctionRR function);

    void defineRI(const char* name, OpCode opCode, FunctionRI function);

    void defineIR(const char* name, OpCode opCode, FunctionIR function);

    void defineII(const char* name, OpCode opCode, FunctionII function);

    void defineRRR(const char* name, OpCode opCode, FunctionRRR function);

    void defineRRI(const char* name, OpCode opCode, FunctionRRI function);

    void defineRIR(const char* name, OpCode opCode, FunctionRIR function);

    void defineRII(const char* name, OpCode opCode, FunctionRII function);

    void defineIRR(const char* name, OpCode opCode, FunctionIRR function);

    void defineIRI(const char* name, OpCode opCode, FunctionIRI function);

    void defineIIR(const char* name, OpCode opCode, FunctionIIR function);

    void defineIII(const char* name, OpCode opCode, FunctionIII function);

    void run(const Program& program) {
        for (auto i = program.instructions.begin(); i != program.instructions.end(); i++) {
            run(*i);
        }
    }

    void run(const Instruction& instruction) {
        auto iterator = defs.find(instruction.opCode);
        if (iterator != defs.end()) {
            InstructionDefinition& def = iterator->second;
            assert(def.opCode == instruction.opCode);
            def.function(*this, instruction);
        }
    }
};


