#include "Music.h"
#include <iterator>

Event polka[] = {
    Event::Note(0, 1, 3, C),
    Event::Note(1, 1, 3, E),
    Event::Note(2, 1, 3, G),
    Event::Note(3, 1, 3, E),
    Event::Bar(4),
    Event::Note(0, 1, 3, G),
    Event::Note(1, 1, 3, F),
    Event::Note(2, 2, 3, D),
    Event::Bar(4),
    Event::Note(0, 1, 3, G),
    Event::Note(1, 1, 3, F),
    Event::Note(2, 2, 3, D),
    Event::Bar(4),
    Event::Note(0, 1, 3, G),
    Event::Note(1, 1, 3, E),
    Event::Note(2, 1.8, 3, C),
    Event::Bar(4),
    Event::Note(0, 1, 3, C),
    Event::Note(1, 1, 3, E),
    Event::Note(2, 1, 3, G),
    Event::Note(3, 1, 3, E),
    Event::Bar(4),
    Event::Note(0, 1, 3, A),
    Event::Note(1, 1, 3, G),
    Event::Note(2, 2, 3, F),
    Event::Bar(4),
    Event::Note(0, 1, 3, G),
    Event::Note(1, 1, 3, F),
    Event::Note(2, 1, 3, E),
    Event::Note(3, 1, 3, D),
    Event::Bar(4),
    Event::Note(0, 1.8, 3, C),
    Event::Note(2, 1.8, 3, C),
};

Event* Polka::GetEvents()
{
    return polka;
}

int Polka::GetEventsCount()
{
    return std::size(polka);
}
