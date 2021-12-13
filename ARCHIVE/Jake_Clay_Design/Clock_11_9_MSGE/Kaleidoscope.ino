//This void creates a number of symmetrical color gradients accross the LED display.
//Adjusting the input variables drastically changes the resulting display
////Using static versions and small hueDelta versions creates displays applicable to static/dynamic primary functions.
//Used sd to specify which variables are changed by the potentiometer
////sd=0 is for static states in which colors only change based on the potentiometer.  A constant hueDelta is used
////sd=1 is for dynamic states in which the rate of color cycling changes with the potentiometer.  A constant hueDelta is used
////sd=2 is for dynamic states in which the rate of color cycling is constant and hueDelta is changed via potentiometer.
//The symPts is used to specify the number of "points" that new hues radiate from.
////The number of points will be equal to half of this value
////For best displays, specify values of symPts that are factors of 60. (1,2,3,4,5,6,10,12,15,20,30,60)
//////Even values of symPts (2,4,6,20,12,20,30,60) are preferrable in order to make the display continuous.
//////Higher values of symPts (ie, 20, 30, 60) yield patterns similar to static displays.
////////This applies to increasingly small symPts values as hueDelta is increased towards 255.
//hueDelta is used to specify the separation of colors displayed in the gradient at any given instant.
////Smaller hueDelta values give a smaller variety of colors, but a more consistent color "temperature" profile
////Larger hueDelta values give a larger variety of colors with smaller display widths.
//rate is only used for sd=2 and selects the rate of the dynamic pattern,
///Suggested rate values are 1-10.
//Assign all LEDs a static color assigned by the user.
void fxnKaleidoscope()
{
  //Check the state of the function selector switch.  Compare value to bins to determine selector location and initiate appropriate function void.
  secondary = analogRead(secondaryPin);

  if (secondary < state1) {
    kaleidoscope (1, 6, 100, 0);   //3 point, adjustable speed.
  }
  else if (secondary > state1 && secondary < state2) {
    kaleidoscope (1, 10, 100, 0);  //5 point, adjustable speed.
  }
  else if (secondary > state2 && secondary < state3) {
    kaleidoscope (1, 12, 100, 0);  //12 point, adjustable speed.
  }
  else if (secondary > state3 && secondary < state4) {
    kaleidoscope (2, 6, 100, 2);   //3 point, adjustable gradient length
  }
  else if (secondary > state4 && secondary < state5) {
    kaleidoscope (2, 10, 100, 2);   //5 point, adjustable gradient length
  }
  else if (secondary > state5 && secondary < state6) {
    kaleidoscope (2, 12, 100, 2);   //6 point, adjustable gradient length
  }
  else if (secondary > state6 && secondary < state7) {
    kaleidoscope (0, 6, 255, 0);     //Potentiometer controlled kaleidoscope
  }
  else if (secondary > state7) {
    kaleidoscope (0, 10, 255, 0);  //Potentiometer controlled kaleidoscope
  }
}



void kaleidoscope (uint8_t sd, uint8_t symPts, uint8_t hueDelta, uint8_t rate)
{
  static uint8_t wheelState = 0;    //Initialize a variable to hold the state of the first hue used in the gradient.
  //Set whether a static or dynamic display will be used
  if (sd == 0) {       //For the static version of this, use the trimPot to determine color reading to 0-255 position of color wheel.
    wheelState = trimPot (0, 255);
  }
  else if (sd == 1) {     //For the dynamic version of this, use the trimPot to determine the rate of color wheel transition.
    rate = trimPot(0, 10);
    EVERY_N_MILLISECONDS( 50 )
    {
      wheelState += rate;     //Add the value of rate to the existing value of wheelState
    }
  }
  else if (sd == 2) {     //For either static or dynamic versions, this variation allows for adjustments of the hueDelta value.  Larger values result in a larger variety of colors displayed at a given time.
    hueDelta = trimPot (60, 255);
    EVERY_N_MILLISECONDS( 50 )
    {
      wheelState += rate;   //Change this integer to adjust the speed of the kaleidoscope
    }
  }
  uint8_t wheelStateB = wheelState + hueDelta;     //Create a second hue that will be offset from the first hue for the gradients below.
  for (byte i = 0; i < symPts; i++)
  {
    if (i % 2 == 0) { //If even even iteration of for loop, use forward hues
      fill_gradient(leds, i * (NUM_LEDS / symPts), CHSV(wheelState, 255, 255), ((i + 1) * (NUM_LEDS / symPts)) - 1, CHSV(wheelStateB, 255, 255), FORWARD_HUES);
    }
    else if (i % 2 == 1) //If odd iteration of for loop, use backward hues so that patern mirrors the even iteration on the previous group of LEDs
    {
      fill_gradient(leds, i * (NUM_LEDS / symPts), CHSV(wheelStateB, 255, 255), ((i + 1) * (NUM_LEDS / symPts)) - 1, CHSV(wheelState, 255, 255), BACKWARD_HUES);
    }
  }
  //Show the LEDs and delay to keep frame rate appropriate
  FastLED.show();
  FastLED.delay(500 / FRAMES_PER_SECOND);
}
