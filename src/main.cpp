#include "Mapping.h"
#include "Player.h"
#include "Music.h"

Mapping mapping;
Polka p;
Menuet m;
Player player(m, mapping);

void setup()
{
    player.Setup();
}

void loop()
{
    player.Tick();
}
