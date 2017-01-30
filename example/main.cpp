#include <iostream>

#include "../src/isa/all.h"
#include "../src/instruction/Instruction.h"
#include "../src/machine/Machine.h"

int main() {
    Machine machine(16);
    defineArithmetic(machine);
    defineJump(machine);

    {
        machine.defineN("hello world", []() -> jumpdiff {
            std::cout << "Hello, World!" << std::endl;
            return 0;
        });
        machine.defineR("print r0", [](Data& reg) -> jumpdiff {
            std::cout << reg.i << std::endl;
            return 0;
        });
    }

    Program program{{
                            machine.instruction("hello world"),
                            machine.instruction("set2i", 0, 0),
                            machine.instruction("print r0", 0),
                            machine.instruction("add2i", 0, 1),
                            machine.instruction("jl_ii", 0, 10, -3)
                    }};
    machine.run(program);
    return 0;
}