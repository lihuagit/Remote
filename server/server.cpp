
#include"Mouse_act.h"
#include<QMessageBox>

extern Server server;
extern tagpoint* savepoint1;
HANDLE shMutex;

bool WSAstartserver()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)
        return false;
    return true;
}

DWORD WINAPI SFun(LPVOID lpParamter)

{
    while (true)
    {
        WaitForSingleObject(shMutex, INFINITE);
        if (server.recpos())
        {
            Mouse_act m;
            m.mouse_act();
            Sleep(1);
            ReleaseMutex(shMutex);
        }
        else break;
    }

    //pos(client.sclient);
    return 0L;//表示返回的是long型的0
}

/*void serverconnect()
{
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (slisten == INVALID_SOCKET)
    {
        printf("socket error !");
        exit(0);
    }

    //绑定IP和端口
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("bind error !");
    }

    //开始监听
    if (listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen error !");
        exit(0);
    }
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255];
    printf("等待客户端连接...\n");
    sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
    if (sClient == INVALID_SOCKET)
    {
        printf("accept error !");
        exit(0);
    }
    printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));


        int ret = recv(sClient, revData, 255, 0);
        if (ret > 0) {
            revData[ret] = 0x00;
            printf(revData);
            cout << endl;
        }


    closesocket(slisten);
}*/

void Server::serverconnect()
{
    slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (slisten == INVALID_SOCKET)
    {
        printf("socket error !");
        exit(0);
    }

    //绑定IP和端口  
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if (::bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("bind error !");
    }

    //开始监听  
    if (listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen error !");
        exit(0);
    }
    //sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255];
    printf("等待客户端连接...\n");
    sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
    if (sClient == INVALID_SOCKET)
    {
        printf("accept error !");
        exit(0);
    }
    printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));


    ////创建一个子线程
    //HANDLE hThread = CreateThread(NULL, 0, SFun, NULL, 0, NULL);
    //shMutex = CreateMutex(NULL, FALSE, NULL);
    ////关闭线程句柄
    //CloseHandle(hThread);

    while (1) {
        //传输图片
		//请求获得一个互斥量锁
        //WaitForSingleObject(shMutex, INFINITE);
        QScreen* screen = qApp->primaryScreen();
        QPixmap pixmap = screen->grabWindow(0);
        QBuffer buf;
        pixmap.save(&buf, "jpg", 60);

        char b[100];

        int senlen = send(sClient, buf.data().data(), buf.size(), 0);

        //recv(sClient, b, 100, 0);
        //释放互斥量锁
        //ReleaseMutex(shMutex);
    }




    //接收数据  
    /*
    int ret = recv(sClient, revData, 255, 0);
    if (ret > 0){
        revData[ret] = 0x00;
        printf(revData);
    }*/

}

bool Server::recpos()
{

    if (recv(sClient, (char*)savepoint1, sizeof(tagpoint), 0))
    {
        cout << savepoint1->x << "   " << savepoint1->y << "    " << savepoint1->info << endl;
        return true;
    }

    //cout << "dd";
    return false;
    //system("pause");
}

void Server::closeserver()
{
    send(sClient, info, strlen(info), 0);
    closesocket(slisten);
}


