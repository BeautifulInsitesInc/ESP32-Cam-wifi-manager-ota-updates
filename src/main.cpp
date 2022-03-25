#include <Arduino.h>
#include "wifi_manager.h"
#include "multi_client_RTS.h"

//WebServer server(703);

void setup(){
  Serial.begin(115200); Serial.print("Running Setup");

  wifi_manager_config();
  
  multiclientConfig();

}

void loop() {
  wifi_manager_check_for_reset();
}


  