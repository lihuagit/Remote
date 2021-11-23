#pragma once

#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QPoint>
#include "ui_start.h"
#include "client\logon.h"
#include "server\widget.h"

class start : public QWidget
{
    Q_OBJECT

public:
    start(QWidget *parent = Q_NULLPTR);


private:
    QPoint last;
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    Logon* Client;
    Widget* Server;

    void ToClient();
    void ToServer();


private:
    Ui::startClass ui;
};
