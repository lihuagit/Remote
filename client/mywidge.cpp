#include "mywidge.h"

MyWidge::MyWidge(QWidget *parent) : QWidget(parent)
{

}


void MyWidge::leaveEvent(QEvent *){
    emit leave();
}
void MyWidge::paintEvent(QPaintEvent *){
        QPainter painter(this);
        QPixmap map(":/picture/kongjian4.png");
        map = map.scaled(500,60, Qt::IgnoreAspectRatio, Qt::FastTransformation);
        painter.drawPixmap(0,0,map);
}
