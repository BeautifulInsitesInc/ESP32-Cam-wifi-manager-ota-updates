#include <WiFiManager.h> 

#define TRIGGER_PIN 0
long port_number;
bool shouldSaveConfig = false;//flag for saving data

//callback notifying us of the need to save config

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

WiFiManager wm;

void wifi_manager_config(){
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP   
  //bool wm_nonblocking = false; // change to true to use non blocking

  //wm.setDebugOutput(false); // suppress debuggin info
  //wm.setConfigPortalBlocking(false);

  //SPIFFS.format(); //clean FS, for testing

  // Define the extra fields
  //WiFiManagerParameter("customfieldid", "Custom Field Label", "Custom Field Value", customFieldLength,"placeholder=\"Custom Field Placeholder\"");
  WiFiManagerParameter static_ip_box("static_ip_id", "Static IP", "10.10.10.75", 16);
  WiFiManagerParameter static_gw_box("static_gw_id", "Gateway", "10.10.10.2", 16);
  WiFiManagerParameter static_sn_box("static_sn_id", "Subnet", "255.255.255.0", 16); 
  WiFiManagerParameter port_box("port_id", "Port", "705", 8);

  // 2 steps to getting custom fields up, now add the boxes: 
  wm.addParameter(&static_ip_box);
  wm.addParameter(&static_gw_box);
  wm.addParameter(&static_sn_box);
  wm.addParameter(&port_box);

  //set config save notify callback
  //wm.setSaveConfigCallback(saveConfigCallback);

  //set static ip
    IPAddress _ip, _gw, _sn;
    _ip.fromString(static_ip_box.getValue());
    _gw.fromString(static_gw_box.getValue());
    _sn.fromString(static_sn_box.getValue());
    port_number = atol(port_box.getValue());

    wm.setSTAStaticIPConfig(_ip, _gw, _sn);
    
    
    //wm.setMinimumSignalQuality(10);//set minimu quality of signal so it ignores AP's under that quality defaults to 8%
    
    //wm.setTimeout(120);//sets timeout until configuration portal gets turned off useful to make it all retry or go to sleep in seconds

  // wifi manager connect
    if (!wm.autoConnect("Auto Connect")){ //if (wm.autoConnect("AutoConnectAP", "password")) {  // include password
        Serial.println("failed to connect and hit timeout");
        ESP.restart();//reset and try again, or maybe put it to deep sleep
        delay(1000);
    }
    // Connected!
    Serial.println("Wifi Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Server Port : "); Serial.print(port_number);







}

void wifi_manager_check_for_reset(){
  // --- Check for reset press ----
  if (digitalRead(TRIGGER_PIN) == LOW){
      Serial.println("Reset Button Pressed, but not yet triggered");
      delay(2000);// if still holding for 2 seconds, reset settings
      if (digitalRead(TRIGGER_PIN) == LOW ){
          Serial.print("Button Held, Erasing Config and Restarting...");
          wm.resetSettings();
          ESP.restart();
      } 
  }
  // --- End check for reset press ---
}