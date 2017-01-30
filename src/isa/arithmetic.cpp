#include "arithmetic.h"

#include <cmath>

#include "../machine/Machine.h"

void defineArithmetic(Machine& machine) {
    machine.defineR("abs1", [](Data& r0) -> jumpdiff {
        r0.i = abs(r0.i);
        return 0;
    });
    machine.defineRR("abs2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i = abs(r1.i);
        return 0;
    });
    machine.defineRI("set2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i = i1.i;
        return 0;
    });
    machine.defineRR("set2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i = r1.i;
        return 0;
    });
    machine.defineRI("add2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i += i1.i;
        return 0;
    });
    machine.defineRR("add2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i += r1.i;
        return 0;
    });
    machine.defineRI("mul2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i *= i1.i;
        return 0;
    });
    machine.defineRR("mul2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i *= r1.i;
        return 0;
    });
    machine.defineRI("div2i", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i /= i1.i;
        return 0;
    });
    machine.defineRR("div2r", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i /= r1.i;
        return 0;
    });
}