#include "main.h"



// ==== SETUP method ==================================================================
void setup()
{

  // Setup Serial connection:
  Serial.begin(115200);
  delay(1000); // wait for a second to let Serial connect
  out("Starting");

  wmSetup();

  //Test if wifi is running
  if (WiFi.status() == WL_CONNECTED) {
    outln("Wifi is connect, and that is a supper good thing!");
    cameraSetup();



  }
  else outln("WiFi is not connnected - bummer");


 




}

long int pin_test_start = millis();
void loop() {
  vTaskDelay(1000);
  wmLoop();

  telenetLoop();

  if (millis() >= pin_test_start + 5000){
    out("Pin number "); out(TRIGGER_PIN); out(" Is Reading : "); outln(digitalRead(TRIGGER_PIN));
    pin_test_start = millis();
  }


}