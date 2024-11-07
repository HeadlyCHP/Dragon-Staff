#include "risingBars.h"
#include "colorPalettes.h"
#include <FastLED.h>


#define NUM_LEDS 36

extern CRGB leds[];
extern const int ledMap[6][6];
extern const CRGBPalette16 barPalette;

void risingBarsEffect() {
    static uint8_t barHeight[6] = {0, 0, 0, 0, 0, 0};  // Tracks the height of the bar in each column
    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 120;  // Control the speed of the bar rise

    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Step 1: Update each column's bar height
        for (int col = 0; col < 6; col++) {
            // If the bar hasn't reached the top, increase its height
            if (barHeight[col] < 6) {
                barHeight[col]++;
            } else if (random8() < 30) {  // Reset the bar with some randomness
                barHeight[col] = 0;
            }
        }

        // Step 2: Apply the bar effect with shifting colors
        for (int col = 0; col < 6; col++) {
            for (int row = 0; row < 6; row++) {
                int index = ledMap[row][col];
                
                // Determine color based on row position within the bar height
                if (row <= barHeight[col]) {
                    uint8_t colorIndex = (row * 40 + millis() / 10) % 255;  // Shift color over time
                    leds[index] = ColorFromPalette(barPalette, colorIndex);
                } else {
                    leds[index].fadeToBlackBy(30);  // Fade out gradually above the bar height
                }
            }
        }

        FastLED.show();
    }
}
