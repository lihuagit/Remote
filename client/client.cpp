//#include"client.h"
using namespace std;
#include"my_hook.h"
extern tagpoint2* savepoint ;
#include<string>
#include "client.h"
#include <string>
#include<QMessageBox>
#include<QDebug>
#pragma execution_character_set("utf-8")

HANDLE chMutex;

extern Client client;

//������Ӧ�̺߳���
DWORD WINAPI Fun(LPVOID lpParamter)
{
	pos(client.sclient);
	return 0L;//��ʾ���ص���long�͵�0
}

//ͼ����ʾ�̺߳���
DWORD WINAPI Fun2(LPVOID lpParamter)
{
	while (true)
	{
		//������һ����������
		WaitForSingleObject(chMutex, INFINITE);

		client.GetPixData();
		emit client.desk->Getpixed();

		ReleaseMutex(chMutex);
	}
}

bool WSAstartclient()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;

	if (WSAStartup(sockVersion, &data) != 0)
	{
		cout << "��ʼ��ʧ�ܣ�" << endl;
		Sleep(500);
		return  false;

	}
	return true;
}


void Client::clientconnect()
{
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		cout << "invalid socket!" << endl;
		exit(0);
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);


	//cin >> ip;

	const char* IP;
	IP = ip;
	int ret1 = inet_pton(AF_INET, ip, &serAddr.sin_addr.s_addr);
	while (ret1 == 0 || errno == EAFNOSUPPORT) {
		cout << "������Ϸ���IP��ַ��" << endl;
		cin >> ip;
		IP = ip;
		ret1 = inet_pton(AF_INET, ip, &serAddr.sin_addr.s_addr);
	}
	inet_pton(AF_INET, IP, &serAddr.sin_addr.s_addr);
	if (::connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{  //����ʧ�� 
		QMessageBox::warning(desk, "����", "error!", QMessageBox::Ok);
		closesocket(sclient);
		exit(0);
	}

	//����һ�����߳�
	HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	chMutex = CreateMutex(NULL, FALSE, NULL);
	//�ر��߳̾��
	CloseHandle(hThread);


	////����һ�����߳�
	HANDLE hThread2 = CreateThread(NULL, 0, Fun2, NULL, 0, NULL);
	chMutex = CreateMutex(NULL, FALSE, NULL);
	////�ر��߳̾��
	CloseHandle(hThread2);

}


void Client::closeclient()
{
	if (recinfo())
	{
		Sleep(1000);
		closesocket(sclient);
	}

}
bool Client::sendpos()
{
	char temp[200];    //���͵��ַ���
	//struct person p1; //����һ����Ҫ���͵Ľṹ��
	memset(temp, 0, sizeof(temp));         // �Ը��ڴ�ν�����
	//memcpy(savepoint, 0, sizeof(savepoint));
	memcpy(temp,savepoint, sizeof(tagpoint2));     // ������ṹ���е���Ϣ���ڴ��ж��뵽�ַ���temp��
	//����������temp����ַ����Ϳ�����
	
	//cout << temp;
	send(sclient, temp, sizeof(tagpoint2), 0);
	//struct person p1; //����һ����Ҫ���͵Ľṹ��
	//p1.age = 10;
	//p1.high = 1.80f;
	//strcpy(p1.name, "zhangsan", sizeof(p1.name));

	//send(sclient, (char*)savepoint, sizeof(tagpoint), 0);
	return true;
}
/*bool sendpos(SOCKET sclient, string data)
{
	const char* sendData;
	sendData = data.c_str();
	send(sclient, sendData, strlen(sendData), 0);
	return true;
}*/
bool Client::recinfo()
{
	recv(sclient, info, 20, 0);
	cout << info << endl;
	return true;
}

void Client::GetPixData() {
	
	int revlen = recv(sclient, buf, sizeof(buf), 0);
	//QMessageBox::warning(desk, "xxx", "��ʼ", QMessageBox::Ok);
	//if (revlen > 0);
		desk->pixData.setRawData(buf, revlen);
		qDebug() << "size:" << revlen;
}