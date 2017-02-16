#include <iostream>

#include "../src/isa/all.h"
#include "../src/instruction/Instruction.h"
#include "../src/machine/Machine.h"
#include "../src/instruction/Parser.h"

int main() {
    Machine machine(16);
    defineArithmetic(machine);
    defineJump(machine);
    defineMemory(machine);

    machine.defineN("hello_world", []() -> jumpdiff {
        std::cout << "Hello, World!" << std::endl;
        return 0;
    });
    machine.defineR("print_reg", [](Reg reg) -> jumpdiff {
        std::cout << reg.i << std::endl;
        return 0;
    });


    Parser parser(machine);

    Program program = parser.parseProgram(
            ""
                    "hello_world;"
                    "set r0, 0;"
                    "print_reg r0;"
                    "write_reg r0, r0;"
                    "add r0, 1;"
                    "jl r0, 10, -4;"
    );
    machine.run(program);
    machine.printReg();
    return 0;
}