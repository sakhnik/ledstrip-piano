#include "Mapping.h"
#include "Player.h"
#include "Music.h"
Mapping mapping;
Polka p;
Player player(p, mapping);

void setup()
{
    player.Setup();
}

void loop()
{
    player.Tick();
}
