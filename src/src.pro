#
# Dependencies
#

# Core Qt
QT += core \
    network

# Qxt
CONFIG += qxt
QXT += web

# Subversion
CONFIG += link_pkgconfig
PKGCONFIG += apr-1
INCLUDEPATH += /usr/include/svnqt
INCLUDEPATH += /usr/include/subversion-1

# SvnQt
INCLUDEPATH += /usr/include/svnqt
LIBS += -lsvnqt

# Log4Qt
INCLUDEPATH += /usr/include/Log4Qt
LIBS += -lLog4Qt

# QJson
PKGCONFIG += QJson

# Alsa
PKGCONFIG += alsa


#
# Configuration
#

TARGET = codri-client
TEMPLATE = app
QMAKE_CXXFLAGS += -Wall \
    -Wextra
SOURCES += controller.cpp \
    main.cpp \
    mainapplication.cpp \
    networkinterface.cpp \
    userinterface.cpp \
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
    repositoryinterface.cpp \
    auxiliary/fileutils.cpp
HEADERS += controller.h \
    mainapplication.h \
    networkinterface.h \
    auxiliary/qexception.h \
    userinterface.h \
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
    auxiliary/comparingsignaltransition.h \
    auxiliary/fileutils.h
OTHER_FILES += ../share/initpage.html \
    ../share/errorpage.html
other_files.files = $$OTHER_FILES
isEmpty(PREFIX):PREFIX = /usr
BINDIR = $$PREFIX/bin
DATADIR = $$PREFIX/share/$$TARGET
DEFINES += DATADIR=$$DATADIR
INSTALLS += target \
    other_files
target.path = $$BINDIR
other_files.path = $$DATADIR

# Check target
CHECK_FILTERS += -readability/todo \
    -whitespace/line_length \
    -whitespace/labels \
    -runtime/references
check.target = check
check.commands = cd \
    $$PWD \
    && \
    ../tools/cpplint.py \
    --filter=$$join(CHECK_FILTERS,",","","") \
    $$HEADERS \
    $$SOURCES
check.depends = 
QMAKE_EXTRA_TARGETS += check
