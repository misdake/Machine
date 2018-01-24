#pragma once

#include <functional>

#include "machine/Data.h"

typedef int16_t OpCode;

struct Instruction {
public:
    const OpCode opCode;
    const Data oprand0;
    const Data oprand1;
    const Data oprand2;

    Instruction(OpCode opCode) : opCode(opCode) {}

    Instruction(OpCode opCode, int32_t d0) : opCode(opCode), oprand0(d0) {}

    Instruction(OpCode opCode, int32_t d0, int32_t d1) : opCode(opCode), oprand0(d0), oprand1(d1) {}

    Instruction(OpCode opCode, int32_t d0, int32_t d1, int32_t d2) : opCode(opCode), oprand0(d0), oprand1(d1), oprand2(d2) {}
};

enum class OpType {
    N, R, I, RR, RI, II, RRR, RRI, RII, III,
};

typedef int32_t jumpdiff;

typedef Data& Reg;
typedef const Data& Imm;

typedef std::function<void()> FunctionN;

typedef std::function<void(Reg)> FunctionR;
typedef std::function<void(Imm)> FunctionI;

typedef std::function<void(Reg, Reg)> FunctionRR;
typedef std::function<void(Reg, Imm)> FunctionRI;
typedef std::function<void(Imm, Imm)> FunctionII;

typedef std::function<void(Reg, Reg, Reg)> FunctionRRR;
typedef std::function<void(Reg, Reg, Imm)> FunctionRRI;
typedef std::function<void(Reg, Imm, Imm)> FunctionRII;
typedef std::function<void(Imm, Imm, Imm)> FunctionIII;