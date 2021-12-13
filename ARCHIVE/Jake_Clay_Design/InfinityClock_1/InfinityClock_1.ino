#include <Wire.h>
#include "RTClib.h"
#include "LPD8806.h"
#include "SPI.h"

RTC_DS3231 rtc;

int nLEDS = 32;
int dataPin = 2;
int clockPin = 3;
uint16_t i;

LPD8806 strip = LPD8806(nLEDS, dataPin, clockPin);

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600);
  delay(3000);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}
void loop() {
  DateTime now = rtc.now();
  
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print('\n');

  for (i = 0; i < nLEDS; i++){
    if (i != now.hour()-2 && i != now.hour()-1 && i != now.hour())
    {
      strip.setPixelColor(i, 250, 0, 0);
      strip.show();
    }
  }
  strip.setPixelColor(now.hour()-2, 200, 200, 200);
  strip.setPixelColor(now.hour()-1, 200, 200, 200);
  strip.setPixelColor(now.hour(), 200, 200, 200);
  strip.setPixelColor(now.minute()-1, 200, 200, 200);
  strip.setPixelColor(now.second()-1, 200, 200, 200);
  strip.show();
  delay(1000);
}


