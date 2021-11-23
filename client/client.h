#pragma once
#include<WinSock2.h>
#include<stdio.h>
#include<iostream>
#include<cstring>
//#include"testip.h"
#include <WS2tcpip.h>
#include <stdint.h>
//#include"my_hook.h"
#include "desk.h"
#include <QByteArray>
#include <QObject>


using namespace std;

#pragma comment(lib,"ws2_32.lib")


bool WSAstartclient();
//void clientconnect();
//bool sendpos(SOCKET sclient);

class Client : public QObject
{
		Q_OBJECT
public:
	SOCKET sclient;
	char info[20];
	char ip[20];
	void clientconnect();
	bool sendpos();
	bool recinfo();
	void closeclient();
	void GetPixData();
	Desk* desk;
	char buf[300000];

};



