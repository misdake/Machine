#include <iostream>
#include "../src/instruction/Instruction.h"
#include "../src/machine/Machine.h"

int main() {
    Machine machine(16);
    machine.defineN("hello world", 0x1, []() {
        std::cout << "Hello, World!" << std::endl;
    });

    machine.defineRI("r0=i1", 0x2, [](Data& reg, const Data& imm) {
        reg.i = imm.i;
    });
    machine.defineR("print r0", 0x3, [](Data& reg) {
        std::cout << reg.i << std::endl;
    });

    Instruction i0(0x1);
    Instruction i1(0x2, 5, 123);
    Instruction i2(0x3, 5);

    Program program{{i0, i1, i2}};
    machine.run(program);
    return 0;
}