TEMPLATE = app
QT += core network xml

# Herqq
INCLUDEPATH += lib/herqq/hupnp/include
LIBS += -L"lib/herqq/hupnp/bin" -lHUpnp \
        -L"lib/herqq/hupnp/lib/qtsoap-2.7-opensource/lib" \
        -lQtSolutions_SOAP-2.7
QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
QMAKE_POST_LINK += cp -Rf lib/herqq/hupnp/bin/* bin

OBJECTS_DIR = obj
MOC_DIR = obj
DESTDIR = ./bin

SOURCES += \
    main.cpp \
    kiosk.cpp \
    kioskcreator.cpp \
    mainapplication.cpp

HEADERS += \
    kiosk.h \
    kioskcreator.h \
    mainapplication.h
