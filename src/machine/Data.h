#pragma once

#include <cstdint>

union Data {
    int32_t i;
    float f;

    explicit Data(int32_t i) {
        this->i = i;
    }

    explicit Data(float f) {
        this->f = f;
    }

    Data() {
        i = -1;
    }
};
