#include "Mapping.h"

constexpr int OCTAVE_POS[Mapping::OCTAVE_COUNT] = {
    0, 21 - 1, 45 - 1, 69 - 1, 71 + 20, 71 + 45
};

constexpr int NOTE_OFFSETS[Mapping::OCTAVE_COUNT][12] = {
    { -20, -20, 0, 2, 4, 7, 9, 11, 12, 14, 16, 17 },
    { 1, 2, 4, 6, 8, 11, 13, 15, 16, 18, 20, 21 },
    { 1, 2, 4, 6, 8, 11, 13, 14, 16, 18, 19, 21 },
    { 0, 2, /**/4, 5, 7, 10, 12, 14, 15, 17, 19, 21 },
    { 1, 3, 4, 6, 8, 11, 13, 15, 16, 18, 20, 21 },
    { 0, 2, 3, 5, 7, 10, 12, 13, 15, 17, 18, 20 },
};

uint16_t Mapping::GetPosition(int8_t octave, Pitch p)
{
    if (octave < 0 || octave >= OCTAVE_COUNT) {
        return NO_POS;
    }
    auto pos = OCTAVE_POS[octave] + NOTE_OFFSETS[octave][static_cast<int>(p)];
    return pos < 0 ? NO_POS : pos;
}

Mapping::RGBW Mapping::GetColor(Pitch p)
{
    switch (p) {
    case Pitch::C:
    case Pitch::D:
    case Pitch::E:
    case Pitch::F:
    case Pitch::G:
    case Pitch::A:
    case Pitch::B:
        return RGBW{0, 0, 255, 0};
    case Pitch::Cs:
    case Pitch::Ds:
    case Pitch::Fs:
    case Pitch::Gs:
    case Pitch::As:
        return RGBW{255, 0, 0, 0};
    }
    return RGBW{0, 0, 0, 0};
}
