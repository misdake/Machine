#include "logic.h"

#include "../machine/Machine.h"

void defineLogic(Machine& machine) {
    machine.defineR("bool", [](Data& r0) -> jumpdiff {
        r0.i = r0.i ? 1 : 0;
        return 0;
    });
    machine.defineR("notl", [](Data& r0) -> jumpdiff {
        r0.i = r0.i ? 0 : 1;
        return 0;
    });
    machine.defineR("notb", [](Data& r0) -> jumpdiff {
        r0.i = ~r0.i;
        return 0;
    });

    machine.defineRR("andb", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i &= r1.i;
        return 0;
    });
    machine.defineRI("andb", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i &= i1.i;
        return 0;
    });
    machine.defineRR("orb", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i |= r1.i;
        return 0;
    });
    machine.defineRI("orb", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i |= i1.i;
        return 0;
    });
    machine.defineRR("xorb", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i ^= r1.i;
        return 0;
    });
    machine.defineRI("xorb", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i ^= i1.i;
        return 0;
    });

    machine.defineRR("andl", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i = r0.i && r1.i;
        return 0;
    });
    machine.defineRI("andl", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i = r0.i && i1.i;
        return 0;
    });
    machine.defineRR("orl", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i = r0.i || r1.i;
        return 0;
    });
    machine.defineRI("orl", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i = r0.i || i1.i;
        return 0;
    });
}