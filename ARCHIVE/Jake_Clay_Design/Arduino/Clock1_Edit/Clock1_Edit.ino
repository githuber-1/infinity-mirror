#include <Adafruit_NeoPixel.h>
// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

#if defined(ARDUINO_ARCH_SAMD)  // for Zero, output on USB Serial console
   #define Serial SerialUSB
#endif

RTC_DS1307 rtc;

//Define pin locations
  const int potPin = 0;
  const int dlsPin = 7;       //Switch for daylight savings adjustments
//Define parameters:
#define BUTTON_PIN   5    // Digital IO pin connected to the button.  This will be
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

//Variables needed for button cycling
bool oldState = HIGH;
int showType = 0;

//Create color library for ease of programming.  See http://www.rapidtables.com/web/color/RGB_Color.htm for other colors
uint32_t red = strip.Color(255,0,0);
uint32_t gold = strip.Color(255,128,0);
uint32_t orange = strip.Color(204,102,0);
uint32_t yellow = strip.Color(255,255,0);
uint32_t peagreen = strip.Color(255,128,0);
uint32_t green = strip.Color(0,255,0);
uint32_t seafoam = strip.Color(0,255,128);
uint32_t teal = strip.Color(0,255,255);
uint32_t turquoise = strip.Color(0,128,255);
uint32_t blue = strip.Color(0,0,255);
uint32_t purple = strip.Color(127,0,255);
uint32_t magenta = strip.Color(142,68,173);
uint32_t hotpink = strip.Color(255,0,255);
uint32_t pink = strip.Color(255,0,127);
uint32_t white = strip.Color(255,255,255);
uint32_t black = strip.Color(0,0,0);
int state = 0;
int th;
DateTime now = rtc.now();

void setup() {
  //Interrupt (In this case, pin 7 is connected to the button)
  // Once the interrupt is activated (ie button is pressed), go to void dls()
  attachInterrupt(digitalPinToInterrupt(7), dls, LOW); 
  
  //Set pin types
  pinMode(dlsPin, INPUT); 
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  //Initialize LED strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //Initialiazation of RTC
  while (!Serial); // for Leonardo/Micro/Zero
  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //Set clock to the current time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  //Measure the potentiometer to determine the brightness of the strip
  int sensorValue = analogRead(potPin);
  strip.setBrightness(sensorValue/5);     //Divide the sensor value by 5 b/c max strip brightness=255 & mas sensorValue=1023(5volts)
  
  //Measure the daylight savings switch to determine its state
  int dlsState = digitalRead(dlsPin);
  
  //Measure the current time
  DateTime now = rtc.now();
  
  //Populate array for "hour mark" LEDs
  int h[] = {0,5,10,15,20,25,30,35,40,45,50,55,0,5,10,15,20,25,30,35,40,45,50,55};
  //Populate array for "minute mark"LEDs
  int m[] = {1,2,3,4,6,7,8,9,11,12,13,14,16,17,18,19,21,22,23,24,26,27,28,29,31,32,33,34,36,37,38,39,41,42,43,44,46,47,48,49,51,52,53,54,56,57,58,59};
  int ts = now.second();
  int tm = now.minute();
  //Use logic to assign daylight savings adjustments based on switch
  int th;
  //if (dlsState == HIGH){
    //th = now.hour()+1;
  //}
  //if (dlsState == LOW){
    //th = now.hour();
  //}
  
  //Choose the color scheme
  uint32_t sHand = hotpink;                //Color of the second hand
  uint32_t mEmpty = blue;                //Color of the unfilled minutes
  uint32_t mFull = green;               //Color of the filled minutes
  uint32_t hHand = red;                 //Color of the hour hand
  uint32_t hMark = orange;                 //Color of the hour markers

  //Illumniate all minutes
  for (int j=0; j<49; j++){
      strip.setPixelColor(m[j], mEmpty);
  }
  //Illuminate current minutes
  for (int k=0; k<=tm; k++){
    strip.setPixelColor(k, mFull);
  }
  //Illuminate all hours
  for (int i=0; i<12; i++){
    strip.setPixelColor(h[i], hMark);
  }
  //Illuminate current hour
  strip.setPixelColor(h[th], hHand);
  strip.setPixelColor(h[th]+1, hHand);
  strip.setPixelColor(h[th]-1, hHand);
  //Illuminate current second
  strip.setPixelColor(ts, sHand);
  strip.show();

}

void dls()
{
  //Turn off strip hour to indicate change
  strip.setPixelColor(h[th], 0,0,0);
  strip.setPixelColor(h[th]+1, 0,0,0);
  strip.setPixelColor(h[th]-1, 0,0,0);
  strip.show();
  // state 0 = "Normal" Time
  // State 1 = Daylight Savings
  // First check previous state, if 0, add 1 to state value and hour
  if (state == 0){
    th = now.hour()+1;
    state = state++;
  }
  //If previous state is 1, switch to 0 and return to normal time
  if (state == 1){
    th = now.hour();
    state = 0;
  }
  //Turn on strip with new hour!
  strip.setPixelColor(h[th], hHand);
  strip.setPixelColor(h[th]+1, hHand);
  strip.setPixelColor(h[th]-1, hHand);
  strip.show();
}

