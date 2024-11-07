#include "waterfall.h"
#include "colorPalettes.h"
#include <FastLED.h>

#define NUM_LEDS 36

extern CRGB leds[];
extern const int ledMap[6][6];

void waterfallEffect() {
    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 100;  // Control the speed of the waterfall effect

    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Step 1: Shift each row’s color down by copying from the row above
        for (int row = 5; row > 0; row--) {
            for (int col = 0; col < 6; col++) {
                int indexCurrent = ledMap[row][col];
                int indexAbove = ledMap[row - 1][col];

                // Copy color from the row above, but dim it slightly for a trailing effect
                leds[indexCurrent] = leds[indexAbove];
                leds[indexCurrent].fadeToBlackBy(100);  // Adjust fading for smoothness
            }
        }

        // Step 2: Set a solid color for the top row
        CRGB solidColor = ColorFromPalette(rainPalette, random8(100, 200)); // Pick a random blueish color
        for (int col = 0; col < 6; col++) {
            int index = ledMap[0][col];
            leds[index] = solidColor;
        }

        FastLED.show();
    }
}
