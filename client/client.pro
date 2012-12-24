#-------------------------------------------------
#
# Project created by QtCreator 2012-11-26T18:04:01
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcp.cpp \
    ../userlist.cpp

HEADERS  += mainwindow.h \
    ../Public.h \
    tcp.h \
    ../userlist.h

FORMS    += mainwindow.ui

RESOURCES += \
    img.qrc
