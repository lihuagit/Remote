#ifndef MYLABEL_H
#define MYLABEL_H


#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class MyLabel: public QLabel
{
    Q_OBJECT
public:

public:
    MyLabel(QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *event) override;

signals:
    void enter();


};

#endif // MYLABEL_H
