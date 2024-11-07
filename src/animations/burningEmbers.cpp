#include "burningEmbers.h"
#include <FastLED.h>
#include "colorPalettes.h"

#define NUM_LEDS 36
#define COOLING 100
#define SPARKING 10
#define HEAT_MAX 170

extern CRGB leds[];
extern const int ledMap[6][6];
extern uint8_t heat[6][6];  // Declare heat as an external variable

void burningEmbers() {
    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 50;

    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Step 1: Cool down each cell
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 6; col++) {
                heat[row][col] = qsub8(heat[row][col], random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
            }
        }

        // Step 2: Ignite new sparks
        for (int row = 0; row < 6; row++) {
            if (random8() < SPARKING) {
                int col = random8(6);
                heat[row][col] = qadd8(heat[row][col], random8(160, HEAT_MAX));
            }
        }

        // Step 3: Map heat to LED colors
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 6; col++) {
                int index = ledMap[row][col];
                uint8_t colorIndex = scale8(heat[row][col], 240);
                leds[index] = ColorFromPalette(emberPalette, colorIndex);
            }
        }
        
        FastLED.show();
    }
}
