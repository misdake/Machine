#include <iostream>
#include "../src/instruction/Instruction.h"
#include "../src/machine/Machine.h"

int main() {
    Machine machine(16);
    machine.defineN("hello world", []() -> jumpdiff {
        std::cout << "Hello, World!" << std::endl;
        return 0;
    });
    machine.defineRI("=imm", [](Data& reg, const Data& imm) -> jumpdiff {
        reg.i = imm.i;
        return 0;
    });
    machine.defineRI("+=imm", [](Data& reg, const Data& imm) -> jumpdiff {
        reg.i += imm.i;
        return 0;
    });
    machine.defineRR("+=reg", [](Data& r, Data& d) -> jumpdiff {
        r.i += d.i;
        return 0;
    });
    machine.defineRII("if<imm,j", [](Data& reg, const Data& imm, const Data& j) -> jumpdiff {
        if (reg.i < imm.i) {
            return j.i;
        } else {
            return 0;
        }
    });
    machine.defineR("print r", [](Data& reg) -> jumpdiff {
        std::cout << reg.i << std::endl;
        return 0;
    });

    Program program{{
                            machine.instruction("hello world"),
                            machine.instruction("=imm", 0, 0),
                            machine.instruction("print r", 0),
                            machine.instruction("+=imm", 0, 1),
                            machine.instruction("if<imm,j", 0, 10, -3)
                    }};
    machine.run(program);
    return 0;
}