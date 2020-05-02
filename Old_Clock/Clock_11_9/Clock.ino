//Main clock display
//IF HAVING ISSUES W/ DLS SWITCH, check whether dls adjustment is +1 or -1.  This must vary based upon season when RTC was set.
void fxnClock()
{
  //Check the state of the function selector switch.  Compare value to bins to determine selector location and initiate appropriate function void.
  secondary = analogRead(secondaryPin);

  //Common hues include: Red=0, orange=32, yellow=64, green=96, aqua=128, blue=160, purple=192, pink=224
  //Special minute Hue circumstances (described below) must be indicated in the mSpecial variable
  //mSpecial: 0=no special case, 1=rainbow, 2=rotate through color wheel, 3=white (saturation=0), 4=black (value=0)
  //Styles indicates the general clock face style
  //style: 0=standard clock, 1=2color-pie chart, 2=waxing-pie chart
  //void fxnClockA(byte style, byte mSpecial, uint8_t mHue, uint8_t mHandHue, uint8_t hrHue, uint8_t hrHandHue, uint8_t sHue)

  if (secondary < state1)
  {
    Clock(0, 0, HUE_BLUE, HUE_GREEN, HUE_ORANGE, HUE_RED, HUE_PINK);   //Standard clock face w/ defined color scheme
  }
  else if (secondary > state1 && secondary < state2) {
    Clock(0, 2, 1, 1, 1, 1, 1);   //Standard clock face w/ color scheme that rotates through the color wheel
  }
  else if (secondary > state2 && secondary < state3) {
    Clock(2, 1, 1, 1, 1, 1, 1);  //Waxing minutes w/ fills in color wheel w/ rainbow, white second hand and hour markers
  }
  else if (secondary > state3 && secondary < state4) {
    Clock(2, 1, 4, 1, 1, 1, 1);  //Waxing minutes w/ fills in color wheel w/ 4 rainbows, white second hand and hour markers
  }
  else if (secondary > state4 && secondary < state5) {
    Clock(2, 2, 1, 1, 1, 1, 1);   //Waxing minutes w/ color scheme that rotates through the color wheel
  }
  else if (secondary > state5 && secondary < state6) {
    Clock(2, 0, HUE_GREEN, HUE_BLUE, HUE_ORANGE, HUE_RED, HUE_PINK);    //Pie chart clock face w/ prescribed color scheme
  }
  else if (secondary > state6 && secondary < state7) {
    Clock(0, 4, HUE_ORANGE, HUE_ORANGE, HUE_RED, HUE_PURPLE, HUE_PINK);   //Standard color face w/ minutes are black in order to create minimalist appearance
  }
  else if (secondary > state7) {
    Clock(0, 4, HUE_GREEN, HUE_GREEN, HUE_BLUE, HUE_RED, HUE_ORANGE);   //Standard color face w/ minutes are black in order to create minimalist appearance
  }
}


void Clock(byte style, byte mSpecial, uint8_t mHue, uint8_t mHandHue, uint8_t hrHue, uint8_t hrHandHue, uint8_t sHue)
{
  //Scale the potentiometer reading to set the brightness using the trimPot function from main tab.
  uint8_t brightness = trimPot(0, 255);
  FastLED.setBrightness(brightness);
  //Create variables to be used for special case adjustments
  byte sat = 255;   //Default to fully saturated colors

  //Measure the current time
  DateTime now = rtc.now();
  byte ts = now.second();
  byte tm = now.minute();
  //Use logic to assign daylight savings adjustments based on button press
  byte th;
  if (digitalRead(dlsPin) == HIGH) {
    th = now.hour() + 1;
  }
  else {
    th = now.hour();
  }

  //Set the minute display hues
  //MAY NEED TO ADD BRIGHTNESS VARIABLES TO "fill" IN ORDER TO ADD BRIGHTNESS ADJUSTMENTS
  if (mSpecial == 1)    //Special case: minutes are rainbow color wheel.  mHue value is used to specify the number of full rainbows displayed
  {
    for (byte i = 0; i < mHue; i++) { //Fill the LEDs with the number of rainbows assigned in the mHue variable
      fill_gradient(leds, i * (NUM_LEDS / mHue), CHSV(0, 255, 255), i * (NUM_LEDS / mHue) + (NUM_LEDS / mHue) - 1, CHSV(255, 255, 255), LONGEST_HUES);
    }
    sat = 0;        //Reduces HSV saturation to 0 to create a white light for the hours
  }
  else if (mSpecial == 2)   //Special case: minutes rotate through solid color along color wheel
  {
    //FOR TRANSITION AT THE END OF EVERY MINUTE
    //Set the minutes to vary through color wheel depending on the minute
    //mHue = map((6 * tm) % 59, 0, 59, 0, 255); //Using rate scalar and modulo allows setting of cycles faster than once/hr.
    //FOR SMOOTH TRANSITION THROUGH TIME
    //Set the minutes to vary through color wheel depending on the minute
    mHue = map((60 * (60 * tm + ts)) % 3600, 0, 3600, 0, 255); //Using rate scalar and modulo allows setting of cycles faster than once/hr.
    //Set the minute hand & hour had to contrast the current minute colors
    mHandHue = (mHue + 85) % 265;
    hrHue = (mHue + 127) % 265;
    hrHandHue = (mHue + 170) % 255;
    sHue = hrHandHue;
    fill_solid(leds, NUM_LEDS, CHSV(mHue, 255, 255));
  }
  else if (mSpecial == 4)   //Special case: minutes are turned off
  {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  }
  else    //Fill all LEDs with the specified minute hue when no special case is selected
  {
    fill_solid(leds, NUM_LEDS, CHSV(mHue, 255, 255));
  }


  //Apply the minute style
  if (style == 0)   //Standard clock display with minute and hour markers, with three moving hands
  {
    //Illuminate current minute hand.  Use +30 and Modulo function to compensate for LEDs beginining at "minute 30"
    //Minute hand indicated by 2 LEDs
    leds[(tm + 30) % 60].setHue(mHandHue);
    leds[(tm + 29) % 60].setHue(mHandHue);
  }
  else if (style == 1)    //Clock face where minutes fill as two colored pie chart
  {
    //Illuminate all past minutes.  Use +30 and Modulo function to compensate for LEDs beginining at "minute 30"
    //DO NOT USE fill_solid, because this will give issues for tm>30. This can be overcome with the use of an "if" statement
    //but using a for loop is simpler.
    for (byte i = 0; i < (tm + 1); i++)
    {
      leds[(i + 30) % 60] = CHSV(mHandHue, 255, 255);
    }
  }
  else if (style == 2)     //Clock face where minutes fill in like pie chart on black background
  {
    //Black out future minutes
    for (byte i = tm + 1; i < 60; i++)
    {
      leds[(i + 30) % 60] = CHSV(0, 0, 0);
    }
  }

  //Illuminate hour marks
  for (byte i = 0; i < 60; i += 5)
  {
    leds[i].setHSV(hrHue, sat, 255);
  }
  //Illuminate hour hand.  Use modulo to account hour hands being located every 5th LED, and strip begining at hr=6
  leds[(5 * th + 30) % 60].setHSV(hrHandHue, sat, 255);
  //Illuminate surrounding LED on each side to creat 3 LED hour hand
  leds[(5 * th + 29) % 60].setHSV(hrHandHue, sat, 255);
  leds[(5 * th + 31) % 60].setHSV(hrHandHue, sat, 255);
  //Illuminate second hand.
  leds[(ts + 30) % 60].setHSV(sHue, 255, 255);

  //Show LEDs
  FastLED.show();
}
