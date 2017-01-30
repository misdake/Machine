#include "Machine.h"

#define R0 machine.registers[instruction.oprand0.i]
#define R1 machine.registers[instruction.oprand1.i]
#define R2 machine.registers[instruction.oprand2.i]
#define I0 instruction.oprand0
#define I1 instruction.oprand1
#define I2 instruction.oprand2

void Machine::defineN(const std::string& name, FunctionN&& function) {
    define(name, OpType::N, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function();
    });
}

void Machine::defineR(const std::string& name, FunctionR&& function) {
    define(name + "_r", OpType::R, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0);
    });
}

void Machine::defineI(const std::string& name, FunctionI&& function) {
    define(name + "_i", OpType::I, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0);
    });
}

void Machine::defineRR(const std::string& name, FunctionRR&& function) {
    define(name + "_rr", OpType::RR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, R1);
    });
}

void Machine::defineRI(const std::string& name, FunctionRI&& function) {
    define(name + "_ri", OpType::RI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, I1);
    });
}

void Machine::defineIR(const std::string& name, FunctionIR&& function) {
    define(name + "_ir", OpType::IR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, R1);
    });
}

void Machine::defineII(const std::string& name, FunctionII&& function) {
    define(name + "_ii", OpType::II, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, I1);
    });
}

void Machine::defineRRR(const std::string& name, FunctionRRR&& function) {
    define(name + "_rrr", OpType::RRR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, R1, R2);
    });
}

void Machine::defineRRI(const std::string& name, FunctionRRI&& function) {
    define(name + "_rri", OpType::RRI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, R1, I2);
    });
}

void Machine::defineRIR(const std::string& name, FunctionRIR&& function) {
    define(name + "_rir", OpType::RIR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, I1, R2);
    });
}

void Machine::defineRII(const std::string& name, FunctionRII&& function) {
    define(name + "_rii", OpType::RII, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, I1, I2);
    });
}

void Machine::defineIRR(const std::string& name, FunctionIRR&& function) {
    define(name + "_irr", OpType::IRR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, R1, R2);
    });
}

void Machine::defineIRI(const std::string& name, FunctionIRI&& function) {
    define(name + "_iri", OpType::IRI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, R1, I2);
    });
}

void Machine::defineIIR(const std::string& name, FunctionIIR&& function) {
    define(name + "_iir", OpType::IIR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, I1, R2);
    });
}

void Machine::defineIII(const std::string& name, FunctionIII&& function) {
    define(name + "_iii", OpType::III, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, I1, I2);
    });
}