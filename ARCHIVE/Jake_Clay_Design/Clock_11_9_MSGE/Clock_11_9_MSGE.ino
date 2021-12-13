#include "FastLED.h"
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;


//Define pin locations
const byte primaryPin = 0;       //Analog pin connected to output from SP8T switch.  Each of the 8T connected to different point along string of 7x330_Ohm series btwn 5V-GND (thus acting as trimpot).
const byte secondaryPin = 1;     //Analog pin connected to output from SP8T switch.
const byte potPin = 2;           //Analog pin connected to output from potentiometer
const byte msgoutPin = 3;        //Analog pin connected to output from MSGEQ7
const byte msgstrobePin = 7;     //Analog pin connected to MSGEQ7 strobe
const byte msgresPin = 8;        //Analog pin connected to MSGEQ7 reset
//Define MSGEQ7 array and variable
int freqbands[7];                //Array storing frequency band values from MSGEQ7
int band;                        //
//RTC "SDA" connected to analog pin 4
//RTC "SCL" connected to analog pin 5
const byte dlsPin = 3;       //Digital pin connected to SDST toggle switch for daylight savings adjustments.
//Connect 1000_uF accros 5V-GND of NeoPixels to prevent surges and thus prolong LED lifespan


//Define FastLED parameters:
#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    NEOPIXEL
#define COLOR_ORDER RGB
#define NUM_LEDS    60
#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  120
CRGB leds[NUM_LEDS];


//Global variables needed for button cycling and storage of daylight savings setting
int selector;      //Stores the current analog reading of the SP8T primary function selector switch
int secondary;      //Stores the current analog reading of the SP8T secondary function selector switch
byte state;        //Stores the state of the button increment and thus the current mirror display
byte dls;          //Stores the state of the daylight savings selection
uint8_t gHue = 0;  // rotating "base color" used by many of the patterns


//Set the analog bins used to determine the state of the SP8T function selector switch.
//Each state position will be connected to a different position along a series of resistors to ensure uniform bin spacing.
//Analog reading will vary from 0-1053 (0V-5V).
const int state1 = 131;
const int state2 = 263;
const int state3 = 395;
const int state4 = 527;
const int state5 = 659;
const int state6 = 791;
const int state7 = 923;

//Parameters for colorwave
// ten seconds per color palette makes a good demo
// 20-120 is better for deployment
#define SECONDS_PER_PALETTE 30

//Create prototypes for the functions to prevent compiler errors due to tabs
void fxnClock(void);
void fxnColorwave(void);
void fxnDynamic(void);
void fxnExamples(void);
void fxnJuggle(void);
void fxnKaleidoscope (void);
void fxnRainbow(void);
void fxnSD(void);
void fxnSinelon(void);
void fxnStatic(void);


// Forward declarations of an array of cpt-city gradient palettes, and
// a count of how many there are.  The actual color palette definitions
// are at the bottom of this file.
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;

// Current palette number from the 'playlist' of color palettes
uint8_t gCurrentPaletteNumber = 0;

CRGBPalette16 gCurrentPalette( CRGB::Black);
CRGBPalette16 gTargetPalette( gGradientPalettes[0] );



void setup() {
  delay(3000); // 3 second delay for recovery
  Serial.begin(115200);
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  //Set pin types
  pinMode(potPin, INPUT);
  pinMode(primaryPin, INPUT);
  pinMode(secondaryPin, INPUT);
  pinMode(dlsPin, INPUT);
  pinMode(msgoutPin, OUTPUT);
  pinMode(msgstrobePin, OUTPUT);
  pinMode(msgresPin, OUTPUT);
  digitalWrite(msgresPin, LOW);
  digitalWrite(msgstrobePin, HIGH);

          //Initialiazation of RTC
          while (!Serial); // for Leonardo/Micro/Zero
          Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
      while (1);
    }
  if (! rtc.isrunning()) {
  Serial.println("RTC is NOT running!");
  }
  //Set clock to the current time.  Only include this line for the initial clock set.  Then comment out line and re-upload.
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}



void loop()
{
  //Check the state of the function selector switch.  Compare value to bins to determine selector location and initiate appropriate function void.
  selector = analogRead(primaryPin);
  if (selector < state1) {
    fxnClock();
  }
  else if (selector > state1 && selector < state2) {
    fxnStatic();
  }
  else if (selector > state2 && selector < state3) {
    fxnRainbow();
  }
  else if (selector > state3 && selector < state4) {
    fxnColorwave();
  }
  else if (selector > state4 && selector < state5) {
    fxnExamples();
  }
  else if (selector > state5 && selector < state6) {
    fxnKaleidoscope();
  }
  /*Other fxns to be added
    else if (selector > state6 && selector < state7) {
    fxn();
    }
    else if (selector > state7) {
    fxnMusic();
    }
  */
  //Reset the brightness setting so that brightness of each function is independent
  FastLED.setBrightness(255);
}

//Create function to return a scaled value based on the potentiometer postition
//This will be called in many voids
uint8_t trimPot (int Min, int Max)
{
  uint8_t result;
  result = map(analogRead(potPin), 0, 1053, Min, Max);
  return result;
}
