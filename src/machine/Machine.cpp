#include "Machine.h"

#define R0 machine.registers[instruction.oprand0.i]
#define R1 machine.registers[instruction.oprand1.i]
#define R2 machine.registers[instruction.oprand2.i]
#define I0 instruction.oprand0
#define I1 instruction.oprand1
#define I2 instruction.oprand2

void Machine::defineN(const char* name, OpCode opCode, FunctionN function) {
    define(name, opCode, OpType::N, [&](Machine& machine, const Instruction& instruction) {
        function();
    });
}

void Machine::defineR(const char* name, OpCode opCode, FunctionR function) {
    define(name, opCode, OpType::R, [&](Machine& machine, const Instruction& instruction) {
        function(R0);
    });
}

void Machine::defineI(const char* name, OpCode opCode, FunctionI function) {
    define(name, opCode, OpType::I, [&](Machine& machine, const Instruction& instruction) {
        function(I0);
    });
}

void Machine::defineRR(const char* name, OpCode opCode, FunctionRR function) {
    define(name, opCode, OpType::RR, [&](Machine& machine, const Instruction& instruction) {
        function(R0, R1);
    });
}

void Machine::defineRI(const char* name, OpCode opCode, FunctionRI function) {
    define(name, opCode, OpType::RI, [&](Machine& machine, const Instruction& instruction) {
        function(R0, I1);
    });
}

void Machine::defineIR(const char* name, OpCode opCode, FunctionIR function) {
    define(name, opCode, OpType::IR, [&](Machine& machine, const Instruction& instruction) {
        function(I0, R1);
    });
}

void Machine::defineII(const char* name, OpCode opCode, FunctionII function) {
    define(name, opCode, OpType::II, [&](Machine& machine, const Instruction& instruction) {
        function(I0, I1);
    });
}

void Machine::defineRRR(const char* name, OpCode opCode, FunctionRRR function) {
    define(name, opCode, OpType::RRR, [&](Machine& machine, const Instruction& instruction) {
        function(R0, R1, R2);
    });
}

void Machine::defineRRI(const char* name, OpCode opCode, FunctionRRI function) {
    define(name, opCode, OpType::RRI, [&](Machine& machine, const Instruction& instruction) {
        function(R0, R1, I2);
    });
}

void Machine::defineRIR(const char* name, OpCode opCode, FunctionRIR function) {
    define(name, opCode, OpType::RIR, [&](Machine& machine, const Instruction& instruction) {
        function(R0, I1, R2);
    });
}

void Machine::defineRII(const char* name, OpCode opCode, FunctionRII function) {
    define(name, opCode, OpType::RII, [&](Machine& machine, const Instruction& instruction) {
        function(R0, I1, I2);
    });
}

void Machine::defineIRR(const char* name, OpCode opCode, FunctionIRR function) {
    define(name, opCode, OpType::IRR, [&](Machine& machine, const Instruction& instruction) {
        function(I0, R1, R2);
    });
}

void Machine::defineIRI(const char* name, OpCode opCode, FunctionIRI function) {
    define(name, opCode, OpType::IRI, [&](Machine& machine, const Instruction& instruction) {
        function(I0, R1, I2);
    });
}

void Machine::defineIIR(const char* name, OpCode opCode, FunctionIIR function) {
    define(name, opCode, OpType::IIR, [&](Machine& machine, const Instruction& instruction) {
        function(I0, I1, R2);
    });
}

void Machine::defineIII(const char* name, OpCode opCode, FunctionIII function) {
    define(name, opCode, OpType::III, [&](Machine& machine, const Instruction& instruction) {
        function(I0, I1, I2);
    });
}