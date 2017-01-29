#pragma once

#include <map>
#include <cassert>
#include "../program/Program.h"
#include "../instruction/Instruction.h"

class Machine {
private:
    std::map<uint16_t, InstructionDefinition> defs;

public:
    Data registers[32];

    void defineInstruction(uint16_t opcode, const char* name, std::function<void(Machine&, const Instruction&)>&& function) {
        //TODO check correctness
        defs.emplace(std::make_pair(opcode, InstructionDefinition{opcode, name, std::move(function)}));
    }

    void run(const Program& program) {
        for (auto i = program.instructions.begin(); i != program.instructions.end(); i++) {
            run(*i);
        }
    }

    void run(const Instruction& instruction) {
        auto iterator = defs.find(instruction.opcode);
        if (iterator != defs.end()) {
            InstructionDefinition& def = iterator->second;
            assert(def.opcode == instruction.opcode);
            def.function(*this, instruction);
        }
    }
};


