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

#ifndef Firewall_h
#define Firewall_h

#include "Arduino.h"

class Firewall
{
	public:
		Firewall();
		int checkFirewall(String clientIP, String allowNet);
};

#endif

