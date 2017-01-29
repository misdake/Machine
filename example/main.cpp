#include <iostream>
#include "../src/instruction/Instruction.h"
#include "../src/machine/Machine.h"

int main() {
    Machine machine;
    machine.defineInstruction(0x1, "print float", [](Machine& _machine, const Instruction& instruction) {
        std::cout << instruction.oprand0.f << std::endl;
    });
    machine.defineInstruction(0x2, "print int", [](Machine& _machine, const Instruction& instruction) {
        std::cout << instruction.oprand0.i << std::endl;
    });
    machine.defineInstruction(0x3, "write register", [](Machine& _machine, const Instruction& instruction) {
        _machine.registers[instruction.oprand0.i].i = instruction.oprand1.i;
        std::cout << "r[" << instruction.oprand0.i << "] <- " << instruction.oprand1.i << std::endl;
    });
    machine.defineInstruction(0x4, "read register", [](Machine& _machine, const Instruction& instruction) {
        std::cout << "r[" << instruction.oprand0.i << "] =  " << _machine.registers[instruction.oprand0.i].i << std::endl;
    });

    Instruction i1;
    i1.opcode = 0x1;
    i1.oprand0.f = 5.2f;
    Instruction i2;
    i2.opcode = 0x2;
    i2.oprand0.i = 1234;
    Instruction i3;
    i3.opcode = 0x2;
    i3.oprand0.i = 4321;
    Instruction i4;
    i4.opcode = 0x3;
    i4.oprand0.i = 4;
    i4.oprand1.i = 5678;
    Instruction i5;
    i5.opcode = 0x4;
    i5.oprand0.i = 4;
    Instruction i6;
    i6.opcode = 0x3;
    i6.oprand0.i = 8;
    i6.oprand1.i = 91011;
    Instruction i7;
    i7.opcode = 0x4;
    i7.oprand0.i = 8;

    Program program{{i1, i2, i3, i4, i5, i6, i7}};
    machine.run(program);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}