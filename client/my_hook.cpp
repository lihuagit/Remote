#include "stdafx.h"
#include "my_hook.h"
#include"desk.h"
#include<cstring>
#include<string>
#define  _CRT_SECURE_NO_WARNINGS

extern tagpoint2* savepoint;
extern Client client;
extern HANDLE chMutex;


int MyHook::Messsages(SOCKET sclient) {
	//if (client.desk->isok)
		while (msg.message != WM_QUIT) { //while we do not close our application
			//if (!client.desk->isok)
				//continue;
			//if (!client.desk->isKong)
				//continue;
			//������һ����������
			WaitForSingleObject(chMutex, INFINITE);

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}

			/*if (!sendpos(sclient))
			{
				cout << "send error!" << endl;
				exit(0);
			}*/
			SetTimer(msg.hwnd, 1, 1, NULL);

			//�ͷŻ�������
			ReleaseMutex(chMutex);
		}
	UninstallHook(); //if we close, let's uninstall our hook
	//WSACleanup();
	return (int)msg.wParam; //return the messages
}
void MyHook::InstallHook(SOCKET sclient) {

	//WH_MOUSE_LL(14):�˹ҹ�ֻ����Windows NT�б���װ,�����Եײ����������¼����м���
	//WH_MOUSE_LL  �ػ�����ϵͳ������¼�
	//int idHook,    ���ӵ����ͣ������������Ϣ����
	//���˺���ִ�гɹ�,�򷵻�ֵ���Ǹùҹ�������̵ľ��;
	//���˺���ִ��ʧ��,�򷵻�ֵΪNULL(0).
	if (!(hook = SetWindowsHookEx(WH_MOUSE_LL, MyMouseCallback, NULL, 0))) {
		printf_s("Error: %x \n", GetLastError());
	}
	/*HHOOK WINAPI SetWindowsHookEx(

			   int idHook, \\��������

			   HOOKPROC lpfn, \\�ص�������ַ

			   HINSTANCE hMod, \\ʵ�����

			   DWORD dwThreadId); \\�߳�ID*/
			   //HINSTANCE hMod,  Ӧ�ó���ʵ���ľ������ʶ����lpfn��ָ���ӳ̵�DLL��
			   //Ӧ�ó�������ͨ������Windows API���һ�������֮������ Windows�����Ϳ���ʹ�øþ���������úͲ�����Ӧ���ں˶���
			   //�����Windowsϵͳ�ж����ʵ���ı�ʶ����Щ�������ģ�顢Ӧ�ó���ʵ�������ڡ����ơ�λͼ��GDI������Դ���ļ���
			   //���������ָ�������ÿգ����������û���κ����壬�������κ��ں˶��� 
			   //������dwThreadIdΪ0����ָʾ��һ���������̴������߳�֮��ʶ��
			   //�����lpfn����ָ��һ����̬�����еĹҹ��������.
			   //dwThreadId���Ϊ0�������ӳ������е��̹߳�������Ϊȫ�ֹ��ӡ�
			   //WH_KEYBOARD_LL(13):�˹ҹ�ֻ����Windows NT�б���װ,�����Եײ�ļ��������¼����м���.
	if (!(keyboardhook == SetWindowsHookEx(WH_KEYBOARD_LL, MyKeyBoardCallback, NULL, 0)))
	{
		printf_s("Error: %x \n", GetLastError());
	}
}
//����ֹһ��Ӧ�ó���֮ǰ,������ú���UnhookWindowsHookEx���ͷ���˹ҹ���ص�ϵͳ��Դ.
void MyHook::UninstallHook() {

	UnhookWindowsHookEx(hook);
	UnhookWindowsHookEx(keyboardhook);
}
//wParam�����������
LRESULT WINAPI MyMouseCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	client.desk->isok = true;
	MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam; // WH_MOUSE_LL struct

	if (nCode == 0) {
		if (pMouseStruct != NULL) {
			//clientconnect();
			//printf_s("Mouse Coordinates: x = %i | y = %i \n", pMouseStruct->pt.x, pMouseStruct->pt.y);
			//savepoint->x = pMouseStruct->pt.x;
			//savepoint->y = pMouseStruct->pt.y;
			savepoint->winx = client.desk->pixmap.width();
			savepoint->winy = client.desk->pixmap.height();
			point t = client.desk->change(pMouseStruct->pt.x, pMouseStruct->pt.y);

			savepoint->x = t.x;
			savepoint->y = t.y;
			//settagpoint(pMouseStruct->pt.x, pMouseStruct->pt.y);

		}

		switch (wParam) {
		case WM_LBUTTONUP: {
			//save->wParam = WM_LBUTTONUP;
			//printf_s("LEFT CLICK UP\n");
			strcpy_s(savepoint->info, "posinfo514");
			cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
			//client.desk->enterEvent(QEvent *);
			//sendpos(sclient, TCHAR2STRING((TCHAR)wParam));
			//settagpoint(WM_LBUTTONUP);
		}break;
		case WM_LBUTTONDOWN: {
			//save->wParam = WM_LBUTTONDOWN;
			//printf_s("LEFT CLICK DOWN\n");
			strcpy_s(savepoint->info, "posinfo513");
			cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
			//sendpos(sclient, TCHAR2STRING((TCHAR)wParam));
		}break;
		case WM_RBUTTONUP: {
			//save->wParam = WM_RBUTTONUP;
			//printf_s("RIGHT CLICK UP\n");
			strcpy_s(savepoint->info, "posinfo517");
			cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
			//sendpos(sclient, TCHAR2STRING((TCHAR)wParam));
			//settagpoint(WM_RBUTTONUP);
		}break;
		case WM_RBUTTONDOWN: {
			//save->wParam = WM_RBUTTONDOWN;
			//printf_s("RIGHT CLICK DOWN\n");
			strcpy_s(savepoint->info, "posinfo516");
			cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
			//sendpos(sclient, TCHAR2STRING((TCHAR)wParam));
			//settagpoint(WM_RBUTTONDOWN);
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
		}break;
		case WM_MBUTTONDOWN: {
			//save->wParam = WM_RBUTTONDOWN;
			//printf_s("MIDDLE CLICK DOWN\n");
			strcpy_s(savepoint->info, "posinfo519");
			cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
			//sendpos(sclient, TCHAR2STRING((TCHAR)wParam));
			//settagpoint(WM_RBUTTONDOWN);
		}break;
		case WM_MBUTTONUP: {
			//save->wParam = WM_LBUTTONDOWN;
			//printf_s("MIDDLE CLICK UP\n");
			strcpy_s(savepoint->info, "posinfo520");
			cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
			//sendpos(sclient, TCHAR2STRING((TCHAR)wParam));
		}break;


		case WM_MOUSEWHEEL: {
			//cout << "����������" << endl;
			//sendpos(sclient, TCHAR2STRING((TCHAR)wParam));
			//settagpoint(WM_VSCROLL);
			strcpy_s(savepoint->info, "wheelinfo522");
			int n = (short)HIWORD(wParam);
			cout << n << endl;
			cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
		}break;
		default:
		{
			strcpy_s(savepoint->info, "posinfo");
			cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
		}break;


		}

	}

	return CallNextHookEx(MyHook::Instance().hook, nCode, wParam, lParam);
}

LRESULT WINAPI MyKeyBoardCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	client.desk->isok = true;
	MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam; // WH_MOUSE_LL struct
	KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;

	savepoint->winx = client.desk->pixmap.width();
	savepoint->winy = client.desk->pixmap.height();
	//printf_s("Mouse Coordinates: x = %i | y = %i \n", pMouseStruct->pt.x, pMouseStruct->pt.y);
	point t = client.desk->change(pMouseStruct->pt.x, pMouseStruct->pt.y);

	savepoint->x = t.x;
	savepoint->y = t.y;
	//savepoint->info = "keyboardinfo" + (char*)pKeyStruct->vkCode;
	string str;
	char keyboard[10];//char����
	//strncpy_s(keyboard, str.c_str(), str.length() + 1);
	char keyboardinfo[50];
	//strcpy_s(savepoint->info, strcat(keyboardinfo ,keyboard));
//cout << savepoint->x << "   " << savepoint->y << "   " << savepoint->info << endl;
/*if (!client.sendpos())
{
	cout << "send error!" << endl;
	exit(0);
}*/


	if (nCode == 0)
	{
		if (pKeyStruct)
		{


		}
		switch (wParam)
		{
		case WM_KEYDOWN: {
			str = std::to_string(pKeyStruct->vkCode);
			strncpy_s(keyboard, str.c_str(), str.length() + 1);//��StringתChar����
			strcpy_s(keyboardinfo, "keyboardinfodown");
			strcpy_s(savepoint->info, strcat(keyboardinfo, keyboard));
			printf_s("Virtual Key Code: %d \n", pKeyStruct->vkCode);
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
		}break;
		case WM_KEYUP: {
			str = std::to_string(pKeyStruct->vkCode);
			strncpy_s(keyboard, str.c_str(), str.length() + 1);//��StringתChar����
			strcpy_s(keyboardinfo, "keyboardinfoup");
			strcpy_s(savepoint->info, strcat(keyboardinfo, keyboard));
			printf_s("Virtual Key Code: %d \n", pKeyStruct->vkCode);
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}

		}break;
		case WM_SYSKEYDOWN: {
			str = std::to_string(pKeyStruct->vkCode);
			strncpy_s(keyboard, str.c_str(), str.length() + 1);//��StringתChar����
			strcpy_s(keyboardinfo, "keyboardinfodown");
			strcpy_s(savepoint->info, strcat(keyboardinfo, keyboard));
			printf_s("Virtual Key Code: %d \n", pKeyStruct->vkCode);
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}
		}break;
		case WM_SYSKEYUP: {
			str = std::to_string(pKeyStruct->vkCode);
			strncpy_s(keyboard, str.c_str(), str.length() + 1);//��StringתChar����
			strcpy_s(keyboardinfo, "keyboardinfoup");
			strcpy_s(savepoint->info, strcat(keyboardinfo, keyboard));
			printf_s("Virtual Key Code: %d \n", pKeyStruct->vkCode);
			if (!client.sendpos())
			{
				cout << "send error!" << endl;
				exit(0);
			}

		}break;
		}


	}
	return CallNextHookEx(MyHook::Instance().keyboardhook, nCode, wParam, lParam);
}

