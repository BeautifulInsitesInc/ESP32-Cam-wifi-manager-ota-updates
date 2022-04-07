#ifndef FUNCTIONS_H // This is so if it included in mulitple cpp files, the code will not be duplicated
#define FUNCTIONS_H

/**
 * WiFiManager advanced demo, contains advanced configurartion options
 * Implements TRIGGEN_PIN button press, press for ondemand configportal, hold for 3 seconds for reset settings.
 */

#define TRIGGER_PIN 13
#define AP_LED_PIN 15
#define WIFI_LED_PIN 14
#define LED_PIN 33

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager


String ap_name = "Cam AP";
String ap_password = "password"; // password for the local AP

// wifimanager can run in a blocking mode or a non blocking mode
// Be sure to know how to process loops with no delay() if using non blocking
bool wm_nonblocking = false; // change to true to use non blocking

WiFiManager wm; // global wm instance
WiFiManagerParameter custom_field; // global param ( for non blocking w params )



void checkButton(){
  // check for button press
  //out("checking button ... status :"); out(digitalRead(TRIGGER_PIN)); out("  for pin "); outln(TRIGGER_PIN);
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(AP_LED_PIN, HIGH);
    // poor mans debounce/press-hold, code not ideal for production
    delay(1000);
    digitalWrite(AP_LED_PIN, LOW);
    if( digitalRead(TRIGGER_PIN) == LOW ){
      
      Serial.println("Button Pressed");
      // still holding button for 3000 ms, reset settings, code not ideaa for production
      delay(3000); // reset delay hold
      

      if( digitalRead(TRIGGER_PIN) == LOW ){
        digitalWrite(AP_LED_PIN, HIGH);
        digitalWrite(WIFI_LED_PIN, LOW);
        Serial.println("Button Held");
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();
        ESP.restart();
      }
      
      // start portal w delay
      Serial.println("Starting config portal");
      wm.setConfigPortalTimeout(120);
      
      
      if (!wm.startConfigPortal("OnDemandAP","password")) {
        Serial.println("failed to connect or hit timeout");
        digitalWrite(AP_LED_PIN, HIGH);
        delay(3000);
        //ESP.restart();
      } else {
        //if you get here you portal has started
        Serial.println("connected to AP?...yeey :)");
        digitalWrite(AP_LED_PIN, HIGH);
        digitalWrite(WIFI_LED_PIN, LOW);
        
      }
    }
 
  }
  digitalWrite(LED_PIN, HIGH);
  
}


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






void wmSetup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  

  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(AP_LED_PIN, OUTPUT);
  pinMode(WIFI_LED_PIN, OUTPUT);

  
  //wm.resetSettings(); // wipe settings

  if(wm_nonblocking) wm.setConfigPortalBlocking(false);

  // add a custom input field
  int customFieldLength = 40;


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

  // wm.setConnectTimeout(20); // how long to try to connect for before continuing
  wm.setConfigPortalTimeout(30); // auto close configportal after n seconds
  // wm.setCaptivePortalEnable(false); // disable captive portal redirection
  // wm.setAPClientCheck(true); // avoid timeout if client connected to softap

  // wifi scan settings
  // wm.setRemoveDuplicateAPs(false); // do not remove duplicate ap names (true)
  // wm.setMinimumSignalQuality(20);  // set min RSSI (percentage) to show in scans, null = 8%
  // wm.setShowInfoErase(false);      // do not show erase button on info page
  // wm.setScanDispPerc(true);       // show RSSI as percentage not graph icons
  
  // wm.setBreakAfterConfig(true);   // always exit configportal even if wifi save fails

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("Cam Auto AP","password"); // password protected ap
  digitalWrite(AP_LED_PIN, HIGH);
  digitalWrite(WIFI_LED_PIN, LOW);
  
  if(!res) {
    Serial.println("Failed to connect or hit timeout");
    digitalWrite(AP_LED_PIN, HIGH);
    digitalWrite(WIFI_LED_PIN, LOW);
    //ESP.restart();
  } 
  else {
    //if you get here you have connected to the WiFi    
    Serial.println("connected to wifi...yeey :)");
    digitalWrite(AP_LED_PIN, LOW);
    digitalWrite(WIFI_LED_PIN, HIGH);
  }
}



void wmLoop() {
  if(wm_nonblocking) wm.process(); // avoid delays() in loop when non-blocking and other long running code  
  checkButton();
  // put your main code here, to run repeatedly:
}

#endif