#include "popup.h"
#include "ui_popup.h"

Popup::Popup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);

    //使窗口不可操作
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip); //去顶部
//    setAttribute(Qt::WA_DeleteOnClose);
    this->setAttribute(Qt::WA_TranslucentBackground);   //隐藏widget透明

    //获取可用桌面大小
    QDesktopWidget* pDesktopWidget = QApplication::desktop();
    QRect deskRect = QApplication::desktop()->availableGeometry();
    //resize会被label撑开
    setFixedSize(250,100);
    move(deskRect.width()-250,deskRect.height()-100);
//    move(nWidth-200,nHeight-125);
    QTimer* time=new QTimer;
    time->start(8000);
    connect( time,&QTimer::timeout,this,&QWidget::hide );
}

Popup::~Popup()
{
    delete ui;
}
