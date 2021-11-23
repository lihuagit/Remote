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
			//请求获得一个互斥量锁
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

			//释放互斥量锁
			ReleaseMutex(chMutex);
		}
	UninstallHook(); //if we close, let's uninstall our hook
	//WSACleanup();
	return (int)msg.wParam; //return the messages
}
void MyHook::InstallHook(SOCKET sclient) {

	//WH_MOUSE_LL(14):此挂钩只能在Windows NT中被安装,用来对底层的鼠标输入事件进行监视
	//WH_MOUSE_LL  截获整个系统的鼠标事件
	//int idHook,    钩子的类型，即它处理的消息类型
	//若此函数执行成功,则返回值就是该挂钩处理过程的句柄;
	//若此函数执行失败,则返回值为NULL(0).
	if (!(hook = SetWindowsHookEx(WH_MOUSE_LL, MyMouseCallback, NULL, 0))) {
		printf_s("Error: %x \n", GetLastError());
	}
	/*HHOOK WINAPI SetWindowsHookEx(

			   int idHook, \\钩子类型

			   HOOKPROC lpfn, \\回调函数地址

			   HINSTANCE hMod, \\实例句柄

			   DWORD dwThreadId); \\线程ID*/
			   //HINSTANCE hMod,  应用程序实例的句柄。标识包含lpfn所指的子程的DLL。
			   //应用程序总是通过调用Windows API获得一个句柄，之后其他 Windows函数就可以使用该句柄，以引用和操作相应的内核对象。
			   //句柄是Windows系统中对象或实例的标识，这些对象包括模块、应用程序实例、窗口、控制、位图、GDI对象、资源、文件等
			   //句柄可以像指针那样置空，那样句柄就没有任何意义，不代表任何内核对象 
			   //若参数dwThreadId为0或者指示了一个其他进程创建的线程之标识符
			   //则参数lpfn必须指向一个动态链接中的挂钩处理过程.
			   //dwThreadId如果为0，钩子子程与所有的线程关联，即为全局钩子。
			   //WH_KEYBOARD_LL(13):此挂钩只能在Windows NT中被安装,用来对底层的键盘输入事件进行监视.
	if (!(keyboardhook == SetWindowsHookEx(WH_KEYBOARD_LL, MyKeyBoardCallback, NULL, 0)))
	{
		printf_s("Error: %x \n", GetLastError());
	}
}
//在终止一个应用程序之前,必须调用函数UnhookWindowsHookEx以释放与此挂钩相关的系统资源.
void MyHook::UninstallHook() {

	UnhookWindowsHookEx(hook);
	UnhookWindowsHookEx(keyboardhook);
}
//wParam是虚拟键代码
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
			//cout << "滚动条运行" << endl;
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
	char keyboard[10];//char数组
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
			strncpy_s(keyboard, str.c_str(), str.length() + 1);//将String转Char数组
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
			strncpy_s(keyboard, str.c_str(), str.length() + 1);//将String转Char数组
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
			strncpy_s(keyboard, str.c_str(), str.length() + 1);//将String转Char数组
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
			strncpy_s(keyboard, str.c_str(), str.length() + 1);//将String转Char数组
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

