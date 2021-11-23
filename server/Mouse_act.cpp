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

void Mouse_act::mouse_act()//�����ַ�����info����Ϣ��ѡ��������
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
	//��û�н������λ�ú;���λ�õĹ�ϵ
	SetCursorPos(p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny);

	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, p.x* 65536/ savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	if (FindSubStr(savepoint1->info, (char*)"513"))//�������
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"514"))//���̧��
		mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"516"))//�Ҽ�����
		mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"517"))//�Ҽ�̧��
		mouse_event(MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"519"))//�м�����
		mouse_event(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else if (FindSubStr(savepoint1->info, (char*)"520"))//�м�̧��
		mouse_event(MOUSEEVENTF_MIDDLEUP | MOUSEEVENTF_ABSOLUTE, p.x * 65536 / savepoint1->screenx, p.y * 65536 / savepoint1->screeny, 0, 0);
	else
		;

}

void Mouse_act::keyboardact()
{

	if (FindSubStr(savepoint1->info, (char*)"down"))//��������
	{
		keyboard = SpiltSubStr(savepoint1->info, 16);
		keybd_event(keyboard, 0, 0, 0);
	}
	if (FindSubStr(savepoint1->info, (char*)"up"))//����̧��
	{
		keyboard = SpiltSubStr(savepoint1->info, 14);
		keybd_event(keyboard, 0, KEYEVENTF_KEYUP, 0);
	}

	//keybd_event(keyboard, 0, KEYEVENTF_KEYUP, 0);
}

void Mouse_act::wheelact()
{

	//if (FindSubStr(savepoint1->info, (char*) "wheelactup"))//������ǰ��
		//mouse_event(MOUSEEVENTF_WHEEL | MOUSEEVENTF_ABSOLUTE, 0, 0, 1, 0);
	//else if (FindSubStr(savepoint1->info, (char*)"wheelactdown"))//�����Ⱥ��
	int val = -120;
	mouse_event(MOUSEEVENTF_WHEEL | MOUSEEVENTF_ABSOLUTE, 0, 0, val, 0);
	//else;

}

//��Ѱ�ַ���t�Ƿ�������ַ���p
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

//����������Ϣ�����ذ���ASCII��
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




