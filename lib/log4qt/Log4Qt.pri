INCLUDEPATH += $$PWD $$PWD/include/
DEPENDPATH += $$PWD

QT += core xml network

LOG4QT_VERSION_MAJOR = 1
LOG4QT_VERSION_MINOR = 0
LOG4QT_VERSION_RELEASE = 0

LOG4QT_VERSION = '\\"$${LOG4QT_VERSION_MAJOR}.$${LOG4QT_VERSION_MINOR}.$${LOG4QT_VERSION_RELEASE}\\"'
DEFINES += LOG4QT_VERSION_STR=\"$${LOG4QT_VERSION}\"
DEFINES += LOG4QT_VERSION=$${LOG4QT_VERSION}

VERSION = 1.0.0

DEPENDPATH += src src/helpers src/spisrc/ varia
INCLUDEPATH += src src/helpers src/spi src/varia


HEADERS += src/appender.h \
           src/appenderskeleton.h \
           src/basicconfigurator.h \
           src/colorconsoleappender.h \
           src/consoleappender.h \
           src/dailyrollingfileappender.h \
           src/asyncappender.h \
           src/mainthreadappender.h \
#          src/ databaseappender.h \
#          src/ databaselayout.h \
           src/fileappender.h \
           src/hierarchy.h \
           src/layout.h \
           src/level.h \
           src/log4qt.h \
           src/log4qtshared.h \
           src/logger.h \
           src/loggerrepository.h \
           src/loggingevent.h \
           src/logmanager.h \
           src/mdc.h \
           src/ndc.h \
           src/patternlayout.h \
           src/propertyconfigurator.h \
           src/rollingfileappender.h \
           src/signalappender.h \
           src/simplelayout.h \
           src/simpletimelayout.h \
           src/ttcclayout.h \
           src/telnetappender.h \
           src/writerappender.h \
           src/systemlogappender.h \
           src/helpers/classlogger.h \
           src//helpers/appenderattachable.h \
           src/helpers/configuratorhelper.h \
           src/helpers/datetime.h \
           src/helpers/factory.h \
           src/helpers/initialisationhelper.h \
           src/helpers/logerror.h \
           src/helpers/logobject.h \
           src/helpers/logobjectptr.h \
           src/helpers/optionconverter.h \
           src/helpers/patternformatter.h \
           src/helpers/properties.h \
           src/helpers/dispatcher.h \
           src/spi/filter.h \
           src/varia/debugappender.h \
           src/varia/denyallfilter.h \
           src/varia/levelmatchfilter.h \
           src/varia/levelrangefilter.h \
           src/varia/listappender.h \
           src/varia/nullappender.h \
           src/varia/stringmatchfilter.h \
           src/logstream.h

SOURCES += src/appenderskeleton.cpp \
           src/basicconfigurator.cpp \
           src/colorconsoleappender.cpp \
           src/consoleappender.cpp \
           src/dailyrollingfileappender.cpp \
           src/asyncappender.cpp \
           src/mainthreadappender.cpp \
#           src/databaseappender.cpp \
#           src/databaselayout.cpp \
           src/fileappender.cpp \
           src/hierarchy.cpp \
           src/layout.cpp \
           src/level.cpp \
           src/log4qt.cpp \
           src/logger.cpp \
           src/loggerrepository.cpp \
           src/loggingevent.cpp \
           src/logmanager.cpp \
           src/mdc.cpp \
           src/ndc.cpp \
           src/patternlayout.cpp \
           src/propertyconfigurator.cpp \
           src/rollingfileappender.cpp \
           src/signalappender.cpp \
           src/simplelayout.cpp \
           src/simpletimelayout.cpp \
           src/ttcclayout.cpp \
           src/telnetappender.cpp \
           src/writerappender.cpp \
           src/systemlogappender.cpp \
           src/helpers/classlogger.cpp \
           src/helpers/appenderattachable.cpp \
           src/helpers/configuratorhelper.cpp \
           src/helpers/datetime.cpp \
           src/helpers/factory.cpp \
           src/helpers/initialisationhelper.cpp \
           src/helpers/logerror.cpp \
           src/helpers/logobject.cpp \
           src/helpers/logobjectptr.cpp \
           src/helpers/optionconverter.cpp \
           src/helpers/patternformatter.cpp \
           src/helpers/properties.cpp \
           src/helpers/dispatcher.cpp \
           src/spi/filter.cpp \
           src/varia/debugappender.cpp \
           src/varia/denyallfilter.cpp \
           src/varia/levelmatchfilter.cpp \
           src/varia/levelrangefilter.cpp \
           src/varia/listappender.cpp \
           src/varia/nullappender.cpp \
           src/varia/stringmatchfilter.cpp \
           src/logstream.cpp
