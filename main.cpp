#if _MSC_VER >= 1600  

#pragma execution_character_set("utf-8")  

#endif  

#include "start.h"
#include <QtWidgets/QApplication>
//#pragma execution_character_set("utf-8")

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    start start;
    start.show();
    return app.exec();
}