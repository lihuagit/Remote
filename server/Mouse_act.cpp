#include "Mouse_act.h"

extern tagpoint* savepoint1;

Mouse_act::Mouse_act()
{
	if (savepoint1->winx != 0 || savepoint1->winy != 0)
	{
		p.x = savepoint1->x * GetSystemMetrics(SM_CXSCREEN) / savepoint1->winx;
		p.y = savepoint1->y * GetSystemMetrics(SM_CYSCREEN) / savepoint1->winy;
		keyboard = 0;
	}
	
}

void Mouse_act::mouse_act()//解析字符数组info的信息，选择键鼠操作
{
	if (FindSubStr(savepoint1->info, (char*)"posinfo"))
		posact();
	else if (FindSubStr(savepoint1->info, (char*)"wheelinfo"))
		wheelact();
	else if (FindSubStr(savepoint1->info, (char*)"keyboardinfo"))
		keyboardact();
	else
		cout << "false";

}



void Mouse_act::posact()
{
	//还没有建立相对位置和绝对位置的关系
	SetCursorPos(p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny);

	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, p.x* 65536/ savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	if (FindSubStr(savepoint1->info, (char*)"513"))//左键按下
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"514"))//左键抬起
		mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"516"))//右键按下
		mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"517"))//右键抬起
		mouse_event(MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"519"))//中键按下
		mouse_event(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"520"))//中键抬起
		mouse_event(MOUSEEVENTF_MIDDLEUP | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else
		;

}

void Mouse_act::keyboardact()
{

	if (FindSubStr(savepoint1->info, (char*)"down"))//鼠标键按下
	{
		keyboard = SpiltSubStr(savepoint1->info, 16);
		keybd_event(keyboard, 0, 0, 0);
	}
	if (FindSubStr(savepoint1->info, (char*)"up"))//鼠标键抬起
	{
		keyboard = SpiltSubStr(savepoint1->info, 14);
		keybd_event(keyboard, 0, KEYEVENTF_KEYUP, 0);
	}

	//keybd_event(keyboard, 0, KEYEVENTF_KEYUP, 0);
}

void Mouse_act::wheelact()
{

	//if (FindSubStr(savepoint1->info, (char*) "wheelactup"))//滚轮向前滚
		//mouse_event(MOUSEEVENTF_WHEEL | MOUSEEVENTF_ABSOLUTE, 0, 0, 1, 0);
	//else if (FindSubStr(savepoint1->info, (char*)"wheelactdown"))//滚轮先后滚
	int val = -120;
	mouse_event(MOUSEEVENTF_WHEEL | MOUSEEVENTF_ABSOLUTE, 0, 0, val, 0);
	//else;

}

//搜寻字符串t是否存在子字符串p
bool FindSubStr(char* t, char* p)
{

	int i = 0, j = 0;
	while (p[i] != 0 && t[j] != 0)
	{
		if (p[i] == t[j])
		{
			i++;
			j++;

		}
		else {
			j = j - i + 1;
			i = 0;
		}
	}
	if (p[i] == 0)  return true;
	else return false;
}

//解析键盘信息，返回按键ASCII码
int SpiltSubStr(char* t, int n)
{
	int p = strlen(t) - n;
	cout << "p:" << p << endl;
	int keyboard = 0;
	int mul = 1;
	for (int i = p; i > 0; i--)
	{
		keyboard = ((int)t[n + i - 1] - 48) * mul + keyboard;
		mul *= 10;
	}

	return keyboard;
}




