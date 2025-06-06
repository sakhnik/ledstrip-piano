#pragma once

#include "Defs.h"
#include <cstdint>
#include <limits>

class Mapping
{
public:
    static constexpr int8_t OCTAVE_COUNT = 6;
    static constexpr int8_t BASE_OCTAVE = 3;
    static constexpr uint16_t NO_POS = std::numeric_limits<uint16_t>::max();

    uint16_t GetPosition(int8_t octave, Pitch p);

    struct RGBW
    {
        uint8_t r, g, b, w;
    };

    RGBW GetColor(Pitch p);
};
