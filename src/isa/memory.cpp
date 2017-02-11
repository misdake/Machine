#include "memory.h"

#include "../instruction/Instruction.h"
#include "../machine/Machine.h"

void defineMemory(Machine& machine) {
    machine.define("read_reg_rr", OpType::RR, [](Machine& m, const Instruction& instruction) -> jumpdiff {
        m.reg(instruction.oprand1.i).i = m.reg(m.reg(instruction.oprand0.i).i).i;
        return 0;
    });
    machine.define("write_reg_rr", OpType::RR, [](Machine& m, const Instruction& instruction) -> jumpdiff {
        m.reg(m.reg(instruction.oprand0.i).i).i = m.reg(instruction.oprand1.i).i;
        return 0;
    });
}