#pragma once
/*#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif*/

#include <stdio.h>
#include <tchar.h>


#include<iostream>
//#include <winnt.h>
//#include <wtypes.h>
#include"server/server.h"
using namespace std;

typedef struct tagpoint
{
	LONG x;
	LONG y;
	char info[20];
	int screenx ;
	int screeny ;
	int winx;
	int winy;

};