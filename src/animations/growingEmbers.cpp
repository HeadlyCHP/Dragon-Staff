#include "growingEmbers.h"
#include "colorPalettes.h"
#include <FastLED.h>

#define NUM_LEDS 36
#define HEAT_MAX 255

extern CRGB leds[];
extern const int ledMap[6][6];
extern const CRGBPalette16 emberPalette;

extern uint8_t heat[6][6];  // Heat array to track each LED's heat level

void growingEmbersEffect() {
    static unsigned long startTime = millis();
    unsigned long elapsedTime = millis() - startTime;
    const unsigned long duration = 15000;  // 15 seconds

    // Calculate cooling and sparking based on elapsed time (interpolated from initial to final values)
    int cooling = map(elapsedTime, 0, duration, 100, 10);
    int sparking = map(elapsedTime, 0, duration, 10, 100);

    // Limit cooling and sparking to final values once time has elapsed
    if (elapsedTime >= duration) {
        cooling = 10;
        sparking = 100;
    }

    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 50;  // Update interval for smooth animation

    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Step 1: Cool down every cell slightly based on current cooling level
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 6; col++) {
                heat[row][col] = qsub8(heat[row][col], random8(0, ((cooling * 10) / NUM_LEDS) + 2));
            }
        }

        // Step 2: Randomly ignite new sparks based on current sparking level
        for (int row = 0; row < 6; row++) {
            if (random8() < sparking) {
                int col = random8(6);
                heat[row][col] = qadd8(heat[row][col], random8(160, HEAT_MAX));
            }
        }

        // Step 3: Map heat to LED colors
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 6; col++) {
                int index = ledMap[row][col];
                uint8_t colorIndex = scale8(heat[row][col], 240);  // Scale heat to palette index
                leds[index] = ColorFromPalette(emberPalette, colorIndex);
            }
        }
        
        FastLED.show();
    }
}
