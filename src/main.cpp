#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  // initialize digital pin SPEAKER as an output.
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(SPEAKER, HIGH);   // turn the SPEAKER on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(SPEAKER, LOW);    // turn the SPEAKER off by making the voltage LOW
  delay(1000); 
}