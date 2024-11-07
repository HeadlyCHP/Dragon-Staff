#include "colorPalettes.h"

// Define the Incandescent gradient for embers
DEFINE_GRADIENT_PALETTE( Incandescent_gp ) {
    0,   0,  0,  0,
  117,  18,  0,  0,
  151, 112,  0,  0,
  172, 175, 14,  1,
  206, 255, 67,  4,
  217, 244,131,  1,
  229, 237,221,  1,
  241, 239,229, 35,
  255, 239,237,160
};
const CRGBPalette16 emberPalette = Incandescent_gp;

// Define the rain gradient for the waterfall effect
DEFINE_GRADIENT_PALETTE( rain_gp ) {
    0,   0,  0,  0,
   11,   1,  1,  2,
   23,   1,  1, 16,
   42,   1,  3, 27,
   62,   5,  8, 40,
   93,   8, 32, 47,
  125,  12, 75, 54,
  190,  84,151,132,
  255, 255,255,255
};
const CRGBPalette16 rainPalette = rain_gp;

// Fire gradient from red at the bottom to yellow at the top
DEFINE_GRADIENT_PALETTE( fire_gp ) {
    0, 255, 0, 0,      // Red
   64, 255, 85, 0,     // Orange-red
  128, 255, 170, 0,    // Orange
  192, 255, 255, 0,    // Yellow-orange
  255, 255, 255, 0     // Yellow
};
const CRGBPalette16 firePalette = fire_gp;

// Define the plant growth gradient from dark green to light green
DEFINE_GRADIENT_PALETTE( GPS_Nature_Grass_gp ) {
    0, 109,203, 42,
   10,  83,139, 26,
   21,  60, 90, 14,
   31,  39, 91,  3,
   42,  22, 92,  1,
   53,  21, 75,  5,
   68,  20, 59, 21,
   83,  14, 49, 13,
  105,   9, 40,  7,
  133,   5, 27,  3,
  172,   3, 17,  1,
  205,   4, 14,  1,
  255,   5, 11,  1};

const CRGBPalette16 plantPalette = GPS_Nature_Grass_gp;

// Define the purple-to-dark gradient palette
DEFINE_GRADIENT_PALETTE( bhw1_oldladyinpurple_gp ) {
    0, 157, 57,197,
   81,  42,  0, 45,
  158,   8,  1, 10,
  255,   0,  0,  0
};
const CRGBPalette16 barPalette = bhw1_oldladyinpurple_gp;

// Define the alarm palette with warm and vibrant colors
DEFINE_GRADIENT_PALETTE( alarm_p4_0_7_gp ) {
    0, 227,255,223,
   12, 201,255,153,
   25, 208,255,105,
   38, 237,255, 73,
   51, 255,227, 50,
   63, 255,182, 33,
   76, 255,135, 21,
   89, 255, 91, 11,
  102, 255, 53,  6,
  114, 255, 23,  2,
  127, 255,  6,  1,
  140, 255,  1,  1,
  153, 255,  1, 37,
  165, 255,  1,149,
  178, 169,  1,255,
  191,  48,  1,255,
  204,   4,  1,255,
  216,   1,  7,255,
  229,   1, 56,255,
  242,   1,162,255,
  255,   1,255,186
};
const CRGBPalette16 columnPalette = alarm_p4_0_7_gp;