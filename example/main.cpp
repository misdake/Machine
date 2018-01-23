#include <iostream>

#include <isa/isa_all.h>
#include <instruction/Instruction.h>
#include <machine/Machine.h>
#include <instruction/Parser.h>
#include <instruction/Printer.h>

int main() {
    MachinePrototype prototype(16, 16);
    defineArithmetic(prototype);
    defineJump(prototype);
    defineMemory(prototype);

    prototype.defineN("hello_world", []() -> jumpdiff {
            std::cout << "Hello, World!" << std::endl;
            return 0;
        });
    prototype.defineR("print_reg", [](Reg reg) -> jumpdiff {
        std::cout << reg.i << std::endl;
        return 0;
    });

    Parser parser(prototype);
    Program program = parser.parseProgram(
            ""
                    "hello_world;"
                    "set r0, 0;"
                    "set r1, 1;"
                    "set r2, r0;"
                    "add r2, r1;"
                    "print_reg r2;"
                    "set r0, r1;"
                    "set r1, r2;"
                    "jl r2, 100, -6;"
    );

    Printer printer(prototype);
    printer.print(program);

    Machine machine(prototype);
    machine.run(program);
    machine.printReg();

    return 0;
}