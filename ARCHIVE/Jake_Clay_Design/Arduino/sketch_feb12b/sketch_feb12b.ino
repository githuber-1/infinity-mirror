#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

//#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 59

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  while (!Serial); // for Leonardo/Micro/Zero

  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop() {
  //Read the current time
  DateTime now = rtc.now();
  int tm = 35;
  int ts = (now.second());
  int th = 6;
  //Populate array for "hour mark" LEDs
  int h[12] = {0,5,10,15,20,25,30,35,40,45,50,55};
  //Populate array for "minute mark"LEDs
  int m[] = {1,2,3,4,6,7,8,9,11,12,13,14,16,17,18,19,21,22,23,24,26,27,28,29,31,32,33,34,36,37,38,39,41,42,43,44,46,47,48,49,51,52,53,54,56,57,58,59};
  //int ts=3;
  //int tm=7;
  //Illumniate all minutes
  for (int j=0; j<49; j++){
      strip.setPixelColor(m[j], strip.Color(0,0,255));
  }
  //Illuminate current minutes
  for (int k=0; k<=tm; k++){
    strip.setPixelColor(k, strip.Color(0,255,0));
  }
  //Illuminate all hours
  for (int i=0; i<11; i++){
    strip.setPixelColor(h[i], strip.Color(255,0,0));
  }
  //Illuminate current hour
  strip.setPixelColor(h[th], strip.Color(50,50,50));
  //Illuminate current second
  strip.setPixelColor(ts, strip.Color(25,0,50));
  strip.show();
  Serial.print("ts=");
  Serial.print(ts);
  Serial.println();
  Serial.print(now.second(), DEC);
    Serial.println();
  delay(1000);
  
}


