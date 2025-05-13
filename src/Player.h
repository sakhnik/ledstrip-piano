#pragma once

#include <arduino-timer.h>

struct Piece;
struct Event;
struct Mapping;

class Player
{
public:
    Player(Piece &piece, Mapping &mapping);
    void Setup();
    void Tick();

private:
    Piece &piece;
    Mapping &mapping;
    float mspb = 1000.f;
    Event *events;
    int events_count;

    Timer<> timer = timer_create_default();

    unsigned long base_millis;
    float base = 0.f;
    int cur_idx = 0;

    void Reset();
    void NextEvent();
    void ProcessNow();
    void NoteOn(const Event &);
    void NoteOff();
};
