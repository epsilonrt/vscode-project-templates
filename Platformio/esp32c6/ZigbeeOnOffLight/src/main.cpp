// Copyright 2024 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
   @brief This example demonstrates simple Zigbee light bulb.

   The example demonstrates how to use Zigbee library to create a end device light bulb.
   The light bulb is a Zigbee end device, which is controlled by a Zigbee coordinator.

   Proper Zigbee mode must be selected in Tools->Zigbee mode
   and also the correct partition scheme must be selected in Tools->Partition Scheme.

   Please check the README.md for instructions and more detailed description.

   Created by Jan Procházka (https://github.com/P-R-O-C-H-Y/)
*/

#ifndef ZIGBEE_MODE_ZCZR
#error "Zigbee coordinator mode is not selected in Tools->Zigbee mode"
#endif

#include <Arduino.h>
#include <Zigbee.h>

/* Zigbee light bulb configuration */
#define ZIGBEE_LIGHT_ENDPOINT 1
uint8_t led = LED_BUILTIN;
uint8_t button = BOOT_PIN;

ZigbeeLight zbLight = ZigbeeLight (ZIGBEE_LIGHT_ENDPOINT);

/********************* RGB LED functions **************************/
void setLED (bool value) {
  #if defined(ARDUINO_XIAO_ESP32C6)
  digitalWrite (led, !value);
  #else
  digitalWrite (led, value);
  #endif
}

/********************* Arduino functions **************************/
void setup() {
  Serial.begin (115200);
  delay (1000);

  // Init LED and turn it OFF (if LED_PIN == RGB_BUILTIN, the rgbLedWrite() will be used under the hood)
  pinMode (led, OUTPUT);
  setLED (false);

  // Init button for factory reset
  pinMode (button, INPUT_PULLUP);

  //Optional: set Zigbee device name and model
  zbLight.setManufacturerAndModel ("Espressif", "ZBLightBulb");

  // Set callback function for light change
  zbLight.onLightChange (setLED);

  //Add endpoint to Zigbee Core
  Serial.println ("Adding ZigbeeLight endpoint to Zigbee Core");
  Zigbee.addEndpoint (&zbLight);

  // When all EPs are registered, start Zigbee. By default acts as ZIGBEE_END_DEVICE
  if (!Zigbee.begin()) {
    Serial.println ("Zigbee failed to start!");
    Serial.println ("Rebooting...");
    ESP.restart();
  }

  Serial.println ("Connecting to network");
  while (!Zigbee.connected()) {

    Serial.print (".");
    delay (100);
  }
  Serial.println();
}

void loop() {
  static bool oldState = false;

  // Checking button for factory reset
  if (digitalRead (button) == LOW) { // Push button pressed
    int count = 0;

    // Key debounce handling
    delay (20);
    int startTime = millis();

    while (digitalRead (button) == LOW) {

      count++;
      delay (20);

      if ( (millis() - startTime) > 3000) {
        // If key pressed for more than 3secs, factory reset Zigbee and reboot
        Serial.println ("Resetting Zigbee to factory and rebooting in 1s.");
        delay (1000);
        Zigbee.factoryReset(); // Factory reset Zigbee (all data in NVRAM will be lost) and restart
      }
    }

    if (count > 1) { //  Push button still pressed

      zbLight.setLight (!zbLight.getLightState());
    }
  }
  
  if (oldState != zbLight.getLightState()) {
    // Light state changed, print the new state to Serial
    Serial.printf ("Light state changed to: %s\n", zbLight.getLightState() ? "ON" : "OFF");
    oldState = zbLight.getLightState();
  }
  delay (100);
}
