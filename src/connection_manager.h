void connectionManager(){
    WiFi.mode(WIFI_STA);

    pinMode(TRIGGER_PIN, INPUT_PULLUP);
    Serial.print("Trigger pin :"); Serial.print(TRIGGER_PIN);

    // moving this to loop
    WiFiManager wm; //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    
    //wm.resetSettings(); //reset settings - wipe stored credentials for testing

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
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

void connectionManagerLoop(){
    // is configuration portal requested?
    //WiFiManager wm;  moved to setup 
    Serial.print("Button pressed");
    WiFiManager wm; //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around

    //reset settings - for testing
    wm.resetSettings();

    // set configportal timeout
    wm.setConfigPortalTimeout(timeout);

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

