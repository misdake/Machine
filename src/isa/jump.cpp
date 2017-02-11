#include "jump.h"

#include "../machine/Machine.h"

void defineJump(Machine& machine) {
    machine.defineRRR("jl", [](Reg r0, Reg r1, Reg r2) -> jumpdiff {
        return r0.i < r1.i ? r2.i : 0;
    });
    machine.defineRRI("jl", [](Reg r0, Reg r1, Imm i2) -> jumpdiff {
        return r0.i < r1.i ? i2.i : 0;
    });
    machine.defineRII("jl", [](Reg r0, Imm i1, Imm i2) -> jumpdiff {
        return r0.i < i1.i ? i2.i : 0;
    });

    machine.defineRRR("jne", [](Reg r0, Reg r1, Reg r2) -> jumpdiff {
        return r0.i != r1.i ? r2.i : 0;
    });
    machine.defineRRI("jne", [](Reg r0, Reg r1, Imm i2) -> jumpdiff {
        return r0.i != r1.i ? i2.i : 0;
    });
    machine.defineRII("jne", [](Reg r0, Imm i1, Imm i2) -> jumpdiff {
        return r0.i != i1.i ? i2.i : 0;
    });

    machine.defineRRR("je", [](Reg r0, Reg r1, Reg r2) -> jumpdiff {
        return r0.i == r1.i ? r2.i : 0;
    });
    machine.defineRRI("je", [](Reg r0, Reg r1, Imm i2) -> jumpdiff {
        return r0.i == r1.i ? i2.i : 0;
    });
    machine.defineRII("je", [](Reg r0, Imm i1, Imm i2) -> jumpdiff {
        return r0.i == i1.i ? i2.i : 0;
    });

    machine.defineRRR("jg", [](Reg r0, Reg r1, Reg r2) -> jumpdiff {
        return r0.i > r1.i ? r2.i : 0;
    });
    machine.defineRRI("jg", [](Reg r0, Reg r1, Imm i2) -> jumpdiff {
        return r0.i > r1.i ? i2.i : 0;
    });
    machine.defineRII("jg", [](Reg r0, Imm i1, Imm i2) -> jumpdiff {
        return r0.i > i1.i ? i2.i : 0;
    });
}