#ifndef DESK_H
#define DESK_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QBuffer>
#include <QByteArray>
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QDir>
#include "../filestream.h"
#include <QDebug>
#include <QDesktopWidget> 
#include <QPoint>


namespace Ui {
class Desk;
}

struct point {
    int x;
    int y;
};


class Desk : public QWidget
{
    Q_OBJECT

public:
    explicit Desk(QWidget *parent = nullptr);
    ~Desk();

    void ConnectStop();
    void ConnecrStart();


    QTimer* time;
    QByteArray pixData;
    QPixmap pixmap;
    bool isok;
    int realWidth;
    int realHeight;
    int deskheight;
    int deskwidth;

    point change(int x, int y);

    void getdesksize();
    void enterEvent(QEvent* event)
    {
        isok = true;
    }
    void leaveEvent(QEvent* event)
    {
        isok = false;
    }
    bool isKong = 0;

private:
    Ui::Desk *ui;




private:
    FileStream* filestream;//文件类 处理文件传输用
    QFile pixfile;
    QString IPaddre;
   



private:
    void closeEvent (QCloseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void exit();
    void Getpixed();


};

#endif // DESK_H
