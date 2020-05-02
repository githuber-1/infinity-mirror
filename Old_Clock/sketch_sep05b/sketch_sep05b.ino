#include "FastLED.h"
#include <Wire.h>

//Define FastLED parameters:
#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER RGB
#define NUM_LEDS    60
int BRIGHTNESS = 55;
int SAT = 255;
#define FRAMES_PER_SECOND  120
CRGB leds[NUM_LEDS];

void setup() {
  delay(3000);
  Serial.begin(9600);
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  fill_solid(leds, NUM_LEDS, CHSV(100, 100, 100));
  FastLED.show();
}

