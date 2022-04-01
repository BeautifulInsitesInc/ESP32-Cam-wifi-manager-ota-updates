#include "main.h"
#include "wifi_manager.h"
#include "camera_RTS.h"


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


void loop() {
  vTaskDelay(1000);
  wmLoop();


}