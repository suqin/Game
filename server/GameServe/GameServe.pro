#-------------------------------------------------
#
# Project created by QtCreator 2012-11-26T14:47:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += network
TARGET = GameServe
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    serverlistener.cpp \
    ../../packagereader.cpp \
    ../../userlist.cpp

HEADERS += \
    serverlistener.h \
    ../../packagereader.h \
    ../../Public.h \
    ../../userlist.h
