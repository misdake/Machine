#include "arithmetic.h"

#include <cmath>

#include "machine/Machine.h"

void defineArithmetic(MachinePrototype& machine) {
    machine.defineR("abs", [](Reg r0) { r0.i = abs(r0.i); });
    machine.defineRR("abs", [](Reg r0, Reg r1) { r0.i = abs(r1.i); });
    machine.defineRI("set", "%s = %s", [](Reg r0, Imm i1) { r0.i = i1.i; });
    machine.defineRR("set", "%s = %s", [](Reg r0, Reg r1) { r0.i = r1.i; });
    machine.defineRI("add", "%s += %s", [](Reg r0, Imm i1) { r0.i += i1.i; });
    machine.defineRR("add", "%s += %s", [](Reg r0, Reg r1) { r0.i += r1.i; });
    machine.defineRI("mul", "%s *= %s", [](Reg r0, Imm i1) { r0.i *= i1.i; });
    machine.defineRR("mul", "%s *= %s", [](Reg r0, Reg r1) { r0.i *= r1.i; });
    machine.defineRI("div", "%s /= %s", [](Reg r0, Imm i1) { r0.i /= i1.i; });
    machine.defineRR("div", "%s /= %s", [](Reg r0, Reg r1) { r0.i /= r1.i; });
}