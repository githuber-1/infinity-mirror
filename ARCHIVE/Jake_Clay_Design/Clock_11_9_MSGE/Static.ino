//Assign all LEDs a static color assigned by the user.
void fxnStatic()
{
  //Check the state of the function selector switch.  Compare value to bins to determine selector location and initiate appropriate function void.
  secondary = analogRead(secondaryPin);

  //See the kaleidoscope function tab for descriptions on how the three input variables affect the display.
  if (secondary < state1) {
    kaleidoscope(0, 1, 0, 0); //Solid color, defined by user
  }
  else if (secondary > state1 && secondary < state2) {
    kaleidoscope(0, 60, 128, 0);  //2 alternating complimentary colors, defined by user
  }
  else if (secondary > state2 && secondary < state3) {
    kaleidoscope(0, 30, 128, 0); //2 alternating complimentray colors (2 LED wide segments, defined by user
  }
  else if (secondary > state3 && secondary < state4) {
    kaleidoscope(0, 20, 60, 0); //1xA,2xB,1xA,2xC pattern of user selected colors, small gradient for consistent color temperatures
  }
  else if (secondary > state4 && secondary < state5) {
    kaleidoscope(0, 20, 170, 0); //1xA,2xB,1xA,2xC pattern of user selected colors, large gradient for a variety of colors
  }
  else if (secondary > state5 && secondary < state6) {
    kaleidoscope(0, 12, 85, 0);   //Gradient display with low color variety for consistent display temperature
  }
  else if (secondary > state6 && secondary < state7) {

  }
  else if (secondary > state7) {

  }
}
