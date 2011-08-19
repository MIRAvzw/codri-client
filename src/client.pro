# -------------------------------------------------
# Project created by QtCreator 2011-03-07T15:07:36
# -------------------------------------------------
QT += core \
    gui \
    webkit \
    xml \
    network
CONFIG += link_pkgconfig
PKGCONFIG += apr-1
INCLUDEPATH += /usr/include/svnqt
INCLUDEPATH += /usr/include/subversion-1
LIBS += -lsvnqt
INCLUDEPATH += /usr/include/Log4Qt
LIBS += -lLog4Qt
CONFIG += brisa \
    qxt
QXT += core \
    web
BRISA += core \
    upnp \
    utils
INCLUDEPATH += /usr/include/BRisa
LIBS += -lBrisaCore \
    -lBrisaUpnp \
    -lBrisaUtils
TARGET = client
TEMPLATE = app
RESOURCES += userinterface/webpage.qrc \
    networkinterface/descriptions.qrc
SOURCES += controller.cpp \
    datamanager.cpp \
    main.cpp \
    mainapplication.cpp \
    networkinterface/devices/kioskdevice.cpp \
    networkinterface/services/applicationservice.cpp \
    networkinterface/services/deviceservice.cpp \
    networkinterface.cpp \
    userinterface/webpage.cpp \
    userinterface/webpages/logpage.cpp \
    userinterface/webpages/mediapage.cpp \
    userinterface/webpages/statuspage.cpp \
    userinterface.cpp \
    userinterface/webpages/initpage.cpp \
    userinterface/webpages/errorpage.cpp
HEADERS += controller.h \
    datamanager.h \
    mainapplication.h \
    networkinterface/devices/kioskdevice.h \
    networkinterface/services/applicationservice.h \
    networkinterface/services/deviceservice.h \
    networkinterface.h \
    qexception.h \
    userinterface/webpage.h \
    userinterface/webpages/logpage.h \
    userinterface/webpages/mediapage.h \
    userinterface/webpages/statuspage.h \
    userinterface.h \
    userinterface/webpages/initpage.h \
    userinterface/webpages/errorpage.h
OTHER_FILES += networkinterface/descriptions/device_scpd.xml \
    networkinterface/descriptions/application_scpd.xml \
    userinterface/webpages/logpage.html \
    userinterface/webpages/statuspage.html \
    userinterface/webpages/initpage.html \
    userinterface/webpages/errorpage.html
