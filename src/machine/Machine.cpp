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

OpType Machine::opCodeType(OpCode opCode) {
    InstructionDefinition& def = defs[opCode];
    return def.opType;
}

void Machine::define(const std::string& name, OpType opType, std::function<jumpdiff(Machine&, const Instruction&)> function) {
    auto iterator = nameMap.find(name);
    if (iterator == nameMap.end()) {
        OpCode opCode = nameMap[name] = next++;
        defs.push_back(InstructionDefinition{name, opCode, opType, function});
//            std::cout << "define instruction '" << name << "'" << std::endl;
    } else {
        OpCode opCode = nameMap[name];
        defs[opCode] = InstructionDefinition{name, opCode, opType, function};
        std::cout << "redefine instruction '" << name << "'" << std::endl;
    }
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


void Machine::defineN(const std::string& name, FunctionN&& function) {
    define(name+ "_", OpType::N, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
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

void Machine::defineRII(const std::string& name, FunctionRII&& function) {
    define(name + "_rii", OpType::RII, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(R0, I1, I2);
    });
}
void Machine::defineIII(const std::string& name, FunctionIII&& function) {
    define(name + "_iii", OpType::III, [=](Machine& machine, const Instruction& instruction) -> jumpdiff {
        return function(I0, I1, I2);
    });
}
Data& Machine::reg(int32_t addr) {
    if (addr < 0) addr = 0;
    if (addr >= registerCount) addr = registerCount - 1;
    return registers[addr];
}
