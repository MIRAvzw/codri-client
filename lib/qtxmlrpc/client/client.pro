#
# Qxmlrpc Client
#
TEMPLATE = lib
CONFIG += staticlib
#CONFIG += dll
QT -= gui


#TODO: here in future replace
contains( CONFIG, dll ) {
    win32:DEFINES += QLOGGER_SHARED
}

include(client.pri)


CONFIG(debug, debug|release) {
    DESTDIR = ./lib
    TARGET = xmlrpcclientd
} else {
    DESTDIR = ./lib
    TARGET = xmlrpcclient
}

win32 {
    LIBS += -lsetupapi -luuid -ladvapi32
}
unix:!macx {
    LIBS += -ludev
}
