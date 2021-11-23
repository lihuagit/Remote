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

	Mouse_act();//构造函数
	//~Mouse_act();
	void mouse_act();//检测键鼠进行鼠标操作、键盘操作和滚轮操作
	void posact();//鼠标响应
	void keyboardact();//键盘响应
	void wheelact();//滚轮响应


	tagpoint* savepoint;


};
bool FindSubStr(char* t, char* p);
int SpiltSubStr(char* t,int n);
