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
        machine.defineR("print_reg", [](Reg reg) -> jumpdiff {
            std::cout << reg.i << std::endl;
            return 0;
        });
    }

    Program program{{
                            machine.instruction("hello world"),
                            machine.instruction("set_ri", 0, 0),
                            machine.instruction("print_reg_r", 0),
                            machine.instruction("add_ri", 0, 1),
                            machine.instruction("jl_rii", 0, 10, -3)
                    }};
    machine.run(program);
    return 0;
}