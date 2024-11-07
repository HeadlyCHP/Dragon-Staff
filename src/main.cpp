#include <Arduino.h>
#include <FastLED.h>
#include "animations/testAnimation.h"
#include "animations/burningEmbers.h"
#include "animations/growingEmbers.h"
#include "animations/waterfall.h"
#include "animations/lightning.h"
#include "animations/fallingStar.h"
#include "animations/geyser.h"
#include "animations/fire.h"
#include "animations/plantGrowth.h"
#include "animations/risingBars.h"
#include "animations/movingColumn.h"
#include "colorPalettes.h"


#define LED_PIN 6
#define NUM_LEDS 36
#define SWITCH_PIN 5

CRGB leds[NUM_LEDS];
const int ledMap[6][6] = {
    {5, 6, 17, 18, 29, 30},
    {4, 7, 16, 19, 28, 31},
    {3, 8, 15, 20, 27, 32},
    {2, 9, 14, 21, 26, 33},
    {1, 10, 13, 22, 25, 24},
    {0, 11, 12, 23, 24, 35}
};

uint8_t heat[6][6] = {0};

int currentAnimation = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int lastSwitchState = HIGH;

void setup() {
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    Serial.begin(9600);  // Initialize Serial for UART communication
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
}

// Function to cycle animations via button press
void cycleAnimation() {
    int switchState = digitalRead(SWITCH_PIN);

    if (switchState != lastSwitchState && (millis() - lastDebounceTime) > debounceDelay) {
        lastDebounceTime = millis();  // Reset debounce timer

        if (switchState == LOW) {  // Check for button press
            currentAnimation = (currentAnimation + 1) % 11;  // Cycle through all animations
        }
    }

    lastSwitchState = switchState;
}

// Function to update animation based on serial input
void updateAnimationBySerial() {
    if (Serial.available() > 0) {
        int command = Serial.read();  // Read the incoming byte

        switch (command) {
            case 0x01:
                currentAnimation = 0;  // fireEffect
                break;
            case 0x02:
                currentAnimation = 1;  // growingEmbersEffect
                break;
            case 0x03:
                currentAnimation = 2;  // waterfallEffect
                break;
            case 0x04:
                currentAnimation = 3;  // lightningEffect
                break;
            case 0x05:
                currentAnimation = 4;  // fallingStarEffect
                break;
            case 0x06:
                currentAnimation = 5;  // geyserEffect
                break;
            case 0x07:
                currentAnimation = 6;  // fireEffect
                break;
            case 0x08:
                currentAnimation = 7;  // plantGrowthEffect
                break;
            case 0x09:
                currentAnimation = 8;  // risingBarsEffect
                break;
            case 0x0A:
                currentAnimation = 9;  // movingColumnEffect
                break;
            case 0x0B:
                currentAnimation = 10;  // testMatrixDisplay
                break;
            default:
                // Do nothing for unrecognized commands
                break;
        }
    }
}

void loop() {
    // Update animation selection based on button press or serial input
    cycleAnimation();        // Check for button press to cycle animations
    updateAnimationBySerial();  // Check for serial input to set specific animations

    // Display the selected animation based on currentAnimation
    switch (currentAnimation) {
        case 0:
            burningEmbers();
            break;
        case 1:
            growingEmbersEffect();
            break;
        case 2:
            waterfallEffect();
            break;
        case 3:
            lightningEffect();
            break;
        case 4:
            fallingStarEffect();
            break;
        case 5:
            geyserEffect();
            break;
        case 6:
            fireEffect();
            break;
        case 7:
            plantGrowthEffect();
            break;
        case 8:
            risingBarsEffect();
            break;
        case 9:
            movingColumnEffect();
            break;
        case 10:
            testMatrixDisplay();
            break;
    }
}
