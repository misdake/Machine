#include "logic.h"

#include "machine/Machine.h"

void defineLogic(MachinePrototype& machine) {
    machine.defineR("bool", [](Reg r0) { r0.i = r0.i ? 1 : 0; });
    machine.defineR("notl", [](Reg r0) { r0.i = r0.i ? 0 : 1; });
    machine.defineR("notb", [](Reg r0) { r0.i = ~r0.i; });

    machine.defineRR("andb", [](Reg r0, Reg r1) { r0.i &= r1.i; });
    machine.defineRI("andb", [](Reg r0, Imm i1) { r0.i &= i1.i; });
    machine.defineRR("orb", [](Reg r0, Reg r1) { r0.i |= r1.i; });
    machine.defineRI("orb", [](Reg r0, Imm i1) { r0.i |= i1.i; });
    machine.defineRR("xorb", [](Reg r0, Reg r1) { r0.i ^= r1.i; });
    machine.defineRI("xorb", [](Reg r0, Imm i1) { r0.i ^= i1.i; });

    machine.defineRR("andl", [](Reg r0, Reg r1) { r0.i = r0.i && r1.i; });
    machine.defineRI("andl", [](Reg r0, Imm i1) { r0.i = r0.i && i1.i; });
    machine.defineRR("orl", [](Reg r0, Reg r1) { r0.i = r0.i || r1.i; });
    machine.defineRI("orl", [](Reg r0, Imm i1) { r0.i = r0.i || i1.i; });
}