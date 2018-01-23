#include "Machine.h"

#define R0 machine.reg(instruction.oprand0.i)
#define R1 machine.reg(instruction.oprand1.i)
#define R2 machine.reg(instruction.oprand2.i)
#define I0 instruction.oprand0
#define I1 instruction.oprand1
#define I2 instruction.oprand2

OpCode MachinePrototype::getOpCode(const char* name) {
    auto iterator = nameMap.find(name);
    if (iterator == nameMap.end()) {
        printf("unknown instruction '%s'", name);
        return -1;
    }
    return iterator->second;
}

const std::string& MachinePrototype::opCodeName(OpCode opCode) {
    InstructionDefinition& def = defs[opCode];
    return def.name;
}

const std::string& MachinePrototype::opCodeForamt(OpCode opCode) {
    InstructionDefinition& def = defs[opCode];
    return def.format;
}

OpType MachinePrototype::opCodeType(OpCode opCode) {
    InstructionDefinition& def = defs[opCode];
    return def.opType;
}

#define functionCall0() [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return function(); }
#define functionCall1(a) [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return function(a); }
#define functionCall2(a, b) [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return function(a, b); }
#define functionCall3(a, b, c) [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return function(a, b, c); }

void MachinePrototype::define(const std::string& name, const std::string& format, OpType opType, std::function<jumpdiff(Machine&, const Instruction&)> function) {
    auto iterator = nameMap.find(name);
    std::string f = "%s " + format;
    if (iterator == nameMap.end()) {
        OpCode opCode = nameMap[name] = next++;
        defs.push_back(InstructionDefinition{name, f, opCode, opType, function});
//        printf("define instruction '%s'", name);
    } else {
        OpCode opCode = nameMap[name];
        defs[opCode] = InstructionDefinition{name, f, opCode, opType, function};
        printf("redefine instruction '%s'", name);
    }
}

void MachinePrototype::defineN(const std::string& name, FunctionN&& function) { define(name + "_", "", OpType::N, functionCall0()); }
void MachinePrototype::defineN(const std::string& name, const std::string& format, FunctionN&& function) { define(name + "_", format, OpType::N, functionCall0()); }

void MachinePrototype::defineR(const std::string& name, FunctionR&& function) { define(name + "_r", "%s", OpType::R, functionCall1(R0)); }
void MachinePrototype::defineR(const std::string& name, const std::string& format, FunctionR&& function) { define(name + "_r", format, OpType::R, functionCall1(R0)); }

void MachinePrototype::defineI(const std::string& name, FunctionI&& function) { define(name + "_i", "%s", OpType::I, functionCall1(I0)); }
void MachinePrototype::defineI(const std::string& name, const std::string& format, FunctionI&& function) { define(name + "_i", format, OpType::I, functionCall1(I0)); }

void MachinePrototype::defineRR(const std::string& name, FunctionRR&& function) { define(name + "_rr", "%s, %s", OpType::RR, functionCall2(R0, R1)); }
void MachinePrototype::defineRR(const std::string& name, const std::string& format, FunctionRR&& function) { define(name + "_rr", format, OpType::RR, functionCall2(R0, R1)); }

void MachinePrototype::defineRI(const std::string& name, FunctionRI&& function) { define(name + "_ri", "%s, %s", OpType::RI, functionCall2(R0, I1)); }
void MachinePrototype::defineRI(const std::string& name, const std::string& format, FunctionRI&& function) { define(name + "_ri", format, OpType::RI, functionCall2(R0, I1)); }

void MachinePrototype::defineII(const std::string& name, FunctionII&& function) { define(name + "_ii", "%s, %s", OpType::II, functionCall2(I0, I1)); }
void MachinePrototype::defineII(const std::string& name, const std::string& format, FunctionII&& function) { define(name + "_ii", format, OpType::II, functionCall2(I0, I1)); }

void MachinePrototype::defineRRR(const std::string& name, FunctionRRR&& function) { define(name + "_rrr", "%s, %s, %s", OpType::RRR, functionCall3(R0, R1, R2)); }
void MachinePrototype::defineRRR(const std::string& name, const std::string& format, FunctionRRR&& function) { define(name + "_rrr", format, OpType::RRR, functionCall3(R0, R1, R2)); }

void MachinePrototype::defineRRI(const std::string& name, FunctionRRI&& function) { define(name + "_rri", "%s, %s, %s", OpType::RRI, functionCall3(R0, R1, I2)); }
void MachinePrototype::defineRRI(const std::string& name, const std::string& format, FunctionRRI&& function) { define(name + "_rri", format, OpType::RRI, functionCall3(R0, R1, I2)); }

void MachinePrototype::defineRII(const std::string& name, FunctionRII&& function) { define(name + "_rii", "%s, %s, %s", OpType::RII, functionCall3(R0, I1, I2)); }
void MachinePrototype::defineRII(const std::string& name, const std::string& format, FunctionRII&& function) { define(name + "_rii", format, OpType::RII, functionCall3(R0, I1, I2)); }

void MachinePrototype::defineIII(const std::string& name, FunctionIII&& function) { define(name + "_iii", "%s, %s, %s", OpType::III, functionCall3(I0, I1, I2)); }
void MachinePrototype::defineIII(const std::string& name, const std::string& format, FunctionIII&& function) { define(name + "_iii", format, OpType::III, functionCall3(I0, I1, I2)); }
