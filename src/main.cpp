#include "camera_1.h"



// ==== SETUP method ==================================================================
void setup()
{

  // Setup Serial connection:
  Serial.begin(115200);
  delay(1000); // wait for a second to let Serial connect

  cameraSetup();
  
}


void loop() {
  vTaskDelay(1000);
}