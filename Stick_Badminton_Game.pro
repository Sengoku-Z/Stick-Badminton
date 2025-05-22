QT       += core gui
QT       += core gui multimedia # 加这个模块 播放音乐
CONFIG   += resources_big # 管理资源用的模块
QT       += core gui sql # 加入SQL模块
#QMAKE_CXXFLAGS += /Zm500
# 在 .pro 文件中添加以下行
LIBS += -luser32

#include(deployment.pri)  QT += qml quick quick-private


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ball.cpp \
    Inlog.cpp \
    Instruction.cpp \
    Menu.cpp \
    MyNet.cpp \
    Player_Left.cpp \
    Player_Right.cpp \
    Regis.cpp \
    main.cpp \
    Widget.cpp

HEADERS += \
    Ball.h \
    Inlog.h \
    Instruction.h \
    Menu.h \
    MyNet.h \
    Player_Left.h \
    Player_Right.h \
    Regis.h \
    Widget.h

FORMS += \
    Inlog.ui \
    Instruction.ui \
    Menu.ui \
    Regis.ui \
    Widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Left_Hit.qrc \
    Left_Start_Hit.qrc \
    Play_Left_Run_Right.qrc \
    Play_Right_Run_Left.qrc \
    Play_Right_Run_Right.qrc \
    Player_Left_Run_Left.qrc \
    Right_Hit.qrc \
    Right_Start_Hit.qrc \
    images.qrc \
    images2.qrc \
    musics.qrc
