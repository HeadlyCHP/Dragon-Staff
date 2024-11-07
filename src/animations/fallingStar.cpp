#include "fallingStar.h"
#include <FastLED.h>

#define NUM_LEDS 36
#define STAR_BRIGHTNESS 255  // Maximum brightness for the falling star
#define TRAIL_FADE_AMOUNT 50  // Amount of fading for the star's trail

extern CRGB leds[];
extern const int ledMap[6][6];

void fallingStarEffect() {
    static unsigned long lastStarTime = 0;
    static int currentRow = -1;  // -1 indicates no active star
    static int startCol = 0;
    const unsigned long starInterval = random(1000, 3000);  // Interval between new stars

    // Clear LEDs to keep the background black
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].fadeToBlackBy(TRAIL_FADE_AMOUNT);  // Gradual fading effect
    }

    // Check if it's time for a new falling star
    if (currentRow == -1 && millis() - lastStarTime > starInterval) {
        lastStarTime = millis();
        currentRow = 0;  // Start a new star at the top row
        startCol = random(0, 6);  // Random column
    }

    // If there's an active falling star, animate it
    if (currentRow >= 0) {
        // Set the current position of the star to bright gold
        int index = ledMap[currentRow][startCol];
        leds[index] = CRGB::Gold;
        leds[index].fadeLightBy(100 - currentRow * 15);  // Gradual fade as it falls

        // Move the star down to the next row
        currentRow++;

        // If the star reaches the bottom, reset it
        if (currentRow >= 6) {
            currentRow = -1;  // Reset to indicate no active star
        }
    }

    FastLED.show();
    delay(50);  // Control the speed of the star's descent
}
