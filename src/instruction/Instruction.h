#pragma once

#include <functional>
#include "../machine/Data.h"

typedef uint16_t OpCode;

struct Instruction {
    OpCode opCode;
    Data oprand0;
    Data oprand1;
    Data oprand2;

    Instruction(OpCode opCode) {
        this->opCode = opCode;
    }
    Instruction(OpCode opCode, int32_t d0) {
        this->opCode = opCode;
        oprand0.i = d0;
    }
    Instruction(OpCode opCode, int32_t d0, int32_t d1) {
        this->opCode = opCode;
        oprand0.i = d0;
        oprand1.i = d1;
    }
    Instruction(OpCode opCode, int32_t d0, int32_t d1, int32_t d2) {
        this->opCode = opCode;
        oprand0.i = d0;
        oprand1.i = d1;
        oprand2.i = d2;
    }
};

enum class OpType {
    N, R, I, RR, RI, IR, II, RRR, RRI, RIR, RII, IRR, IRI, IIR, III, OTHER
};

class Machine;

typedef std::function<void()> FunctionN;

typedef std::function<void(Data&)> FunctionR;
typedef std::function<void(const Data&)> FunctionI;

typedef std::function<void(Data&, Data&)> FunctionRR;
typedef std::function<void(Data&, const Data&)> FunctionRI;
typedef std::function<void(const Data&, Data&)> FunctionIR;
typedef std::function<void(const Data&, const Data&)> FunctionII;

typedef std::function<void(Data&, Data&, Data&)> FunctionRRR;
typedef std::function<void(Data&, Data&, const Data&)> FunctionRRI;
typedef std::function<void(Data&, const Data&, Data&)> FunctionRIR;
typedef std::function<void(Data&, const Data&, const Data&)> FunctionRII;
typedef std::function<void(const Data&, Data&, Data&)> FunctionIRR;
typedef std::function<void(const Data&, Data&, const Data&)> FunctionIRI;
typedef std::function<void(const Data&, const Data&, Data&)> FunctionIIR;
typedef std::function<void(const Data&, const Data&, const Data&)> FunctionIII;

typedef std::function<void(Machine&, const Instruction&)> InstructionFunction;

struct InstructionDefinition {
    const char* name;
    OpCode opCode;
    OpType opType;
    InstructionFunction function;
};