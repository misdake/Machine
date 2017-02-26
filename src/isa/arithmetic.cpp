#include "arithmetic.h"

#include <cmath>

#include "machine/Machine.h"

void defineArithmetic(Machine& machine) {
    machine.defineR("abs", [](Reg r0) -> jumpdiff {
        r0.i = abs(r0.i);
        return 0;
    });
    machine.defineRR("abs", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i = abs(r1.i);
        return 0;
    });
    machine.defineRI("set", "%s = %s", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i = i1.i;
        return 0;
    });
    machine.defineRR("set", "%s = %s", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i = r1.i;
        return 0;
    });
    machine.defineRI("add", "%s += %s", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i += i1.i;
        return 0;
    });
    machine.defineRR("add", "%s += %s", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i += r1.i;
        return 0;
    });
    machine.defineRI("mul", "%s *= %s", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i *= i1.i;
        return 0;
    });
    machine.defineRR("mul", "%s *= %s", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i *= r1.i;
        return 0;
    });
    machine.defineRI("div", "%s /= %s", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i /= i1.i;
        return 0;
    });
    machine.defineRR("div", "%s /= %s", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i /= r1.i;
        return 0;
    });
}