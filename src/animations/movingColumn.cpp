#include "movingColumn.h"
#include "colorPalettes.h"
#include <FastLED.h>

#define NUM_LEDS 36

extern CRGB leds[];
extern const int ledMap[6][6];
extern const CRGBPalette16 columnPalette;

void movingColumnEffect() {
    static int currentCol = 0;  // Tracks the current column
    static unsigned long lastUpdate = 0;
    const unsigned long updateInterval = 0;  // Speed of the column movement

    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Step 1: Clear the entire LED matrix for the fading effect
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i].fadeToBlackBy(40);  // Fade trail intensity
        }

        // Step 2: Draw the moving column in the current position
        for (int row = 0; row < 6; row++) {
            int index = ledMap[row][currentCol];
            uint8_t colorIndex = (row * 20 + millis() / 10) % 255;  // Shift color with time for dynamic effect
            leds[index] = ColorFromPalette(columnPalette, colorIndex);
        }

        // Step 3: Move to the next column
        currentCol = (currentCol + 1) % 6;  // Wrap around to the left after reaching the right side

        FastLED.show();
    }
}
