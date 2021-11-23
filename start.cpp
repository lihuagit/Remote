#include "start.h"
#include "ui_start.h"
#include <qtoolbutton.h>
#include <QToolbutton>
#include"server/Mouse_act.h"
#include<iostream>

using namespace std;

tagpoint* savepoint1 = new tagpoint();
Server server;


start::start(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    Client = new Logon;
    Server = new Widget;

    setWindowFlags(Qt::FramelessWindowHint); //去窗口顶部边框
    
    this->setAttribute(Qt::WA_TranslucentBackground);   //隐藏widget透明


    //顶部三个按键得实现
    connect(ui.MinButton, &QToolButton::clicked, this, &QWidget::showMinimized);
    //    connect(ui->MaxButton,&QToolButton::clicked,this,&QWidget::showMaximized);
    connect(ui.CloseButton, &QToolButton::clicked, this, &QWidget::close);

    //client or server
    connect(ui.ClientButton, &QToolButton::clicked,this, &start::ToClient);
    connect(ui.ServerButton, &QToolButton::clicked, this,&start::ToServer);

    //子窗口关闭父窗口显示
    connect(Client, &Logon::exit, this, &start::show);
    connect(Server, &Widget::exit, this, &start::show);

}



void start::ToClient() {
    Client->show();
    this->hide();
}

void start::ToServer() {
    Server->show();
    //server->tcpconnect();
    if (WSAstartserver())
    {
        server.serverconnect();
        server.closeserver();
        WSACleanup();
    }
    this->hide();
}








//实现任意位置拖动窗口
void start::mousePressEvent(QMouseEvent* e)

{
    last = e->globalPos();

}

void start::mouseMoveEvent(QMouseEvent* e)

{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x() + dx, y() + dy);
}
void start::mouseReleaseEvent(QMouseEvent* e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x() + dx, y() + dy);
}
