include(../../lib/libqavahi/libqavahi.pri)
INCLUDEPATH += ../../lib/libqavahi/

TEMPLATE = app
TARGET = demo_mdns
HEADERS += \ 
    servicediscoverer.h
SOURCES += main.cpp \
    servicediscoverer.cpp
CONFIG += qt console
QT += gui
