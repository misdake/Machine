#include "Printer.h"

#include <iostream>

#include "Instruction.h"
#include "program/Program.h"
#include "machine/Machine.h"

Printer::Printer(MachinePrototype& machine)
        : machine(machine) {

}

Printer::~Printer() {

}

std::string dataImm(const Data& data) {
    char buf[16];
    sprintf(buf, "%d", data.i);
    return std::string(buf);
}

std::string dataReg(const Data& data) {
    char buf[16];
    sprintf(buf, "r%d", data.i);
    return std::string(buf);
}

#define INST0() sprintf(buf, format.c_str(), name.c_str()); break;
#define INST1(r0) sprintf(buf, format.c_str(), name.c_str(), r0.c_str()); break;
#define INST2(r0, r1) sprintf(buf, format.c_str(), name.c_str(), r0.c_str(), r1.c_str()); break;
#define INST3(r0, r1, r2) sprintf(buf, format.c_str(), name.c_str(), r0.c_str(), r1.c_str(), r2.c_str()); break;

std::string Printer::print(const Instruction& instruction) {
    char buf[128];
    buf[0] = '\0';
    const std::string& nameW = machine.opCodeName(instruction.opCode);
    unsigned int i = nameW.find_last_of('_');

    std::string name = i != std::string::npos ? nameW.substr(0, i) : nameW;
    std::string format = machine.opCodeForamt(instruction.opCode);
    OpType type = machine.opCodeType(instruction.opCode);
    std::string r0 = dataReg(instruction.oprand0);
    std::string r1 = dataReg(instruction.oprand1);
    std::string r2 = dataReg(instruction.oprand2);
    std::string i0 = dataImm(instruction.oprand0);
    std::string i1 = dataImm(instruction.oprand1);
    std::string i2 = dataImm(instruction.oprand2);
    switch (type) {
        case OpType::N: INST0()
        case OpType::R: INST1(r0)
        case OpType::I: INST1(i0)
        case OpType::RR: INST2(r0, r1)
        case OpType::RI: INST2(r0, i1)
        case OpType::II: INST2(i0, i1)
        case OpType::RRR: INST3(r0, r1, r2)
        case OpType::RRI: INST3(r0, r1, i2)
        case OpType::RII: INST3(r0, i1, i2)
        case OpType::III: INST3(i0, i1, i2)
    }
    return std::string(buf);
}

std::string Printer::print(const Program& program) {
    std::string all;
    for (const Instruction& instruction : program.instructions) {
        std::string line = print(instruction);
        all += line + "\n";
    }
    return all;
}
