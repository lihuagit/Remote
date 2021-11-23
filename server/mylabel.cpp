#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{

}

void MyLabel::enterEvent(QEvent *event)
{
    emit enter();
//    qDebug()<<"鼠标进入了";
}
