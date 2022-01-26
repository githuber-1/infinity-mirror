// ColorWavesWithPalettes
// Animated shifting color waves, with several cross-fading color palettes.
// by Mark Kriegsman, August 2015
//
// Color palettes courtesy of cpt-city and its contributors:
//   http://soliton.vm.bytemark.co.uk/pub/cpt-city/
//
// Color palettes converted for FastLED using "PaletteKnife" v1:
//   http://fastled.io/tools/paletteknife/
//

// This function draws color waves with an ever - changing,
// widely-varying set of parameters, using a color palette.
void fxnColorwave()
{
  //Check the state of the function selector switch.  Compare value to bins to determine selector location and initiate appropriate function void.
  secondary = analogRead(secondaryPin);

  // Current palette number from the 'playlist' of color palettes
  uint8_t gCurrentPaletteNumber = 0;

  CRGBPalette16 gCurrentPalette( CRGB::Black);
  CRGBPalette16 gTargetPalette( gGradientPalettes[0] );

  if (secondary < state1) {
    gCurrentPalette = 0;
    colorwaves( leds, NUM_LEDS, gCurrentPalette);
  }
  else if (secondary > state1 && secondary < state2) {
    gCurrentPalette = 1;
    colorwaves( leds, NUM_LEDS, gCurrentPalette);
  }
  else if (secondary > state2 && secondary < state3) {
    gCurrentPalette = 2;
    colorwaves( leds, NUM_LEDS, gCurrentPalette);
  }
  else if (secondary > state3 && secondary < state4) {
    gCurrentPalette = 3;
    colorwaves( leds, NUM_LEDS, gCurrentPalette);
  }
  else if (secondary > state4 && secondary < state5) {
    gCurrentPalette = 4;
    colorwaves( leds, NUM_LEDS, gCurrentPalette);
  }
  else if (secondary > state5 && secondary < state6) {
    gCurrentPalette = 5;
    colorwaves( leds, NUM_LEDS, gCurrentPalette);
  }
  else if (secondary > state6 && secondary < state7) {
    gCurrentPalette = 6;
    colorwaves( leds, NUM_LEDS, gCurrentPalette);
  }
  else {
    EVERY_N_SECONDS( SECONDS_PER_PALETTE ) {
      gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
      gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
    }
    EVERY_N_MILLISECONDS(40) {
      nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
    }
    colorwaves( leds, NUM_LEDS, gCurrentPalette);
  }
  FastLED.show();
  FastLED.delay(20);
}


void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette)
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  for ( uint16_t i = 0 ; i < numleds; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if ( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    uint8_t index = hue8;
    //index = triwave8( index);
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( palette, index, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numleds - 1) - pixelnumber;

    nblend( ledarray[pixelnumber], newcolor, 128);
  }
  FastLED.show();
  FastLED.delay(20);
}


/*
  // Alternate rendering function just scrolls the current palette
  // across the defined LED strip.
  void palettetest( CRGB* ledarray, uint16_t numleds, const CRGBPalette16& gCurrentPalette)
  {
  static uint8_t startindex = 0;
  startindex--;
  fill_palette( ledarray, numleds, startindex, (256 / NUM_LEDS) + 1, gCurrentPalette, 255, LINEARBLEND);
  }
*/
