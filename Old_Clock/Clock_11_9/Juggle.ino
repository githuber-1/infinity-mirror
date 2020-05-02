//Weaving colored dots.  Void taken from FastLED "DemoReel100"
void fxnJuggle()
{
  while (selector > state6 && selector < state7)
  { //Loop repeats until selector switch is changed.  Must check selector switch condition w/in loop
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy( leds, NUM_LEDS, 20);
    byte dothue = 0;
    for ( int i = 0; i < 8; i++) {
      leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);

    // do some periodic updates
    EVERY_N_MILLISECONDS( 20 )
    {
      gHue++; // slowly cycle the "base color" through the rainbow
    }
    //Verify that function selector switch is at clock position.
    //DO NOT REMOVE THIS LINE OR ELSE THE WHILE LOOP WILL CONTINUE INDEFINITELY.
    selector = analogRead(primaryPin);
  }
}


