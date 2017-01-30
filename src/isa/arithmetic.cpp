#include "arithmetic.h"

#include <cmath>

#include "../machine/Machine.h"

void defineArithmetic(Machine& machine) {
    machine.defineR("abs", [](Data& r0) -> jumpdiff {
        r0.i = abs(r0.i);
        return 0;
    });
    machine.defineRR("abs", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i = abs(r1.i);
        return 0;
    });
    machine.defineRI("set", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i = i1.i;
        return 0;
    });
    machine.defineRR("set", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i = r1.i;
        return 0;
    });
    machine.defineRI("add", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i += i1.i;
        return 0;
    });
    machine.defineRR("add", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i += r1.i;
        return 0;
    });
    machine.defineRI("mul", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i *= i1.i;
        return 0;
    });
    machine.defineRR("mul", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i *= r1.i;
        return 0;
    });
    machine.defineRI("div", [](Data& r0, const Data& i1) -> jumpdiff {
        r0.i /= i1.i;
        return 0;
    });
    machine.defineRR("div", [](Data& r0, Data& r1) -> jumpdiff {
        r0.i /= r1.i;
        return 0;
    });
}