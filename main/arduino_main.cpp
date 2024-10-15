#include "sdkconfig.h"
#include <Arduino.h>

#define LED_BUILTIN 2 // defines the word "LED_BUILTIN" as the number 2 for ease of use/readability when using the pin later

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
     // configures pin 2 to be a GPIO output pin 
}

void loop() {
    Serial.println("IS IT WORKING");
    digitalWrite(LED_BUILTIN, HIGH); // writes a digital high to pin 2
    delay(1000); // waits for 1000 milliseconds (1 second)
    digitalWrite(LED_BUILTIN, LOW); // writes a digital low to pin 2
    delay(1000);
    Serial.println("K Diddy");
}
