#include <iostream>
#include "../src/instruction/Instruction.h"
#include "../src/machine/Machine.h"

int main() {
    Machine machine;
    machine.defineInstruction(0x1, OprandType::f32, [](Machine& _machine, const Instruction& instruction) {
        std::cout << instruction.oprand.f32.oprand0 << std::endl;
    });
    machine.defineInstruction(0x2, OprandType::u32, [](Machine& _machine, const Instruction& instruction) {
        std::cout << instruction.oprand.u32.oprand0 << std::endl;
    });

    Instruction i1;
    i1.opcode = 0x1;
    i1.oprand.f32.oprand0 = 5.2f;
    Instruction i2;
    i2.opcode = 0x2;
    i2.oprand.u32.oprand0 = 1234;
    Instruction i3;
    i3.opcode = 0x2;
    i3.oprand.u32.oprand0 = 4321;

    Program program{{i1, i2, i3}};
    machine.run(program);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}