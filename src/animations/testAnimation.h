#ifndef TEST_ANIMATION_H
#define TEST_ANIMATION_H

#include <FastLED.h>

extern const int ledMap[6][6];  // Declare ledMap here as an extern variable

void testMatrixDisplay();    // Function for original test
void movingBarTopToBottom(); // Function for top-to-bottom bar animation

#endif
