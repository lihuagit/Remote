#include "myqlabel.h"
#include <QMouseEvent>
#include <QDebug>

MyQLabel::MyQLabel(QWidget* parent)
    : QLabel(parent)
{

}


void MyQLabel::enterEvent(QEvent* event)
{
    emit enter();
    //    qDebug()<<"鼠标进入了";
    this->setPixmap(QPixmap(":/picture/kongjian5.png"));
}
