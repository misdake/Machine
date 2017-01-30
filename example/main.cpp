#include <iostream>
#include "../src/instruction/Instruction.h"
#include "../src/machine/Machine.h"

int main() {
    Machine machine(16);
    machine.defineN("hello world", []() {
        std::cout << "Hello, World!" << std::endl;
    });

    machine.defineRI("=imm", [](Data& reg, const Data& imm) {
        reg.i = imm.i;
    });
    machine.defineR("print r0", [](Data& reg) {
        std::cout << reg.i << std::endl;
    });

    Instruction i0 = machine.instruction("hello world");
    Instruction i1 = machine.instruction("=imm", 5, 123);
    Instruction i2 = machine.instruction("print r0", 5);
    Instruction i3 = machine.instruction("abcde");

    Program program{{i0, i1, i2, i3}};
    machine.run(program);
    return 0;
}