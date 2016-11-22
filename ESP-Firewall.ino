
// Example Firewall for ESP8266
// This example firewall denies web traffic unless it is in a specific /24.
// Set the subnet to allow in the variable allowNet .
// This example will display the temperature from an TMP36 if authenticated.
//
// Joe McManus josephmc@alumni.cmu.edu
// version 0.2 2016.11.21
// Copyright (C) 2016 Joe McManus
//
// Kickstarted this by looking at the Sparkfun ESP8266 Thing Dev
// libraries. Thanks Sparkfun.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//See <http://www.gnu.org/licenses/>.

#include <ESP8266WiFi.h>
#include <Firewall.h>

//Set some statics
const char WiFiSSID[] = "yourSSID";
const char WiFiPSK[] = "yourPassphrase";
const int tempPin = A0;

//Set the subnet you will ALLOW traffic from. 
//Right now it just supports /24, /16 or /8 networks. 
//i.e. allowNet="192.168.1"  | allowNet="172.16" | allowNet="10" 
String allowNet = "192.168.1"; 

WiFiServer server(80);

//Instantiate the firewall
Firewall firewall;

void setup()
{
  Serial.begin(9600);
  connectWiFi();
  server.begin();
}

void connectWiFi()
{
  //From Sparkfun sample: https://goo.gl/ubHfDF
  Serial.println("Connecting to: " + String(WiFiSSID));
  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFiSSID, WiFiPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);

  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Check the firewall
  int firewallResponse = firewall.checkFirewall(client.remoteIP().toString(), allowNet);
  if ( firewallResponse == 0) {
    client.flush();

    // Send Reply
    String s = "HTTP/1.1 200 OK\r\n";
    s += "Content-Type: text/html\r\n\r\n";
    s += "<!DOCTYPE HTML>\r\n<html>\r\n";
    s += "<head> <title> ESP8266 Firewall Example </title> </head> \n";
    s += "<body> <center> <h2> ESP8266 Firewall Example </h2><br> ";
    s += "<b>Congratulations, you have passed the firewall. <br> </b>";
    s += "Current Temperature: ";
    s += ((analogRead(tempPin) / 1024.0) - 0.5 ) * 100 * 9 / 5 + 32 ;
    s += "<br>";
    s += "Your ClientIP is : ";
    s += String(client.remoteIP().toString());
    s += "</body></html>\n";

    client.print(s);
    delay(1);
  }
}
