#include "Machine.h"

#define R0 machine.registers[instruction.oprand0.i]
#define R1 machine.registers[instruction.oprand1.i]
#define R2 machine.registers[instruction.oprand2.i]
#define I0 instruction.oprand0
#define I1 instruction.oprand1
#define I2 instruction.oprand2

Machine::Machine(unsigned int registerCount) {
    this->registerCount = registerCount;
    registers = new Data[registerCount];
    next = 0;
}

Machine::~Machine() {
    delete[] registers;
}

OpCode Machine::getOpCode(const char* name) {
    auto iterator = nameMap.find(name);
    if (iterator == nameMap.end()) {
        std::cout << "unknown instruction '" << name << "'" << std::endl;
        return -1;
    }
    return iterator->second;
}

const std::string& Machine::opCodeName(OpCode opCode) {
    InstructionDefinition& def = defs[opCode];
    return def.name;
}

const std::string& Machine::opCodeForamt(OpCode opCode) {
    InstructionDefinition& def = defs[opCode];
    return def.format;
}

OpType Machine::opCodeType(OpCode opCode) {
    InstructionDefinition& def = defs[opCode];
    return def.opType;
}

void Machine::run(const Program& program) {
    int min = 0, max = program.instructions.size() - 1;
    int pointer = 0;
    while (pointer <= max) {
        jumpdiff i = run(program.instructions[pointer]);
        pointer += i + 1;
        if (pointer < min) pointer = min;
    }
}

jumpdiff Machine::run(const Instruction& instruction) {
    if (instruction.opCode >= 0) {
        InstructionDefinition& def = defs[instruction.opCode];
        return def.function(*this, instruction);
    }
    return 0;
}

Data& Machine::reg(int32_t addr) {
    if (addr < 0) addr = 0;
    if (addr >= registerCount) addr = registerCount - 1;
    return registers[addr];
}

#define functionCall0() [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return function(); }
#define functionCall1(a) [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return function(a); }
#define functionCall2(a, b) [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return function(a, b); }
#define functionCall3(a, b, c) [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return function(a, b, c); }

void Machine::define(const std::string& name, const std::string& format, OpType opType, std::function<jumpdiff(Machine&, const Instruction&)> function) {
    auto iterator = nameMap.find(name);
    std::string f = "%s " + format;
    if (iterator == nameMap.end()) {
        OpCode opCode = nameMap[name] = next++;
        defs.push_back(InstructionDefinition{name, f, opCode, opType, function});
//            std::cout << "define instruction '" << name << "'" << std::endl;
    } else {
        OpCode opCode = nameMap[name];
        defs[opCode] = InstructionDefinition{name, f, opCode, opType, function};
        std::cout << "redefine instruction '" << name << "'" << std::endl;
    }
}

void Machine::defineN(const std::string& name, FunctionN&& function) { define(name + "_", "", OpType::N, functionCall0()); }
void Machine::defineN(const std::string& name, const std::string& format, FunctionN&& function) { define(name + "_", format, OpType::N, functionCall0()); }

void Machine::defineR(const std::string& name, FunctionR&& function) { define(name + "_r", "%s", OpType::R, functionCall1(R0)); }
void Machine::defineR(const std::string& name, const std::string& format, FunctionR&& function) { define(name + "_r", format, OpType::R, functionCall1(R0)); }

void Machine::defineI(const std::string& name, FunctionI&& function) { define(name + "_i", "%s", OpType::I, functionCall1(I0)); }
void Machine::defineI(const std::string& name, const std::string& format, FunctionI&& function) { define(name + "_i", format, OpType::I, functionCall1(I0)); }

void Machine::defineRR(const std::string& name, FunctionRR&& function) { define(name + "_rr", "%s, %s", OpType::RR, functionCall2(R0, R1)); }
void Machine::defineRR(const std::string& name, const std::string& format, FunctionRR&& function) { define(name + "_rr", format, OpType::RR, functionCall2(R0, R1)); }

void Machine::defineRI(const std::string& name, FunctionRI&& function) { define(name + "_ri", "%s, %s", OpType::RI, functionCall2(R0, I1)); }
void Machine::defineRI(const std::string& name, const std::string& format, FunctionRI&& function) { define(name + "_ri", format, OpType::RI, functionCall2(R0, I1)); }

void Machine::defineII(const std::string& name, FunctionII&& function) { define(name + "_ii", "%s, %s", OpType::II, functionCall2(I0, I1)); }
void Machine::defineII(const std::string& name, const std::string& format, FunctionII&& function) { define(name + "_ii", format, OpType::II, functionCall2(I0, I1)); }

void Machine::defineRRR(const std::string& name, FunctionRRR&& function) { define(name + "_rrr", "%s, %s, %s", OpType::RRR, functionCall3(R0, R1, R2)); }
void Machine::defineRRR(const std::string& name, const std::string& format, FunctionRRR&& function) { define(name + "_rrr", format, OpType::RRR, functionCall3(R0, R1, R2)); }

void Machine::defineRRI(const std::string& name, FunctionRRI&& function) { define(name + "_rri", "%s, %s, %s", OpType::RRI, functionCall3(R0, R1, I2)); }
void Machine::defineRRI(const std::string& name, const std::string& format, FunctionRRI&& function) { define(name + "_rri", format, OpType::RRI, functionCall3(R0, R1, I2)); }

void Machine::defineRII(const std::string& name, FunctionRII&& function) { define(name + "_rii", "%s, %s, %s", OpType::RII, functionCall3(R0, I1, I2)); }
void Machine::defineRII(const std::string& name, const std::string& format, FunctionRII&& function) { define(name + "_rii", format, OpType::RII, functionCall3(R0, I1, I2)); }

void Machine::defineIII(const std::string& name, FunctionIII&& function) { define(name + "_iii", "%s, %s, %s", OpType::III, functionCall3(I0, I1, I2)); }
void Machine::defineIII(const std::string& name, const std::string& format, FunctionIII&& function) { define(name + "_iii", format, OpType::III, functionCall3(I0, I1, I2)); }
