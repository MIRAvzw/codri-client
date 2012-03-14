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

RESOURCES += user/webpage.qrc
SOURCES += controller.cpp \
    main.cpp \
    mainapplication.cpp \
    networkinterface.cpp \
    user/webpage.cpp \
    user/webpages/logpage.cpp \
    user/webpages/statuspage.cpp \
    userinterface.cpp \
    user/webpages/initpage.cpp \
    user/webpages/errorpage.cpp \
    user/webpages/presentationpage.cpp \
    network/webservicedispatcher.cpp \
    network/jsonresource.cpp \
    network/resource.cpp \
    network/resources/configurationresource.cpp \
    network/resources/kioskresource.cpp \
    state/presentation.cpp \
    state/kiosk.cpp \
    state/configuration.cpp \
    network/resources/presentationresource.cpp \
    network/serverclient.cpp \
    controller/initcontroller.cpp \
    network/registrationcontroller.cpp \
    platforminterface.cpp \
    repositoryinterface.cpp
HEADERS += controller.h \
    mainapplication.h \
    networkinterface.h \
    qexception.h \
    user/webpage.h \
    user/webpages/logpage.h \
    user/webpages/statuspage.h \
    userinterface.h \
    user/webpages/initpage.h \
    user/webpages/errorpage.h \
    user/webpages/presentationpage.h \
    network/resource.h \
    network/webservicedispatcher.h \
    network/jsonresource.h \
    network/resources/configurationresource.h \
    network/resources/kioskresource.h \
    state/presentation.h \
    state/kiosk.h \
    state/configuration.h \
    network/resources/presentationresource.h \
    network/serverclient.h \
    controller/initcontroller.h \
    network/registrationcontroller.h \
    platforminterface.h \
    repositoryinterface.h \
    auxiliary/parameterizedsignaltransition.h \
    auxiliary/comparingsignaltransition.h
OTHER_FILES += \
    user/webpages/logpage.html \
    user/webpages/statuspage.html \
    user/webpages/initpage.html \
    user/webpages/errorpage.html

isEmpty(PREFIX) {
  PREFIX = /usr
}
BINDIR = $$PREFIX/bin
DATADIR =$$PREFIX/share
INSTALLS += target
target.path =$$BINDIR

# Check target
CHECK_FILTERS += \
    -readability/todo \
    -whitespace/line_length
# TODO: fix braces instead of disabling
check.target = check
check.commands = cd $$PWD && ../tools/cpplint.py --filter=$$join(CHECK_FILTERS,",","","") $$HEADERS $$SOURCES
check.depends =
QMAKE_EXTRA_TARGETS += check
