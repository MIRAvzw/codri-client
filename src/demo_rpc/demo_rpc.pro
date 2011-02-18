
TARGET=demo_rpc

include(../../lib/qtxmlrpc/server/server.pri)

QT += 

SOURCES += main.cpp \
	server.cpp

HEADERS += \
	server.h

