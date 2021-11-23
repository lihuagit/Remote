#ifndef MYWIDGE_H
#define MYWIDGE_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>

class MyWidge : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidge(QWidget *parent = nullptr);




protected:

    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void leave();

};

#endif // MYWIDGE_H
