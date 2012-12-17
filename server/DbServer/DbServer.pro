#-------------------------------------------------
#
# Project created by QtCreator 2012-11-29T00:36:36
#
#-------------------------------------------------

QT       += core
QT       += sql
QT       += network
QT       -= gui

TARGET = DbServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    db.cpp \
    net.cpp \
    core.cpp

HEADERS += \
    db.h \
    ../../Public.h \
    net.h \
    core.h
