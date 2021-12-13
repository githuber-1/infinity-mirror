// Day light savings switch confirmed to work on Infinity Mirror_a_Built-6-2-2020 on 6-20-2020
// primarySelector Analog Input confirmed to work on Infinity Mirror_a_Built-6-2-2020 on 6-20-2020
// secondarySelector Analog Input confirmed to work on Infinity Mirror_a_Built-6-2-2020 on 6-20-2020
// potPin Analog Input confirmed to work on Infinity Mirror_a_Built-6-2-2020 on 6-20-2020
const byte primaryPin = 0;
const byte secondaryPin = 1;
const byte potPin = 2;
const byte dlsPin = 3;

int primarySelector;
int secondarySelector;
int potInput;
int dlsDigital;
byte dls;


void setup() {
  delay(250);
  Serial.begin(9600);
  pinMode(primaryPin, INPUT);
  pinMode(secondaryPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(dlsPin, INPUT);
  
}

void loop() {
  primarySelector = analogRead(primaryPin);
  secondarySelector = analogRead(secondaryPin);
  potInput = analogRead(potPin);
  dlsDigital = digitalRead(dlsPin);

  Serial.print("primary", primarySelector);
  Serial.print(",");
  Serial.print("secondary", secondarySelector);
  Serial.print(",");
  Serial.println("potInput", potInput);
//  Serial.println(dlsDigital);
  
  
  delay(750);

  
  

}
