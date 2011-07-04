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
BRISA += core upnp utils
INCLUDEPATH += /usr/include/BRisa
LIBS += -lBrisaCore -lBrisaUpnp -lBrisaUtils

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
    repository.cpp \
    networkinterface/services/deviceservice.cpp \
    networkinterface/services/applicationservice.cpp

HEADERS  += \
    mainapplication.h \
    qexception.h \
    userinterface.h \
    userinterface/webpage.h \
    userinterface/webpages/debugpage.h \
    userinterface/webpages/initpage.h \
    networkinterface.h \
    networkinterface/devices/kioskdevice.h \
    repository.h \
    networkinterface/services/deviceservice.h \
    networkinterface/services/applicationservice.h

OTHER_FILES += \
    networkinterface/descriptions/device_scpd.xml \
    networkinterface/descriptions/application_scpd.xml \
    userinterface/webpages/initpage.html
