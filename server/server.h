#pragma once

#pragma once
#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

//#define WM_MOUSEWHEEL 0x020A（编译通过）
#define    WIN32_LEAN_AND_MEAN  
#include<stdio.h>
#include<Windows.h>
#include<WinSock2.h>
#include<iostream>
#include<QBuffer>
#include<QScreen>
#include<QPixmap>
#include<qapplication.h>
#include"Mouse_act.h"

using namespace std;

#pragma comment(lib,"ws2_32.lib")
bool WSAstartserver();
class Server
{
public:
	SOCKET slisten;
	SOCKET sClient;
	char info[20] = "服务器断开";
	void serverconnect();
	bool recpos();
	void closeserver();
};
//void serverconnect();
