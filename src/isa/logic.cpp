#include "logic.h"

#include "../machine/Machine.h"

void defineLogic(Machine& machine) {
    machine.defineR("bool1", [](Data& r0) -> jumpdiff {
        r0.i = r0.i ? 1 : 0;
        return 0;
    });
    machine.defineR("notl1", [](Data& r0) -> jumpdiff {
        r0.i = r0.i ? 0 : 1;
        return 0;
    });
    machine.defineR("notb1", [](Data& r0) -> jumpdiff {
        r0.i = ~r0.i;
        return 0;
    });

    machine.defineRR("andb2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i &= r1.i;
        return 0;
    });
    machine.defineRI("andb2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i &= i1.i;
        return 0;
    });
    machine.defineRI("orb2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i |= i1.i;
        return 0;
    });
    machine.defineRR("orb2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i |= r1.i;
        return 0;
    });
    machine.defineRI("xorb2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i ^= i1.i;
        return 0;
    });
    machine.defineRR("xorb2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i ^= r1.i;
        return 0;
    });

    machine.defineRR("andl2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i = r0.i && r1.i;
        return 0;
    });
    machine.defineRI("andl2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i = r0.i && i1.i;
        return 0;
    });
    machine.defineRI("orl2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i = r0.i || i1.i;
        return 0;
    });
    machine.defineRR("orl2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i = r0.i || r1.i;
        return 0;
    });
}