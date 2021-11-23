#ifndef TPCSTREAM_H
#define TPCSTREAM_H

#include <QWidget>
#include<WinSock2.h>
#include<QMessageBox>
#include<QScreen>
#include<QPixmap>
#include<QBuffer>
#include<QByteArray>
#include<QDataStream>
#include<QByteArray>
#include<stdio.h>
#include<string.h>
#include "server/Mouse_act.h"
#include"receivepos.h"


#pragma comment(lib,"ws2_32.lib")

using namespace std;


namespace Ui {
class TpcStream;
}

class TpcStream : public QWidget
{
    Q_OBJECT

public:
    explicit TpcStream(QWidget *parent = nullptr);
    ~TpcStream();


public:
    bool isConnect=false;


    int Send(char* data,int len);
    QString GetIP();
    void First();
    void SendPix();
    void Acpt();


    void serverconnect();


private:
    void SetSockt();
    void Bind();

    bool recpos();
    void closeserver();

signals:
    void stop();


private:
    Ui::TpcStream *ui;

    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;

    SOCKET *slisten;
    SOCKET *sClient;

    int host=8888;

    sockaddr_in remoteAddr;
    sockaddr_in sin;
    char Data[1024];

    QPixmap pixmap;
    QScreen *screen;


    tagpoint* savepoint;

};

#endif // TPCSTREAM_H
