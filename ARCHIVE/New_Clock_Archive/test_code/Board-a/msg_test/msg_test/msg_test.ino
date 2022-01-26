// Confirmed that Infinity Mirror_a_Built-6-2-2020 works with MSGEQ7 on 6-20-2020s

int strobePin = 8;
int resetPin = 10;
int outPin = A3;
int level[7];

void setup() {
 
  Serial.begin (9600);
 
  // Define our pin modes
  pinMode      (strobePin, OUTPUT);
  pinMode      (resetPin,  OUTPUT);
  pinMode      (outPin,    INPUT);
 
  // Create an initial state for our pins
  digitalWrite (resetPin,  LOW);
  digitalWrite (strobePin, LOW);
  delay        (1);
 
  // Reset the MSGEQ7 as per the datasheet timing diagram
  digitalWrite (resetPin,  HIGH);
  delay        (1);
  digitalWrite (resetPin,  LOW);
  digitalWrite (strobePin, HIGH); 
  delay        (1);
 
}

void loop() {
  
  // Cycle through each frequency band by pulsing the strobe.
  for (int i = 0; i < 7; i++) {
    digitalWrite       (strobePin, LOW);
    delayMicroseconds  (100);                  // Delay necessary due to timing diagram
    level[i] =         analogRead (outPin);
    digitalWrite       (strobePin, HIGH);
    delayMicroseconds  (1);                    // Delay necessary due to timing diagram  
  }
 
  for (int i = 0; i < 7; i++) {
    if(i == 0){
      Serial.print       (level[i]);
    }
//    Serial.print       (level[i]);
//    Serial.print       (",");
  }
 
  Serial.println ();  
 
}
