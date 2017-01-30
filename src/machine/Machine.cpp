#include "Machine.h"

#define R0 machine.registers[instruction.oprand0.i]
#define R1 machine.registers[instruction.oprand1.i]
#define R2 machine.registers[instruction.oprand2.i]
#define I0 instruction.oprand0
#define I1 instruction.oprand1
#define I2 instruction.oprand2

void Machine::defineN(const char* name, FunctionN&& function) {
    define(name, OpType::N, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function();
    });
}

void Machine::defineR(const char* name, FunctionR&& function) {
    define(name, OpType::R, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0);
    });
}

void Machine::defineI(const char* name, FunctionI&& function) {
    define(name, OpType::I, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0);
    });
}

void Machine::defineRR(const char* name, FunctionRR&& function) {
    define(name, OpType::RR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, R1);
    });
}

void Machine::defineRI(const char* name, FunctionRI&& function) {
    define(name, OpType::RI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, I1);
    });
}

void Machine::defineIR(const char* name, FunctionIR&& function) {
    define(name, OpType::IR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, R1);
    });
}

void Machine::defineII(const char* name, FunctionII&& function) {
    define(name, OpType::II, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, I1);
    });
}

void Machine::defineRRR(const char* name, FunctionRRR&& function) {
    define(name, OpType::RRR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, R1, R2);
    });
}

void Machine::defineRRI(const char* name, FunctionRRI&& function) {
    define(name, OpType::RRI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, R1, I2);
    });
}

void Machine::defineRIR(const char* name, FunctionRIR&& function) {
    define(name, OpType::RIR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, I1, R2);
    });
}

void Machine::defineRII(const char* name, FunctionRII&& function) {
    define(name, OpType::RII, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, I1, I2);
    });
}

void Machine::defineIRR(const char* name, FunctionIRR&& function) {
    define(name, OpType::IRR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, R1, R2);
    });
}

void Machine::defineIRI(const char* name, FunctionIRI&& function) {
    define(name, OpType::IRI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, R1, I2);
    });
}

void Machine::defineIIR(const char* name, FunctionIIR&& function) {
    define(name, OpType::IIR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, I1, R2);
    });
}

void Machine::defineIII(const char* name, FunctionIII&& function) {
    define(name, OpType::III, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, I1, I2);
    });
}