#include "logon.h"
#include "ui_logon.h"
#include<iostream>
#include "my_hook.h"
#include<string>

using namespace std;
//tagpoint* savepoint ;
tagpoint2* savepoint = new tagpoint2();
Client client;

#pragma execution_character_set("utf-8")

Logon::Logon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logon)
{
    //创建好连接桌面、弹窗和ui
    ui->setupUi(this);
    desk=new Desk;
    popup=new Popup;
    time = new QTimer;

    setWindowFlags(Qt::FramelessWindowHint); //去窗口顶部边框

    this->setAttribute(Qt::WA_TranslucentBackground);   //隐藏widget透明

    ui->lineEdit->setStyleSheet("background:transparent;border-style:outset"); //输入框透明+隐藏线框
    ui->lineEdit->setPlaceholderText("请输入IP");  //设置占位符

    //将“发起连接”按钮与回车键绑定   目前键盘两个回车键只能绑定一个
//    ui->ConnectButton->setFocus();    //设置默认焦点
//    ui->StartButton->setShortcut(Qt::Key_Enter);  //设置快捷键为小键盘enter键
    ui->StartButton->setShortcut(Qt::Key_Return); //设置快捷键为键盘上的enter键

    //子窗口close 父窗口show
    connect(desk,&Desk::exit,this,&QWidget::show);

    //实现顶部按键
    connect(ui->MinButton,&QToolButton::clicked,this,&QWidget::showMinimized);
//    connect(ui->MaxButton,&QToolButton::clicked,this,&QWidget::showMaximized);
    connect(ui->closeButton, &QToolButton::clicked, this, [=]() { emit exit(); this->close(); });
    
    connect(time, &QTimer::timeout, this, [=]() {
            client.GetPixData();
            desk->update();
        }
    );
    //connect(&client, &Client::Getpixed, desk, &Desk::update);
}

Logon::~Logon()
{
    delete ui;
}


string Logon::GetIp(){
    return IP.toStdString();
}

void Logon::DeskShow(){
    desk->show();
    desk->setWindowTitle("IP : "+IP);
    //desk->time->start(33);

    popup->show();
    this->hide();

    strcpy(client.ip, IP.toStdString().data());

    client.desk = desk;

    if (WSAstartclient())
    {
        client.clientconnect();
       // this->time->start(33);
        //client.closeclient();
        //WSACleanup();
    }
    else
        QMessageBox::warning(this, "错误！", "error!", QMessageBox::Ok);
}


bool Logon::isConnect(){
    bool isOk=1;
    if(IP.isEmpty()){
        QMessageBox::warning(this,"错误！","请先输入IP!",QMessageBox::Ok);
        return false;
    }

    return isOk;

}

//点击发起连接开始链接
void Logon::on_StartButton_clicked()
{
    //检查IP
    IP=ui->lineEdit->text();
    if(isConnect()) DeskShow();

}



//实现任意位置拖动窗口
void Logon::mousePressEvent(QMouseEvent *e)

{
    last = e->globalPos();

}

void Logon::mouseMoveEvent(QMouseEvent *e)

{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    last = e->globalPos();
    move(x() + dx, y() + dy);
}
void Logon::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x() + dx, y() + dy);
}
