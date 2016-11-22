# ESP8266-Firewall
-----

Overview
----
The ESP8266 is an amazing low cost device with embedded WiFi. I was unable to find a firewall for it so this is what I came up with. A simple firewall/access list. Limitations: this only allows for /24, /16 or /8 networks.  But really a /24 should be more than enough for an ESP8266. 

To import the libary simply go to Sketch -> Include Library -> Add .ZIP Library. 
Use 
----

In your sketch set the variable allowNet to the octets of the network you'd like to allow. Use one of the following format Use one of the following formats. 

    String allowNet = "192.168.1";
    String allowNet = "172.16";
    String allowNet = "10";


Then initialize the firewall object. 

    Firewall firewall;


In your main loop check to see if you passed the firewall. 

    int firewallResponse = firewall.checkFirewall(client.remoteIP().toString(), allowNet);
    if ( firewallResponse == 0) {


Sample
---
There is a sample file included called ESP-Firewall.ino that will demonstrate the use. 

![](https://raw.githubusercontent.com/joemcmanus/ESP8266-Firewall/master/screenshot.png)
