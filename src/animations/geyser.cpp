#include "geyser.h"
#include "colorPalettes.h"
#include <FastLED.h>

#define NUM_LEDS 36

extern CRGB leds[];
extern const int ledMap[6][6];

// Use the rain palette for more color variance
extern const CRGBPalette16 rainPalette;

void geyserEffect() {
    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 200;  // Speed of the swirling effect

    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Step 1: Move colors in the center columns (2 and 3) upward
        for (int col = 2; col <= 3; col++) {
            for (int row = 0; row < 5; row++) {
                int indexCurrent = ledMap[row][col];
                int indexAbove = ledMap[row + 1][col];
                leds[indexCurrent] = leds[indexAbove];  // Shift color upward
            }
            // Add a new random color from the rain palette at the bottom of each center column
            leds[ledMap[5][col]] = ColorFromPalette(rainPalette, random8(0, 80));
        }

        // Step 2: Move colors in the outer columns (0, 1 on left and 4, 5 on right) downward
        for (int col = 0; col <= 1; col++) {  // Left side
            for (int row = 5; row > 0; row--) {
                int indexCurrent = ledMap[row][col];
                int indexBelow = ledMap[row - 1][col];
                leds[indexCurrent] = leds[indexBelow];  // Shift color downward
            }
            leds[ledMap[0][col]] = ColorFromPalette(rainPalette, random8(50, 160));  // New color at the top
        }
        for (int col = 4; col <= 5; col++) {  // Right side
            for (int row = 5; row > 0; row--) {
                int indexCurrent = ledMap[row][col];
                int indexBelow = ledMap[row - 1][col];
                leds[indexCurrent] = leds[indexBelow];  // Shift color downward
            }
            leds[ledMap[0][col]] = ColorFromPalette(rainPalette, random8(50, 160));  // New color at the top
        }

        FastLED.show();
    }
}
