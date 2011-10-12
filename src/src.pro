# -------------------------------------------------
# Project created by QtCreator 2011-03-07T15:07:36
# -------------------------------------------------

QT += core \
    gui \
    webkit \
    network \
    xml
CONFIG += link_pkgconfig
PKGCONFIG += apr-1
INCLUDEPATH += /usr/include/svnqt
INCLUDEPATH += /usr/include/subversion-1
LIBS += -lsvnqt
INCLUDEPATH += /usr/include/Log4Qt
LIBS += -lLog4Qt
CONFIG += brisa
BRISA += core \
    upnp \
    utils
INCLUDEPATH += /usr/include/BRisa
LIBS += -lBrisaCore \
    -lBrisaUpnp \
    -lBrisaUtils
TARGET = aa3client
TEMPLATE = app

RESOURCES += userinterface/webpage.qrc \
    networkinterface/descriptions.qrc
SOURCES += controller.cpp \
    datamanager.cpp \
    main.cpp \
    mainapplication.cpp \
    networkinterface/devices/kioskdevice.cpp \
    networkinterface.cpp \
    userinterface/webpage.cpp \
    userinterface/webpages/logpage.cpp \
    userinterface/webpages/statuspage.cpp \
    userinterface.cpp \
    userinterface/webpages/initpage.cpp \
    userinterface/webpages/errorpage.cpp \
    networkinterface/services/configurationservice.cpp \
    networkinterface/services/presentationservice.cpp \
    userinterface/webpages/presentationpage.cpp
HEADERS += controller.h \
    datamanager.h \
    mainapplication.h \
    networkinterface/devices/kioskdevice.h \
    networkinterface.h \
    qexception.h \
    userinterface/webpage.h \
    userinterface/webpages/logpage.h \
    userinterface/webpages/statuspage.h \
    userinterface.h \
    userinterface/webpages/initpage.h \
    userinterface/webpages/errorpage.h \
    networkinterface/services/configurationservice.h \
    networkinterface/services/presentationservice.h \
    userinterface/webpages/presentationpage.h
OTHER_FILES += \
    userinterface/webpages/logpage.html \
    userinterface/webpages/statuspage.html \
    userinterface/webpages/initpage.html \
    userinterface/webpages/errorpage.html \
    networkinterface/descriptions/configuration_scpd.xml \
    networkinterface/descriptions/presentation_scpd.xml

isEmpty(PREFIX) {
  PREFIX = /usr
}
BINDIR = $$PREFIX/bin
DATADIR =$$PREFIX/share
INSTALLS += target
target.path =$$BINDIR
















