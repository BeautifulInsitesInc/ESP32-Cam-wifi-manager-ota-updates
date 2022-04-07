#include <Arduino.h>
#include "main.h"
long int pin_test_start = millis();
// ==== SETUP method ==================================================================
void setup()
{
  // Setup Serial connection:
  Serial.begin(115200);
  delay(1000); // wait for a second to let Serial connect
  out("Starting");
  
  wmSetup();
  telnetSetup();


  //Test if wifi is running
  if (WiFi.status() == WL_CONNECTED) {
    outln("Wifi is connect, and that is a supper good thing!");
    digitalWrite(AP_LED_PIN, LOW);
    digitalWrite(WIFI_LED_PIN, HIGH);
    cameraSetup();
    //telnetSetup();
  }
  else outln("WiFi is not connnected - bummer");

  pin_test_start = millis();

}




void loop() {
  vTaskDelay(1000);
  wmLoop();

  telenetLoop();

  if (millis() >= pin_test_start + 5000){
    //out("Pin number "); out(TRIGGER_PIN); out(" Is Reading : "); outln(digitalRead(TRIGGER_PIN));
    out("Pin 15 - AP led status : "); outln(digitalRead(AP_LED_PIN)); 
    out("Pin 14 - WIFI led status : "); outln(digitalRead(WIFI_LED_PIN));

    tout("Pin number "); out(TRIGGER_PIN); tout(" Is Reading : "); toutln(digitalRead(TRIGGER_PIN));
    tout("Pin 15 - AP led status : "); out(digitalRead(AP_LED_PIN)); out("Pin 14 - WIFI led status : "); outln(digitalRead(WIFI_LED_PIN));

    pin_test_start = millis();
  }
  tout("It's working!!!!........!!!!");

}