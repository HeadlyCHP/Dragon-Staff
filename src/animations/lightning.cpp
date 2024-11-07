#include "lightning.h"
#include <FastLED.h>

#define NUM_LEDS 36
#define BOLT_BRIGHTNESS 255  // Maximum brightness for bolts

extern CRGB leds[];
extern const int ledMap[6][6];

void lightningEffect() {
    static unsigned long lastBoltTime = 0;
    static unsigned long lastFlashTime = 0;
    const unsigned long boltInterval = random(500, 2000); // Interval between bolts
    const unsigned long flashInterval = random(3000, 8000); // Interval between flashes

    // Check if it's time for a new lightning bolt
    if (millis() - lastBoltTime > boltInterval) {
        lastBoltTime = millis();

        // Determine the starting position (top or bottom row)
        int row = (random(0, 2) == 0) ? 0 : 5;  // Choose either row 0 (top) or row 5 (bottom)
        int col = random(0, 6);  // Random column to start

        // Arcing bolt pattern
        for (int i = 0; i < 6; i++) {
            int index = ledMap[row][col];
            leds[index] = CRGB(BOLT_BRIGHTNESS, BOLT_BRIGHTNESS, BOLT_BRIGHTNESS);  // Bright white for bolt
            FastLED.show();
            delay(30);  // Short delay for each step of the bolt

            // Randomly change direction for jagged effect
            if (random(0, 2) == 0) {
                col = constrain(col + random(-1, 2), 0, 5);  // Move left or right randomly
            }
            row = (row == 0) ? row + 1 : row - 1;  // Move down if starting from top, up if from bottom
        }

        // Fade the bolt
        for (int fade = 200; fade > 0; fade -= 50) {
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].fadeToBlackBy(50);
            }
            FastLED.show();
            delay(30);  // Fade duration
        }
    }

    // Check if it's time for a random flash
    if (millis() - lastFlashTime > flashInterval) {
        lastFlashTime = millis();

        // Random flash across the entire matrix
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB(BOLT_BRIGHTNESS, BOLT_BRIGHTNESS, BOLT_BRIGHTNESS);  // Bright white flash
        }
        FastLED.show();
        delay(100);  // Flash duration

        // Fade the flash quickly
        for (int fade = 200; fade > 0; fade -= 50) {
            for (int i = 0; i < NUM_LEDS; i++) {
                leds[i].fadeToBlackBy(50);
            }
            FastLED.show();
            delay(30);  // Fade duration
        }
    }
}
