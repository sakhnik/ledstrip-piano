#include "Mapping.h"
#include <Adafruit_NeoPixel.h>

#define PIN        2      // GPIO to which the strip is connected
#define NUM_LEDS   144     // Number of LEDs in the strip

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Mapping mapping;

void setup()
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
    static int8_t octave = 0;
    static int8_t pitch = 0;
    strip.clear();

    // Set a color (e.g. red, green, blue cycling)
    auto rgba = mapping.GetColor(static_cast<Pitch>(pitch));
    uint32_t color = strip.Color(rgba.r, rgba.g, rgba.b, rgba.w);
    auto pos = mapping.GetPosition(octave, static_cast<Pitch>(pitch));
    if (pos != Mapping::NO_POS) {
        strip.setPixelColor(pos, color);
    }
    strip.show();

    if (12 == ++pitch) {
        pitch = 0;
        if (++octave == Mapping::OCTAVE_COUNT) {
            octave = 0;
        }
    }
    delay(1000);
}
