#include <Arduino.h>

const unsigned long INTERVAL = 1000; // interval to wait between LED toggles

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW); 
  Serial.begin(115200);
  delay(2000);

  Serial.println("Setting up, done !");
}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Led High");
  delay(INTERVAL);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Led Low");
  delay(INTERVAL);
}
