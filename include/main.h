#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <WiFiMulti.h>
#include <ElegantOTA.h>



#define DEBUG_PRE_WIFI
    #ifdef DEBUG_PRE_WIFI
        #define pout(x) Serial.print(x)
        #define poutln(x) Serial.println(x)
    #else
        #define pout(x) 
        #define poutln(x)
    #endif

#define DEBUG_WIFI
    #ifdef DEBUG_WIFI
        #define out(x) Telnet.print(x)
        #define outln(x) Telnet.println(x)
    #else
        #define pout(x) 
        #define poutln(x)
    #endif


#include "wifi_manager.h"
#include "telnet_server.h"
#include "camera_RTS.h"







#endif