#pragma once
//#include<iostream>
//#include "Windows.h"
#include<string>
#include "../receivepos.h"
#include<Windows.h>

using namespace std;


class Mouse_act
{
public:
	POINT p;
	int keyboard;

	Mouse_act();//���캯��
	//~Mouse_act();
	void mouse_act();//��������������������̲����͹��ֲ���
	void posact();//�����Ӧ
	void keyboardact();//������Ӧ
	void wheelact();//������Ӧ


	tagpoint* savepoint;


};
bool FindSubStr(char* t, char* p);
int SpiltSubStr(char* t,int n);
