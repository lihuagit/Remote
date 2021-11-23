#include "desk.h"
#include "ui_desk.h"
#pragma execution_character_set("utf-8")


Desk::Desk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Desk)
{
    ui->setupUi(this);

    time=new QTimer;

    //connect(time,&QTimer::timeout,this,[=](){ update(); } );

    //实现顶部弹窗
    connect(ui->ToolLabel,&MyQLabel::enter,ui->ToolWidget,&MyWidge::show);
    connect(ui->ToolWidget,&MyWidge::leave,ui->ToolWidget,&QWidget::hide);
    connect(ui->ToolWidget,&MyWidge::leave,ui->ToolLabel,[=](){ ui->ToolLabel->setPixmap(QPixmap(":/picture/kongjian3.png")); } );
    ui->ToolWidget->hide();
    connect(ui->ControlBut, &QToolButton::clicked, this, [=]() { isKong = 1; });
    connect(ui->SeeBut, &QToolButton::clicked, this, [=]() { isKong = 0; });
    connect(this, &Desk::Getpixed, this, [=]() { update(); });
}

Desk::~Desk()
{
    delete ui;
}

void Desk::closeEvent (QCloseEvent *){
    emit exit();
    time->stop();
    this->close();
}
void Desk::paintEvent(QPaintEvent *){


    //if(pixData.isEmpty()) QMessageBox::warning(this, "llsd！", "pix paintering！！！", QMessageBox::Ok);
    QPainter painter(this);
    pixmap.loadFromData(pixData);
    pixmap = pixmap.scaled(realWidth,realHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    pixmap = pixmap.scaled(realWidth,realHeight, Qt::KeepAspectRatio, Qt::FastTransformation);
    painter.drawPixmap(0,0,pixmap);
    //pixData = NULL;
}

void Desk::resizeEvent(QResizeEvent *){
    realWidth=this->width();
    realHeight=this->height();
}
void Desk::getdesksize()//获取可用桌面大小
{
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    QRect deskRect = QApplication::desktop()->availableGeometry();
    //QDesktopWidget* desktopWidget = QApplication::desktop();
    //QDesktopWidget* desktopWidget = QApplication::desktop();

    //QRect deskRect = desktopWidget->availableGeometry();   //获取可用桌面大小

    deskheight = deskRect.width();
    deskwidth = deskRect.height();
}



point Desk::change(int x, int y) {
    QPoint map(x, y);
    map = mapFromGlobal(QPoint(map));
    point temp;
    temp.x = map.x();
    temp.y = map.y();
    return temp;
}