#-------------------------------------------------
#
# Project created by QtCreator 2011-03-07T15:07:36
#
#-------------------------------------------------

QT       += core gui


include(../lib/log4qt/Log4Qt.pro)
INCLUDEPATH += ../lib/log4qt/src

include(../lib/libqavahi/libqavahi.pri)
INCLUDEPATH += ../lib/libqavahi/

include(../lib/qtxmlrpc/server/server.pri)
INCLUDEPATH += ../lib/qtxmlrpc/server/src

TARGET = client
TEMPLATE = app


SOURCES += main.cpp \
    servicepublisher.cpp \
    mainapplication.cpp \
    applicationinterface.cpp \
    logfacility.cpp

HEADERS  += \
    servicepublisher.h \
    mainapplication.h \
    logfacility.h \
    logstream.h \
    applicationinterface.h

FORMS    +=
