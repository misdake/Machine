#include "jump.h"

#include "machine/Machine.h"

void defineJump(Machine& machine) {
    machine.defineRRR("jl", "%s < %s => pc += %s", [](Reg r0, Reg r1, Reg r2) -> jumpdiff {
        return r0.i < r1.i ? r2.i : 0;
    });
    machine.defineRRI("jl", "%s < %s => pc += %s", [](Reg r0, Reg r1, Imm i2) -> jumpdiff {
        return r0.i < r1.i ? i2.i : 0;
    });
    machine.defineRII("jl", "%s < %s => pc += %s", [](Reg r0, Imm i1, Imm i2) -> jumpdiff {
        return r0.i < i1.i ? i2.i : 0;
    });

    machine.defineRRR("jne", "%s != %s => pc += %s", [](Reg r0, Reg r1, Reg r2) -> jumpdiff {
        return r0.i != r1.i ? r2.i : 0;
    });
    machine.defineRRI("jne", "%s != %s => pc += %s", [](Reg r0, Reg r1, Imm i2) -> jumpdiff {
        return r0.i != r1.i ? i2.i : 0;
    });
    machine.defineRII("jne", "%s != %s => pc += %s", [](Reg r0, Imm i1, Imm i2) -> jumpdiff {
        return r0.i != i1.i ? i2.i : 0;
    });

    machine.defineRRR("je", "%s == %s => pc += %s", [](Reg r0, Reg r1, Reg r2) -> jumpdiff {
        return r0.i == r1.i ? r2.i : 0;
    });
    machine.defineRRI("je", "%s == %s => pc += %s", [](Reg r0, Reg r1, Imm i2) -> jumpdiff {
        return r0.i == r1.i ? i2.i : 0;
    });
    machine.defineRII("je", "%s == %s => pc += %s", [](Reg r0, Imm i1, Imm i2) -> jumpdiff {
        return r0.i == i1.i ? i2.i : 0;
    });

    machine.defineRRR("jg", "%s > %s => pc += %s", [](Reg r0, Reg r1, Reg r2) -> jumpdiff {
        return r0.i > r1.i ? r2.i : 0;
    });
    machine.defineRRI("jg", "%s > %s => pc += %s", [](Reg r0, Reg r1, Imm i2) -> jumpdiff {
        return r0.i > r1.i ? i2.i : 0;
    });
    machine.defineRII("jg", "%s > %s => pc += %s", [](Reg r0, Imm i1, Imm i2) -> jumpdiff {
        return r0.i > i1.i ? i2.i : 0;
    });
}