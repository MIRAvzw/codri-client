#-------------------------------------------------
#
# Project created by QtCreator 2011-03-07T15:07:36
#
#-------------------------------------------------

QT       += core gui


include(../lib/log4qt/log4qt.pri)
INCLUDEPATH += ../lib/log4qt/

include(../lib/libqavahi/libqavahi.pri)
INCLUDEPATH += ../lib/libqavahi/

TARGET = client
TEMPLATE = app


SOURCES += main.cpp \
    servicepublisher.cpp \
    mainapplication.cpp

HEADERS  += \
    servicepublisher.h \
    mainapplication.h

FORMS    +=
