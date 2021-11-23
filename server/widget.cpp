#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置窗口透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->ui->NameLabel->setAttribute(Qt::WA_TranslucentBackground);

     //去掉边框 | 隐藏任务栏图标 | 位于最顶层
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool |Qt::WindowStaysOnTopHint );

    //获取屏幕宽高 将窗口置于桌面右下角
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    deskRect =new QRect( QApplication::desktop()->availableGeometry() );
    this->move(deskRect->width()-200,deskRect->height()-100);

    //使窗口五秒后隐藏
    time=new QTimer;
    time->start(5000);
    connect(time,&QTimer::timeout,this,&Widget::Hide);

    //鼠标进入控件则展开控件
    connect(ui->label,&MyLabel::enter,this,&Widget::eject);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::tcpconnect() {
    //Tpc = new TpcStream;
    //Tpc->First();
    //time2 = new QTimer;
    //time2->start(1);
    //connect(time2, &QTimer::timeout, Tpc, &TpcStream::SendPix);
    //Tpc->serverconnect();
}


void Widget::on_StopBut_clicked()
{
    emit exit();
    this->close();
}

//鼠标离开则缩回控件
void Widget::leaveEvent(QEvent *event){
    this->move(deskRect->width()-30,deskRect->height()-100);
    ui->label->setPixmap(QPixmap(":/picture/left.png"));
}


void Widget::eject(){
    this->move(deskRect->width()-200,deskRect->height()-100);
    ui->label->setPixmap(QPixmap(":/picture/right.png"));
}

void Widget::Hide(){
    this->move(deskRect->width()-30,deskRect->height()-100);
    ui->label->setPixmap(QPixmap(":/picture/left.png"));
    time->stop();
}