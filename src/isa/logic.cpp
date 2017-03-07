#include "logic.h"

#include "machine/Machine.h"

void defineLogic(MachinePrototype& machine) {
    machine.defineR("bool", [](Reg r0) -> jumpdiff {
        r0.i = r0.i ? 1 : 0;
        return 0;
    });
    machine.defineR("notl", [](Reg r0) -> jumpdiff {
        r0.i = r0.i ? 0 : 1;
        return 0;
    });
    machine.defineR("notb", [](Reg r0) -> jumpdiff {
        r0.i = ~r0.i;
        return 0;
    });

    machine.defineRR("andb", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i &= r1.i;
        return 0;
    });
    machine.defineRI("andb", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i &= i1.i;
        return 0;
    });
    machine.defineRR("orb", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i |= r1.i;
        return 0;
    });
    machine.defineRI("orb", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i |= i1.i;
        return 0;
    });
    machine.defineRR("xorb", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i ^= r1.i;
        return 0;
    });
    machine.defineRI("xorb", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i ^= i1.i;
        return 0;
    });

    machine.defineRR("andl", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i = r0.i && r1.i;
        return 0;
    });
    machine.defineRI("andl", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i = r0.i && i1.i;
        return 0;
    });
    machine.defineRR("orl", [](Reg r0, Reg r1) -> jumpdiff {
        r0.i = r0.i || r1.i;
        return 0;
    });
    machine.defineRI("orl", [](Reg r0, Imm i1) -> jumpdiff {
        r0.i = r0.i || i1.i;
        return 0;
    });
}