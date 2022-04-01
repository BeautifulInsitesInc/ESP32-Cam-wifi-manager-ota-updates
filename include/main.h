#ifndef MAIN_H
#define MAIN_H

#define DEBUG
#ifdef DEBUG
    #define out(x) Serial.print(x)
    #define outln(x) Serial.println(x)
#else
    #define out(x) 
    #define outln(x)
#endif

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <WiFiMulti.h>




#endif