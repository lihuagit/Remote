#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class MyQLabel : public QLabel
{
    Q_OBJECT

public:
    MyQLabel(QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *event) override;

signals:
    void enter();


};
#endif // WIDGET_H

