// Copyright © 2020  Philip Lindh 
// All rights reserved

#include "config.h"
#include "Application.h"

#include "HardwareSpecs.h"

#include <stdio.h> 
#include <iostream>

using namespace std;

bool isInteger(const string& s)
{
   if(s.empty() || !isdigit(s[0]))
   	return false;

   char * p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}

int main(int argc, char** argv) 
{
	
}
