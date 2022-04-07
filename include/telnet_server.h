#ifndef TELNET_H // This is so if it included in mulitple cpp files, the code will not be duplicated
#define TELNET_H

// include this file in the main.cpp
WiFiServer TelnetServer(23); // setup Telenet port
WiFiClient Telnet;

// Call this fuction in the main Setup fuction
void telnetSetup(){
    TelnetServer.begin();
    TelnetServer.setNoDelay(true);
    toutln("Ready to use telent. Port 23 to connect:);");
    outln("Ready to use telent. Port 23 to connect:);");
}


void telnetLoop(){// Handle Telnet - put on main loop
  if (TelnetServer.hasClient()){ // client is connected
  out("client is connected!");
    if (!TelnetServer || !Telnet.connected()) {
      if (Telnet) Telnet.stop(); // client disconnected
      Telnet = TelnetServer.available(); //ready for new client
      out("ready for new client");

    } else{
      TelnetServer.available().stop(); // have client, block next
      out("client connected");
    }

  }
}

#endif