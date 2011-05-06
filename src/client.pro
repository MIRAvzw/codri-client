#-------------------------------------------------
#
# Project created by QtCreator 2011-03-07T15:07:36
#
#-------------------------------------------------

QT += core gui webkit xml network

INCLUDEPATH += /usr/include/Log4Qt
LIBS += -lLog4Qt

CONFIG += brisa qxt
QXT += core web
BRISA += upnp core utils
INCLUDEPATH += /usr/include/BRisa
LIBS += -lBrisaUpnp

TARGET = client
TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = obj
DESTDIR = ./bin

RESOURCES += userinterface/webpage.qrc \
    networkinterface/descriptions.qrc

SOURCES += main.cpp \
    mainapplication.cpp \
    userinterface.cpp \
    userinterface/webpage.cpp \
    userinterface/webpages/debugpage.cpp \
    userinterface/webpages/initpage.cpp \
    networkinterface.cpp \
    networkinterface/devices/kioskdevice.cpp \
    networkinterface/services/applicationservice.cpp \
    networkinterface/services/dataservice.cpp \
    repository.cpp

HEADERS  += \
    mainapplication.h \
    qexception.h \
    userinterface.h \
    userinterface/webpage.h \
    userinterface/webpages/debugpage.h \
    userinterface/webpages/initpage.h \
    networkinterface.h \
    networkinterface/devices/kioskdevice.h \
    networkinterface/services/applicationservice.h \
    networkinterface/services/dataservice.h \
    repository.h
