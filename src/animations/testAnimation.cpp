#include "testAnimation.h"
#include <FastLED.h>

extern CRGB leds[];  // Use the LED array declared in the main file
extern const int ledMap[6][6]; // Use the LED mapping from the main file

// Test function: lights each LED in order, left to right, top to bottom
void testMatrixDisplay() {
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 6; col++) {
            int index = ledMap[row][col];
            leds[index] = CRGB::Red;
            FastLED.show();
            delay(100);
            leds[index] = CRGB::Black;
        }
    }
}

// New function: moves a bar from the top row to the bottom
void movingBarTopToBottom() {
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 6; col++) {
            int index = ledMap[row][col];
            leds[index] = CRGB::Blue;
        }
        FastLED.show();
        delay(200);  // Delay to see the bar in each row
        // Turn off the row before moving to the next
        for (int col = 0; col < 6; col++) {
            int index = ledMap[row][col];
            leds[index] = CRGB::Black;
        }
    }
}
