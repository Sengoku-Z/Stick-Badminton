QT       += core gui
QT       += core gui multimedia # 加这个模块 播放音乐
CONFIG   += resources_big # 管理资源用的模块
QT       += core gui sql # 加入SQL模块
QMAKE_CXXFLAGS += /Zm500

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ball.cpp \
    Inlog.cpp \
    MyNet.cpp \
    Player_Left.cpp \
    Player_Right.cpp \
    Regis.cpp \
    main.cpp \
    Widget.cpp

HEADERS += \
    Ball.h \
    Inlog.h \
    MyNet.h \
    Player_Left.h \
    Player_Right.h \
    Regis.h \
    Widget.h

FORMS += \
    Inlog.ui \
    Regis.ui \
    Widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    musics.qrc
