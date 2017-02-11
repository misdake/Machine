#include "arithmetic.h"

#include <cmath>

#include "../machine/Machine.h"

void defineArithmetic(Machine& machine) {
    machine.defineR("abs", [](Reg r0) -> jumpdiff {
        r0.i = abs(r0.i);
        return 0;
    });
    machine.defineRR("abs", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i = abs(r1.i);
        return 0;
    });
    machine.defineRI("set", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i = i1.i;
        return 0;
    });
    machine.defineRR("set", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i = r1.i;
        return 0;
    });
    machine.defineRI("add", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i += i1.i;
        return 0;
    });
    machine.defineRR("add", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i += r1.i;
        return 0;
    });
    machine.defineRI("mul", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i *= i1.i;
        return 0;
    });
    machine.defineRR("mul", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i *= r1.i;
        return 0;
    });
    machine.defineRI("div", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i /= i1.i;
        return 0;
    });
    machine.defineRR("div", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i /= r1.i;
        return 0;
    });
}