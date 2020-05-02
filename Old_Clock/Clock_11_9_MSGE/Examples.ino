//Assign all LEDs a static color assigned by the user.
void fxnExamples()
{
  //Check the state of the function selector switch.  Compare value to bins to determine selector location and initiate appropriate function void.
  secondary = analogRead(secondaryPin);

  if (secondary < state1) {
    sinelon(0);       //sinelon w/ user selected color
  }
  else if (secondary > state1 && secondary < state2) {
    sinelon(1);      //sinelon w/ color that cycles at user selected speed
  }
  else if (secondary > state2 && secondary < state3) {
    juggle();       //8 colored dots weaving in and out of eachother in synch
  }
  else if (secondary > state3 && secondary < state4) {
    confetti();     // random colored speckles that blink in and fade smoothly
  }
  else if (secondary > state4 && secondary < state5) {
    bpm();         // colored stripes pulsing at a user defined Beats-Per-Minute (BPM)
  }
  else if (secondary > state5 && secondary < state6) {
    //Add theater chase (user selected)
  }
  else if (secondary > state6 && secondary < state7) {
    //Add theater chase (color wheel cycle)
  }
  else if (secondary > state7) {
    //Add theater chase (rainbow)
  }
  
  //Update the LED display
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

//Sweeping dot.  Void taken from FastLED "DemoReel100"
void sinelon (byte style)
{
  if (style == 1)    //Set hue to rotate at a user selected speed
  {
    byte rate = trimPot (0, 255);     //Read the trimpot to determine color cycle speed
    EVERY_N_MILLISECONDS( rate )
    {
      gHue++; // slowly cycle the "base color" through the rainbow
    }
  }
  else if (style == 0)        //Set hue based on user selection
  {
    gHue = trimPot (0, 255);    //Read the trimpot to determine the color
  }
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 255);
}

// eight colored dots, weaving in and out of sync with each other.  Void taken from FastLED "DemoReel100"
void juggle()
{
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

// random colored speckles that blink in and fade smoothly.  Void taken from FastLED "DemoReel100"
void confetti()
{
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
  //Update hue to cycle through spectrum
  EVERY_N_MILLISECONDS( 20 )
  {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
}

// colored stripes pulsing at a defined Beats-Per-Minute (BPM).  VOid taken from FastLED "DemoReel100"
void bpm()
{
  uint8_t BeatsPerMinute = trimPot (30, 100);      //Set the user defined range of BPMs
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}


