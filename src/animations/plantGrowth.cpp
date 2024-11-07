#include "plantGrowth.h"
#include "colorPalettes.h"
#include <FastLED.h>


#define NUM_LEDS 36

extern CRGB leds[];
extern const int ledMap[6][6];
extern const CRGBPalette16 plantPalette;

void plantGrowthEffect() {
    static int currentRow[6] = {-1, -1, -1, -1, -1, -1};  // Tracks growth level for each column
    static uint8_t colorShift[6] = {0};  // Tracks color shift offset for each column
    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 300;  // Speed of growth
    
    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Step 1: Update each column to grow upward
        for (int col = 0; col < 6; col++) {
            if (currentRow[col] < 5) {
                currentRow[col]++;
            }
        }

        // Step 2: Shift color in each cell to create a dynamic vine effect
        for (int col = 0; col < 6; col++) {
            colorShift[col] += random8(1, 5);  // Increment color shift by a small random value for variation

            for (int row = 0; row <= currentRow[col]; row++) {
                int index = ledMap[row][col];
                uint8_t colorIndex = (row * 40 + colorShift[col]) % 255;  // Calculate color with shifting effect
                leds[index] = ColorFromPalette(plantPalette, colorIndex);
            }
        }

        FastLED.show();
    }
}
