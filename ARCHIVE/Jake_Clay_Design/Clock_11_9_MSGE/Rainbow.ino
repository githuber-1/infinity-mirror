void fxnRainbow()
{
  //Check the state of the function selector switch.  Compare value to bins to determine selector location and initiate appropriate function void.
  secondary = analogRead(secondaryPin);

  if (secondary < state1) {
    //Single Rainbow
    Rainbow(1);
  }
  else if (secondary > state1 && secondary < state2) {
    //Double rainbow
    Rainbow(2);
  }
  else if (secondary > state2 && secondary < state3) {
    //Triple Rainbow
    Rainbow(3);
  }
  else if (secondary > state3 && secondary < state4) {
    //Quad Rainbow
    Rainbow(4);
  }
  else if (secondary > state4 && secondary < state5) {
    //Rainbow waves move symettrically down the LEDs, starting from one point.  User selects speed of waves
    
  }
  else if (secondary > state5 && secondary < state6) {
    //Rainbow waves move symettrically down the LEDs, starting from two points.  User selects length of waves
    
  }
  else if (secondary > state6 && secondary < state7) {
    
  }
  else if (secondary > state7) {

  }
}

//Fill LEDs w/ a function specified number of rainbows.  User controls speed of rotation
void Rainbow(byte nRainbows)
{
  //Use the trimpot to determine how fast the rainbows should be rotating
  byte rate = trimPot(0, 20);     //Changing the min/max of this fxn will determine the range of rotation speeds
  static uint8_t wheelState = 0;   //Create a variable to store the offset value.  Use static so that this is only called once.
  //Create an incrementing offset so that the start position of the rainbows moves forward
  EVERY_N_MILLISECONDS( 50 )
  {
    wheelState += rate; // Increment the starting hue of the rainbow gradient based on user selected rate.
  }

  //Fill the LEDs with first rainbow pattern.
  //Set the ends of each rainbow to always be one hue away and take the longest hue pathway.  This creates a rainbow without the need to change position of starting LED.
  //Using a start position offset will create problems when a rainbow segment spans the end of the LED strip
  //Use a for loop to ensure the correct number of rainbow gradients fills the LED strip
  for (byte i = 0; i < nRainbows; i++)
  {
    fill_gradient(leds, i * (NUM_LEDS / nRainbows), CHSV(wheelState, 255, 255), ((NUM_LEDS / nRainbows) - 1) + (i * (NUM_LEDS / nRainbows)), CHSV(wheelState - 1, 255, 255), LONGEST_HUES);
  }
  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

