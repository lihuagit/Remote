#include "tpcstream.h"
#include "ui_tpcstream.h"
#include <QDebug>

#pragma execution_character_set("utf-8")

TpcStream::TpcStream(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TpcStream)
{
    ui->setupUi(this);

    savepoint = new tagpoint();

    if (WSAStartup(sockVersion, &wsaData) != 0) {
        QMessageBox::warning(this,"错误！","网络连接异常！！！",QMessageBox::Ok);
        WSACleanup();
        isConnect=false;
    }
    else isConnect=true;

    slisten =new SOCKET ( socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) );

    if (*slisten == INVALID_SOCKET)
    {
        QMessageBox::warning(this,"错误！","网络连接异常！！！",QMessageBox::Ok);
        closesocket(*slisten);
        WSACleanup();
        isConnect=false;
    }
    else isConnect=true;

}

TpcStream::~TpcStream()
{
    delete ui;
}


void TpcStream::First(){
    Bind();
    Acpt();
}

void TpcStream::Bind(){
    sin.sin_family = AF_INET;
    sin.sin_port = htons(host);
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if( ::bind(*slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR ){
        QMessageBox::warning(this,"错误！","网络连接异常！！！",QMessageBox::Ok);
        closesocket(*slisten);
        WSACleanup();
        isConnect=false;
    }

}


void TpcStream::Acpt(){
    //开始监听
    if(isConnect){
        if (listen(*slisten, 5) == SOCKET_ERROR)
        {
            QMessageBox::warning(this,"错误！","listen连接失败！！！",QMessageBox::Ok);
            closesocket(*slisten);
            WSACleanup();
            isConnect=false;
            return;
        }
        else isConnect=true;

        sClient =new SOCKET;
        int nAddrlen = sizeof(remoteAddr);

        //应该有阻塞才对
        *sClient = accept( *slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
        if (*sClient == INVALID_SOCKET)
        {
            QMessageBox::warning(this,"错误！","连接失败！！！",QMessageBox::Ok);
            closesocket(*slisten);
            WSACleanup();
            isConnect=false;
            return;
        }
        else isConnect=true;
    }
    else{
        QMessageBox::warning(this,"错误！","连接失败！！！",QMessageBox::Ok);
        isConnect=false;
    }

    if(isConnect)
        QMessageBox::information(this,"提示！","连接成功！！！",QMessageBox::Ok);

}

int TpcStream::Send(char* data,int len){
    if(isConnect){
//        strcpy(Data,data);
        len=send(*sClient,data,len,0);
        return len;
    }
    else {
        QMessageBox::warning(this,"错误！","连接失败！！！",QMessageBox::Ok);
        closesocket(*slisten);
        WSACleanup();
        isConnect=false;
        return -1;
    }
}

QString TpcStream::GetIP(){
    return inet_ntoa(remoteAddr.sin_addr);
}


void TpcStream::SendPix(){
     screen=qApp->primaryScreen();
     pixmap=screen->grabWindow(0);
     QBuffer buf;
     pixmap.save(&buf,"jpg",60);

    char b[100];

    int senlen=send(*sClient,buf.data().data(),buf.size(),0);
    qDebug()<<"size:"<<senlen;
    recv(*sClient,b,100,0);

    if(strcmp(b,"stop")==0){
        emit stop();
//            send(*sClient,b,5,0);
        }
}



void TpcStream::serverconnect()
{
    while (true)
    {

        if (this->recpos())
        {

            Mouse_act m;
            m.savepoint = savepoint;
            m.mouse_act();
            Sleep(1);
        }
        else break;
    }




    //接收数据  
    /*
    int ret = recv(sClient, revData, 255, 0);
    if (ret > 0){
        revData[ret] = 0x00;
        printf(revData);
    }*/

}

bool TpcStream::recpos()
{

    if (recv(*sClient, (char*)savepoint, sizeof(tagpoint), 0))
    {
        //cout << savepoint->x << "   " << savepoint->y << "    " << savepoint->info << endl;
        return true;
    }

    //cout << "dd";
    return false;
    //system("pause");
}

void TpcStream::closeserver()
{
    char info[20] = "服务器断开";
    send(*sClient, info, strlen(info), 0);
    closesocket(*slisten);
}


