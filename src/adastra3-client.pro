#-------------------------------------------------
#
# Project created by QtCreator 2011-03-07T15:07:36
#
#-------------------------------------------------

QT += core gui webkit xml network

include(../lib/svnqt/src/svnqt.pri)
LIBS += -lsvn_client-1 -lsvn_wc-1 -lsvn_diff-1 -lsvn_fs-1 -lsvn_repos-1 -lsvn_ra-1 -lsvn_subr-1 -lapr-1 -laprutil-1

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
    networkinterface.cpp \
    networkinterface/devices/kioskdevice.cpp \
    networkinterface/services/deviceservice.cpp \
    networkinterface/services/applicationservice.cpp \
    userinterface/webpages/statuspage.cpp \
    userinterface/webpages/logpage.cpp \
    datamanager.cpp

HEADERS  += \
    mainapplication.h \
    qexception.h \
    userinterface.h \
    userinterface/webpage.h \
    networkinterface.h \
    networkinterface/devices/kioskdevice.h \
    networkinterface/services/deviceservice.h \
    networkinterface/services/applicationservice.h \
    userinterface/webpages/statuspage.h \
    userinterface/webpages/logpage.h \
    datamanager.h

OTHER_FILES += \
    networkinterface/descriptions/device_scpd.xml \
    networkinterface/descriptions/application_scpd.xml \
    userinterface/webpages/logpage.html \
    userinterface/webpages/statuspage.html
