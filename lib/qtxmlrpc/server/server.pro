#
# Qxmlrpc Server
#
TEMPLATE = lib
CONFIG += staticlib
#CONFIG += dll
QT -= gui


#TODO: here in future replace
contains( CONFIG, dll ) {
    win32:DEFINES += QLOGGER_SHARED
}

include(server.pri)


CONFIG(debug, debug|release) {
    DESTDIR = ./lib
    TARGET = xmlrpcserverd
} else {
    DESTDIR = ./lib
    TARGET = xmlrpcserver
}

win32 {
    LIBS += -lsetupapi -luuid -ladvapi32
}
unix:!macx {
    LIBS += -ludev
}
