#include "jump.h"

#include "../machine/Machine.h"

void defineJump(Machine& machine) {
    machine.defineRRR("jl", [](Data& r0, Data& r1, Data& r2) -> jumpdiff {
        return r0.i < r1.i ? r2.i : 0;
    });
    machine.defineRRI("jl", [](Data& r0, Data& r1, const Data& i2) -> jumpdiff {
        return r0.i < r1.i ? i2.i : 0;
    });
    machine.defineRIR("jl", [](Data& r0, const Data& i1, Data& r2) -> jumpdiff {
        return r0.i < i1.i ? r2.i : 0;
    });
    machine.defineRII("jl", [](Data& r0, const Data& i1, const Data& i2) -> jumpdiff {
        return r0.i < i1.i ? i2.i : 0;
    });
}