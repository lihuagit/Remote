QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    desk.cpp \
    filestream.cpp \
    logon.cpp \
    main.cpp \
    myqlabel.cpp \
    mywidge.cpp \
    popup.cpp

HEADERS += \
    desk.h \
    filestream.h \
    logon.h \
    myqlabel.h \
    mywidge.h \
    popup.h

FORMS += \
    desk.ui \
    logon.ui \
    popup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    picture.qrc


#LIBS += -lpthread libwsock32 libws2_32
