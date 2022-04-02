#ifndef TELNET_H // This is so if it included in mulitple cpp files, the code will not be duplicated
#define TELNET_H

WebServer TelnetServer(23); // setup Telenet port
WiFiClient Telnet;

void telnetSetup(){
    TelnetServer.begin();
    TelnetServer.setNoDelay(true);
    out("Ready to use telent. Port 23 to connect:);");
    pout("Ready to use telent. Port 23 to connect:);");
}


void handleTelnet(){
  if (TelnetServer.hasClient()){ // client is connected
  pout("client is connected!");
    if (!TelnetServer || !Telnet.connected()) {
      if (Telnet) Telnet.stop(); // client disconnected
      Telnet = TelnetServer.available(); //ready for new client
      pout("ready for new client");

    } else{
      TelnetServer.available().stop(); // have client, block next
      pout("client connected");
    }

  }
}

#endif