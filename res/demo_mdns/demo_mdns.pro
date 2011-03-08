include(../../lib/libqavahi/libqavahi.pri)
INCLUDEPATH += ../../lib/libqavahi/

TEMPLATE = app
TARGET = demo_mdns
HEADERS += \  
    servicepublisher.h
SOURCES += main.cpp \
    servicepublisher.cpp
CONFIG += qt console
QT += gui
