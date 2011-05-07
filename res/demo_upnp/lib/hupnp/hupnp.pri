INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include(lib/qtsoap/qtsoap.pri)

exists(options.pri) {
    include(options.pri)
}

INCLUDEPATH += $$PWD/include/

debug:DEFINES += DEBUG

SRC_LOC = $$PWD/src/utils

include (./src/utils/utils.pri)

SRC_LOC = $$PWD/src

include (src/http/http.pri)
include (src/ssdp/ssdp.pri)
include (src/socket/socket.pri)
include (src/general/general.pri)
include (src/devicemodel/devicemodel.pri)
include (src/dataelements/dataelements.pri)
include (src/devicehosting/devicehosting.pri)

includes.files += ./include/HUpnpCore/H*

