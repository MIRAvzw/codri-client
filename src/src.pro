# -------------------------------------------------
# Project created by QtCreator 2011-03-07T15:07:36
# -------------------------------------------------

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


#
# Configuration
#

TARGET = aa3client
TEMPLATE = app

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
    networkinterface/resources/applicationresource.cpp \
    networkinterface/jsonresource.cpp \
    networkinterface/resource.cpp
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
    networkinterface/resources/applicationresource.h \
    networkinterface/jsonresource.h
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
















