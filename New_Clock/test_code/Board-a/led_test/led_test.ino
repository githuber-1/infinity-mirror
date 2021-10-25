//confirmed Infinity Mirror_a_Built-6-2-2020 can control LEDs with this code on 6/20/2020. Unfortunately, data_out is unwired
#include "FastLED.h"
#include <Wire.h>
#include "stdlib.h"

#include <WiFi.h>
#include "time.h"

const char* ssid     = "Hooligan";
const char* password = "Bigchocolatetaco";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -25200;
const int   daylightOffset_sec = 3600;

#define NUM_LEDS 60
#define DATA_PIN 5
//#define CLOCK_PIN 13;
CRGB leds[NUM_LEDS];

void clock_leds(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  
  // Now turn the LED off, then pause
  for (int i = 0; i <= NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  
  char timeHour[3];
  strftime(timeHour, 3, "%I", &timeinfo);
  char timeMinute[3];
  strftime(timeMinute, 3, "%M", &timeinfo);
  char timeSecond[3];
  strftime(timeSecond, 3, "%S", &timeinfo);

  int hour_int = atoi(timeHour);
  int minute_int = atoi(timeMinute);
  int second_int = atoi(timeSecond);

  Serial.println(hour_int);
  Serial.println(minute_int);
  Serial.println(second_int);

  int hour_led = ((hour_int * 5) + 30) % 60;
  int minute_led = (minute_int + 30) % 60;
  int second_led = (second_int + 30) % 60;

  Serial.println(hour_led);
  Serial.println(minute_led);
  Serial.println(second_led);
  
  leds[hour_led + 1] = CRGB::White;
  leds[hour_led] = CRGB::White;
  leds[hour_led - 1] = CRGB::White;
  leds[minute_led] = CRGB::Red;
  leds[second_led] = CRGB::Blue;
  
  FastLED.show();
  delay(100);
  Serial.println("...test");
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}

void setup() {
  delay(3000); // 3 second delay for recovery
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop() {
  //printLocalTime();
  clock_leds();
  
}
