#pragma once

#include <cstdint>

enum Pitch { C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B };

enum EventType { Bar, Note };

struct Event
{
    EventType type;
    float offset;
    float duration;
    int8_t octave;
    Pitch pitch;

    static Event Note(float offset, float duration, int8_t octave, Pitch pitch)
    {
        return {EventType::Note, offset, duration, octave, pitch};
    }

    static Event Bar(float duration)
    {
        return {EventType::Bar, 0.f, duration};
    }
};

struct Piece
{
    virtual ~Piece() {}
    virtual Event* GetEvents() = 0;
    virtual int GetEventsCount() = 0;
};
