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
    //    qDebug()<<"��������";
    this->setPixmap(QPixmap(":/picture/kongjian5.png"));
}
