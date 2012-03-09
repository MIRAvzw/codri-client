#
# Dependencies
#

# Core Qt
QT += core \
    gui \
    webkit \
    network \
    xml

# Qxt
CONFIG += qxt
QXT += core web

# SvnQt
CONFIG += link_pkgconfig
PKGCONFIG += apr-1
INCLUDEPATH += /usr/include/svnqt
INCLUDEPATH += /usr/include/subversion-1
LIBS += -lsvnqt

# Log4Qt
INCLUDEPATH += /usr/include/Log4Qt
LIBS += -lLog4Qt

# QJson
PKGCONFIG += QJson
LIBS += -lqjson


#
# Configuration
#

TARGET = codri-client
TEMPLATE = app
QMAKE_CXXFLAGS += -Wall -Wextra

RESOURCES += userinterface/webpage.qrc
SOURCES += controller.cpp \
    datamanager.cpp \
    main.cpp \
    mainapplication.cpp \
    networkinterface.cpp \
    userinterface/webpage.cpp \
    userinterface/webpages/logpage.cpp \
    userinterface/webpages/statuspage.cpp \
    userinterface.cpp \
    userinterface/webpages/initpage.cpp \
    userinterface/webpages/errorpage.cpp \
    userinterface/webpages/presentationpage.cpp \
    networkinterface/webservicedispatcher.cpp \
    networkinterface/jsonresource.cpp \
    networkinterface/resource.cpp \
    networkinterface/resources/configurationresource.cpp \
    networkinterface/resources/kioskresource.cpp \
    state/presentation.cpp \
    state/kiosk.cpp \
    state/configuration.cpp \
    networkinterface/resources/presentationresource.cpp \
    networkinterface/serverclient.cpp \
    controller/initcontroller.cpp \
    networkinterface/registrationcontroller.cpp
HEADERS += controller.h \
    datamanager.h \
    mainapplication.h \
    networkinterface.h \
    qexception.h \
    userinterface/webpage.h \
    userinterface/webpages/logpage.h \
    userinterface/webpages/statuspage.h \
    userinterface.h \
    userinterface/webpages/initpage.h \
    userinterface/webpages/errorpage.h \
    userinterface/webpages/presentationpage.h \
    networkinterface/resource.h \
    networkinterface/webservicedispatcher.h \
    networkinterface/jsonresource.h \
    networkinterface/resources/configurationresource.h \
    networkinterface/resources/kioskresource.h \
    state/presentation.h \
    state/kiosk.h \
    state/configuration.h \
    networkinterface/resources/presentationresource.h \
    networkinterface/serverclient.h \
    controller/initcontroller.h \
    networkinterface/registrationcontroller.h
OTHER_FILES += \
    userinterface/webpages/logpage.html \
    userinterface/webpages/statuspage.html \
    userinterface/webpages/initpage.html \
    userinterface/webpages/errorpage.html

isEmpty(PREFIX) {
  PREFIX = /usr
}
BINDIR = $$PREFIX/bin
DATADIR =$$PREFIX/share
INSTALLS += target
target.path =$$BINDIR
















