#pragma once

#include <cstdint>
#include <functional>

typedef uint16_t Opcode;

struct Instruction {
    Opcode opcode;
    union {
        struct {
            int8_t oprand0;
            int8_t oprand1;
            int8_t oprand2;
            int8_t oprand3;
        } i8;
        struct {
            uint8_t oprand0;
            uint8_t oprand1;
            uint8_t oprand2;
            uint8_t oprand3;
        } u8;
        struct {
            int16_t oprand0;
            int16_t oprand1;
        } i16;
        struct {
            uint16_t oprand0;
            uint16_t oprand1;
        } u16;
        struct {
            int32_t oprand0;
        } i32;
        struct {
            uint32_t oprand0;
        } u32;
        struct {
            float oprand0; //TODO force 32bit
        } f32;
    } oprand;
};

enum class OprandType {
    i8, u8, i16, u16, i32, u32, f32
};

class Machine;
typedef std::function<void(Machine&, const Instruction&)> InstructionFunction;

struct InstructionDefinition {
    Opcode opcode;
    OprandType oprandType;
    InstructionFunction function;
};