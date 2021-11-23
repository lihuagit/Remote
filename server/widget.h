#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRect>
#include <QDesktopWidget>
#include <QTimer>
#include <QDir>
#include <QMessageBox>
#include "mylabel.h"

#include "../tpcstream.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    void tcpconnect();

private slots:
    void on_StopBut_clicked();


private:
    Ui::Widget *ui;
    QRect* deskRect;
    QTimer *time;

private:
    void eject();
    void Hide();
    void leaveEvent(QEvent *event) override;


    QTimer* time2;
    TpcStream* Tpc;
    

signals:
    void exit();



};
#endif // WIDGET_H
