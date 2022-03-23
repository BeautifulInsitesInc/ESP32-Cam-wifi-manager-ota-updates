#include <Arduino.h>
#include <WiFiManager.h>
#include <WiFi.h>

WebServer server(702);
IPAddress ip;

// --- Multiclient camera streaming server
//#include "multiclient_init.h"
#include "multiclient_server.h"

// -- Wifi Manager
#define TRIGGER_PIN 2 // push button to reset 
int timeout = 120; // seconds to run for

bool wm_nonblocking = false; // change to true to use non blocking

WiFiManager wm; // global wm instance
WiFiManagerParameter custom_field; // global param ( for non blocking w params )

//-- Wifi manager functions ----
String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback(){
  Serial.println("[CALLBACK] saveParamCallback fired");
  Serial.println("PARAM customfieldid = " + getParam("customfieldid"));
}
// --- Wifi manager functions

void setup(){
  WiFi.mode(WIFI_STA);

  Serial.begin(115200); Serial.print("Running Setup");
  Serial.setDebugOutput(true);
  
  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  if(wm_nonblocking) wm.setConfigPortalBlocking(false);
  int customFieldLength = 40;// add a custom input field

  // new (&custom_field) WiFiManagerParameter("customfieldid", "Custom Field Label", "Custom Field Value", customFieldLength,"placeholder=\"Custom Field Placeholder\"");
  
  // test custom html input type(checkbox)
  // new (&custom_field) WiFiManagerParameter("customfieldid", "Custom Field Label", "Custom Field Value", customFieldLength,"placeholder=\"Custom Field Placeholder\" type=\"checkbox\""); // custom html type
  
  // test custom html(radio)
  const char* custom_radio_str = "<br/><label for='customfieldid'>Custom Field Label</label><input type='radio' name='customfieldid' value='1' checked> One<br><input type='radio' name='customfieldid' value='2'> Two<br><input type='radio' name='customfieldid' value='3'> Three";
  new (&custom_field) WiFiManagerParameter(custom_radio_str); // custom html input
  
  wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);

  // custom menu via array or vector
  // 
  // menu tokens, "wifi","wifinoscan","info","param","close","sep","erase","restart","exit" (sep is seperator) (if param is in menu, params will not show up in wifi page!)
  // const char* menu[] = {"wifi","info","param","sep","restart","exit"}; 
  // wm.setMenu(menu,6);
  std::vector<const char *> menu = {"wifi","info","param","sep","restart","exit"};
  wm.setMenu(menu);



  // set dark theme
  wm.setClass("invert");

  //set static ip
  // wm.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0)); // set static ip,gw,sn
  // wm.setShowStaticFields(true); // force show static ip fields
  // wm.setShowDnsFields(true);    // force show dns field always

  wm.setConfigPortalTimeout(30);

  bool res;
  res = wm.autoConnect("Auto Connect"); // anonymous ap
  //res = wm.autoConnect("AutoConnectAP","password"); // password protected ap
  if(!res) {
      Serial.println("Failed to connect");
      // ESP.restart();
  } 
  else {
      //if you get here you have connected to the WiFi    
      Serial.println("connected at setup..yeey :)");
      multiclientConfig();
  }
}

void loop() {
  //vTaskDelay(1000);
  if(wm_nonblocking) wm.process();// avoid delays() in loop when non-blocking and other long running code 
  if (digitalRead(TRIGGER_PIN) == LOW) {
    //WiFiManager wm;
    Serial.println("Reset Button pressed - restarting");
    wm.resetSettings(); //reset settings - wipe stored credentials for testing
    ESP.restart();
  }
}


  