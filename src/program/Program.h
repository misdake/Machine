#pragma once

#include <vector>

#include "instruction/Instruction.h"

struct Program {
public:
    std::vector<Instruction> instructions;
};
