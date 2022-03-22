#include <Arduino.h>
#include <WiFiManager.h>
#include <WiFi.h>

WebServer server(702);
IPAddress ip;

// On demand AP
#define TRIGGER_PIN 2
int timeout = 120; // seconds to run for

#include "multiclient_server.h"
#include "multiclient_init.h"
#include "connection_manager.h"
//#include "original_connection.h"


// ==== SETUP method ==================================================================
void setup()
{
  // Setup Serial connection:
  Serial.begin(115200);
  Serial.print("Running Setup");
  
  connectionManager();
  //originalConnection();
  
}

void loop() {
  vTaskDelay(1000);
  if (digitalRead(TRIGGER_PIN) == LOW) connectionManagerLoop();

}


  