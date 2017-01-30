#pragma once

#include <functional>
#include "../machine/Data.h"

typedef int16_t OpCode;

struct Instruction {
private:
    friend class Machine;

    const OpCode opCode;

public:
    const Data oprand0;
    const Data oprand1;
    const Data oprand2;

    Instruction(OpCode opCode) : opCode(opCode) {}

    Instruction(OpCode opCode, int32_t d0) : opCode(opCode), oprand0(d0) {}

    Instruction(OpCode opCode, int32_t d0, int32_t d1) : opCode(opCode), oprand0(d0), oprand1(d1) {}

    Instruction(OpCode opCode, int32_t d0, int32_t d1, int32_t d2) : opCode(opCode), oprand0(d0), oprand1(d1), oprand2(d2) {}
};

enum class OpType {
    N, R, I, RR, RI, IR, II, RRR, RRI, RIR, RII, IRR, IRI, IIR, III, OTHER
};

typedef int32_t jumpdiff;

typedef std::function<jumpdiff()> FunctionN;

typedef std::function<jumpdiff(Data&)> FunctionR;
typedef std::function<jumpdiff(const Data&)> FunctionI;

typedef std::function<jumpdiff(Data&, Data&)> FunctionRR;
typedef std::function<jumpdiff(Data&, const Data&)> FunctionRI;
typedef std::function<jumpdiff(const Data&, Data&)> FunctionIR;
typedef std::function<jumpdiff(const Data&, const Data&)> FunctionII;

typedef std::function<jumpdiff(Data&, Data&, Data&)> FunctionRRR;
typedef std::function<jumpdiff(Data&, Data&, const Data&)> FunctionRRI;
typedef std::function<jumpdiff(Data&, const Data&, Data&)> FunctionRIR;
typedef std::function<jumpdiff(Data&, const Data&, const Data&)> FunctionRII;
typedef std::function<jumpdiff(const Data&, Data&, Data&)> FunctionIRR;
typedef std::function<jumpdiff(const Data&, Data&, const Data&)> FunctionIRI;
typedef std::function<jumpdiff(const Data&, const Data&, Data&)> FunctionIIR;
typedef std::function<jumpdiff(const Data&, const Data&, const Data&)> FunctionIII;