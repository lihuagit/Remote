#include "logon.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Logon logon;
    logon.show();
    return app.exec();
}
