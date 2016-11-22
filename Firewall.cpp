/* 
 * Firewall.h - Library for a basic firewall.
 * Joe McManus josephmc@alumni.cmu.edu
 * version 0.2 2016.11.21
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


// Check IP rules against a /24, /16 or /8.
int Firewall::checkFirewall(String clientIP, String allowNet) {
	//Get Location(index) 
	int clientFirst = clientIP.indexOf(".", 0);
	int clientSecond = clientIP.indexOf(".", clientFirst + 1);
	int clientThird = clientIP.indexOf(".", clientSecond + 1);
  
	int i=0;
	int subnet=0;


	//Count the occurances of . to figure out what we allow
 	while ( i <  allowNet.length() ) {
		if ( allowNet.substring(i,i+1) == "." ) {
			subnet++;
		}
		//Kill trailing .'s 
		if (i == allowNet.length()-1 and allowNet.substring(i,i+1) == "." ) {
			subnet--;
			allowNet=allowNet.substring(0,i);
	  	}
	  	i++;
	}

	//Split the client IP in to octets only keep what we need to match against FW rule
	String c1o = clientIP.substring(0, clientFirst); 
  	String clientSubnet = c1o;
	if ( subnet == 1 || subnet == 2 ) {
		String c2o = clientIP.substring(clientFirst + 1, clientSecond);
  		clientSubnet = clientSubnet + "." +  c2o;
  	}
	if ( subnet == 2 ) {
		String c3o = clientIP.substring(clientSecond + 1, clientThird);
  		clientSubnet = clientSubnet + "." +  c3o;
  	}
	//Troubleshooting
	//Serial.println("Firewall Allow: " + allowNet);
	//Serial.println("Client Subnet: " + clientSubnet);

	if ( clientSubnet != allowNet ) {
		//Troubleshooting
		//Serial.println("Blocking Client");
		return 1;
	} else {
		return 0;
	}
}
