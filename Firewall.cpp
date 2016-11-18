/* 
 * Firewall.h - Library for a basic firewall.
 * Joe McManus josephmc@alumni.cmu.edu
 * version 0.1 2016.11.16
 * Copyright (C) 2016 Joe McManus
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. 
 */

#include "Arduino.h" 
#include "Firewall.h" 

Firewall::Firewall(){
}


int Firewall::checkFirewall(String clientIP, String allowNet) {
  //For now we just allow a /24
  //Get Location(index) and split allowNet
  int clientFirst = clientIP.indexOf(".", 0);
  int clientSecond = clientIP.indexOf(".", clientFirst + 1);
  int clientThird = clientIP.indexOf(".", clientSecond + 1);

  String c1o = clientIP.substring(0, clientFirst); //client first octet
  String c2o = clientIP.substring(clientFirst + 1, clientSecond);
  String c3o = clientIP.substring(clientSecond + 1, clientThird);
  String clientSubnet = c1o + "." +  c2o + "." +  c3o;
  //Serial.println("Firewall Allow: " + allowNet);
  //Serial.println("Client Subnet: " + clientSubnet);
  if ( clientSubnet != allowNet ) {
    Serial.println("Blocking Client");
    return 1;
  } else {
    return 0;
  }
}
