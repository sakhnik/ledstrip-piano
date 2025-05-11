#include <Adafruit_NeoPixel.h>

#define PIN        2      // GPIO to which the strip is connected
#define NUM_LEDS   144     // Number of LEDs in the strip

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

void setup()
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
    static uint8_t pos = 0;
    strip.clear();

    // Set a color (e.g. red, green, blue cycling)
    uint32_t color = strip.Color(0, 255, 0);  // Red
    strip.setPixelColor(pos, color);
    strip.show();

    pos = (pos + 1) % NUM_LEDS;
    delay(50); // Adjust speed
}
