#include "jump.h"

#include "machine/Machine.h"

#define R0 machine.reg(instruction.oprand0.i).i
#define R1 machine.reg(instruction.oprand1.i).i
#define R2 machine.reg(instruction.oprand2.i).i
#define I0 instruction.oprand0.i
#define I1 instruction.oprand1.i
#define I2 instruction.oprand2.i

void defineJump(MachinePrototype& machine) {
    machine.define("jl_rrr", "%s < %s => pc += %s", OpType::RRR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 < R1 ? R2 : 0; });
    machine.define("jl_rri", "%s < %s => pc += %s", OpType::RRI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 < R1 ? I2 : 0; });
    machine.define("jl_rii", "%s < %s => pc += %s", OpType::RII, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 < I1 ? I2 : 0; });
    machine.define("jne_rrr", "%s != %s => pc += %s", OpType::RRR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 != R1 ? R2 : 0; });
    machine.define("jne_rri", "%s != %s => pc += %s", OpType::RRI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 != R1 ? I2 : 0; });
    machine.define("jne_rii", "%s != %s => pc += %s", OpType::RII, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 != I1 ? I2 : 0; });
    machine.define("je_rrr", "%s == %s => pc += %s", OpType::RRR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 == R1 ? R2 : 0; });
    machine.define("je_rri", "%s == %s => pc += %s", OpType::RRI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 == R1 ? I2 : 0; });
    machine.define("je_rii", "%s == %s => pc += %s", OpType::RII, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 == I1 ? I2 : 0; });
    machine.define("jg_rrr", "%s > %s => pc += %s", OpType::RRR, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 > R1 ? R2 : 0; });
    machine.define("jg_rri", "%s > %s => pc += %s", OpType::RRI, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 > R1 ? I2 : 0; });
    machine.define("jg_rii", "%s > %s => pc += %s", OpType::RII, [=](Machine& machine, const Instruction& instruction) -> jumpdiff { return R0 > I1 ? I2 : 0; });
}