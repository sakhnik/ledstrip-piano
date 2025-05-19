#pragma once

#include "Defs.h"

struct Polka
    : Piece
{
    Event* GetEvents() override;
    int GetEventsCount() override;
};

struct Menuet
    : Piece
{
    Event* GetEvents() override;
    int GetEventsCount() override;
};
