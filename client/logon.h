#ifndef LOGON_H
#define LOGON_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QString>
#include <string>
#include "desk.h"
#include "popup.h"
#include <QTimer>
using namespace std;

namespace Ui {
class Logon;
}


class Logon : public QWidget
{
    Q_OBJECT
public:
    explicit Logon(QWidget *parent = nullptr);
    ~Logon();

    //对外接口
public:
    string GetIp();
    QString GetIP() { return IP; }

private slots:

    void DeskShow();
    bool isConnect();

    void on_StartButton_clicked();

private:
    Ui::Logon *ui;
    QString IP;
    Popup *popup;
    Desk *desk;
    QTimer *time;
    QPoint last;

signals:
    void exit();

private:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


};

#endif // LOGON_H
