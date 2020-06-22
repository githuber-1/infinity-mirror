//confirmed Infinity Mirror_a_Built-6-2-2020 can control LEDs with this code on 6/20/2020. Unfortunately, data_out is unwired
#include "FastLED.h"
#include <Wire.h>

#define NUM_LEDS 60
#define DATA_PIN 6
//#define CLOCK_PIN 13;
CRGB leds[NUM_LEDS];
;

void setup() {
  delay(3000); // 3 second delay for recovery
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  
  for(int i = 0; i <= NUM_LEDS; i++){
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  delay(500);
  
  // Now turn the LED off, then pause
  for (int i = 0; i <= NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();
  delay(500);
  Serial.println("...test");
}
