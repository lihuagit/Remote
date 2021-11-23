#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QDesktopWidget>
#include <QTimer>

namespace Ui {
class Popup;
}

class Popup : public QWidget
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = nullptr);
    ~Popup();




private:
    Ui::Popup *ui;
};

#endif // POPUP_H
