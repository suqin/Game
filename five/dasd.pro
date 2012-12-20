#-------------------------------------------------
#
# Project created by QtCreator 2012-10-22T18:53:34
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = dasd
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    core.cpp \
    net.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    core.h \
    net.h \
    player.h \
    ../Public.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    img.qrc
