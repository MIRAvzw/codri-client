#-------------------------------------------------
#
# Project created by QtCreator 2011-03-08T10:35:09
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = demo_log4qt
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
include(../../lib/log4qt/log4qt.pri)
INCLUDEPATH += ../../lib/log4qt/

SOURCES += main.cpp \
    sampleapplication.cpp

HEADERS += \
    sampleapplication.h
