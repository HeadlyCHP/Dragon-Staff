#include "fire.h"
#include "colorPalettes.h"
#include <FastLED.h>


#define NUM_LEDS 36
#define HEAT_MAX 255  // Maximum heat for the fire effect

extern CRGB leds[];
extern const int ledMap[6][6];
extern const CRGBPalette16 firePalette;
extern uint8_t heat[6][6];  // Use the shared heat array

void fireEffect() {
    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 50;  // Speed of the fire flicker

    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Step 1: Cool down every cell slightly
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 6; col++) {
                // Apply cooling, with slightly more cooling in alternate columns
                uint8_t cooling = (col % 2 == 0) ? random8(0, 80) : random8(0, 60);
                heat[row][col] = qsub8(heat[row][col], cooling);
            }
        }

        // Step 2: Randomly ignite new sparks, with more intensity in bottom rows
        for (int row = 4; row < 6; row++) {  // More sparking near the bottom
            if (random8() < 120) {
                int col = random8(6);
                heat[row][col] = qadd8(heat[row][col], random8(160, HEAT_MAX));
            }
        }

        // Step 3: Propagate heat upward and map to colors
        for (int row = 5; row > 0; row--) {
            for (int col = 0; col < 6; col++) {
                heat[row - 1][col] = (heat[row - 1][col] + heat[row][col]) / 2;
            }
        }

        // Step 4: Map heat to LED colors using the fire palette
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 6; col++) {
                int index = ledMap[row][col];
                uint8_t colorIndex = scale8(heat[row][col], 240);  // Scale heat to palette index
                leds[index] = ColorFromPalette(firePalette, colorIndex);
            }
        }

        FastLED.show();
    }
}
