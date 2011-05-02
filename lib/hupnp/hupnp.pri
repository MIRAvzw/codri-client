INCLUDEPATH += $$PWD $$PWD/include/
DEPENDPATH += $$PWD

QT += core xml network

include(lib/qtsoap/qtsoap.pri)

exists(options.pri) {
    include(options.pri)
}

debug:DEFINES += DEBUG

HEADERS += \
    src/utils/hmisc_utils_p.h \
    src/utils/hfunctor.h \
    src/utils/hglobal.h \
    src/utils/hsysutils_p.h \
    src/utils/hthreadpool_p.h
    
SOURCES += \
    src/utils/hmisc_utils_p.cpp \
    src/utils/hsysutils_p.cpp \
    src/utils/hthreadpool_p.cpp

HEADERS += \
    src/devicemodel/hactions_setupdata.h \
    src/devicemodel/hasyncop.h \
    src/devicemodel/hexecargs.h \
    src/devicemodel/hactioninvoke.h \
    src/devicemodel/hactioninvoke_callback.h \
    src/devicemodel/hactionarguments.h \
    src/devicemodel/hactionarguments_p.h \
    src/devicemodel/hdevicestatus.h \
    src/devicemodel/hservice_p.h \
    src/devicemodel/hdevice_p.h \
    src/devicemodel/hdevices_setupdata.h \
    src/devicemodel/hservices_setupdata.h \
    src/devicemodel/hstatevariable_event.h \
    src/devicemodel/hstatevariable_p.h \
    src/devicemodel/hdevicemodel_infoprovider.h \
    src/devicemodel/hstatevariables_setupdata.h \
    src/devicemodel/client/hclientaction.h \
    src/devicemodel/client/hclientactionop.h \
    src/devicemodel/client/hclientaction_p.h \
    src/devicemodel/client/hclientdevice.h \
    src/devicemodel/client/hclientdevice_p.h \
    src/devicemodel/client/hclientservice.h \
    src/devicemodel/client/hclientservice_p.h \
    src/devicemodel/client/hclientstatevariable.h \
    src/devicemodel/client/hdefault_clientaction_p.h \
    src/devicemodel/client/hdefault_clientdevice_p.h \
    src/devicemodel/client/hdefault_clientservice_p.h \
    src/devicemodel/client/hdefault_clientstatevariable_p.h \
    src/devicemodel/server/hserveraction.h \
    src/devicemodel/server/hserverdevice.h \
    src/devicemodel/server/hserverdevice_p.h \
    src/devicemodel/server/hserverservice.h \
    src/devicemodel/server/hserverservice_p.h \
    src/devicemodel/server/hserverstatevariable.h \
    src/devicemodel/server/hdevicemodelcreator.h \
    src/devicemodel/server/hdefault_serverdevice_p.h \
    src/devicemodel/server/hdefault_serveraction_p.h \
    src/devicemodel/server/hdefault_serverstatevariable_p.h

EXPORTED_PRIVATE_HEADERS += \
    src/devicemodel/hservice_p.h \
    src/devicemodel/hdevice_p.h \
    src/devicemodel/server/hserverdevice_p.h \
    src/devicemodel/server/hserverservice_p.h

SOURCES += \
    src/devicemodel/hactions_setupdata.cpp \
    src/devicemodel/hasyncop.cpp \
    src/devicemodel/hexecargs.cpp \
    src/devicemodel/hactionarguments.cpp \
    src/devicemodel/hdevices_setupdata.cpp \
    src/devicemodel/hservices_setupdata.cpp \
    src/devicemodel/hstatevariable_event.cpp \
    src/devicemodel/hstatevariables_setupdata.cpp \
    src/devicemodel/hdevicemodel_infoprovider.cpp \
    src/devicemodel/client/hclientdevice.cpp \
    src/devicemodel/client/hclientaction.cpp \
    src/devicemodel/client/hclientactionop.cpp \
    src/devicemodel/client/hclientservice.cpp \
    src/devicemodel/client/hclientstatevariable.cpp \
    src/devicemodel/server/hserveraction.cpp \
    src/devicemodel/server/hserverdevice.cpp \
    src/devicemodel/server/hserverservice.cpp \
    src/devicemodel/server/hserverstatevariable.cpp \
    src/devicemodel/server/hdevicemodelcreator.cpp

HEADERS += \
    src/devicehosting/hdevicestorage_p.h \
    src/devicehosting/hddoc_parser_p.h \
    src/devicehosting/hmodelcreation_p.h \
    src/devicehosting/messages/hcontrol_messages_p.h \
    src/devicehosting/messages/hevent_messages_p.h \
    src/devicehosting/messages/hnt_p.h \
    src/devicehosting/messages/hsid_p.h \
    src/devicehosting/messages/htimeout_p.h \
    src/devicehosting/controlpoint/hcontrolpoint_p.h \
    src/devicehosting/controlpoint/hcontrolpoint.h \
    src/devicehosting/controlpoint/hdevicebuild_p.h \
    src/devicehosting/controlpoint/hclientmodel_creator_p.h \
    src/devicehosting/controlpoint/hcontrolpoint_configuration.h \
    src/devicehosting/controlpoint/hcontrolpoint_configuration_p.h \
    src/devicehosting/controlpoint/hcontrolpoint_dataretriever_p.h \
    src/devicehosting/controlpoint/hevent_subscription_p.h \
    src/devicehosting/controlpoint/hevent_subscriptionmanager_p.h \
    src/devicehosting/devicehost/hdevicehost_p.h \
    src/devicehosting/devicehost/hdevicehost.h \
    src/devicehosting/devicehost/hserverdevicecontroller_p.h \
    src/devicehosting/devicehost/hservermodel_creator_p.h \
    src/devicehosting/devicehost/hdevicehost_dataretriever_p.h \
    src/devicehosting/devicehost/hevent_notifier_p.h \
    src/devicehosting/devicehost/hdevicehost_configuration.h \
    src/devicehosting/devicehost/hdevicehost_configuration_p.h \
    src/devicehosting/devicehost/hdevicehost_runtimestatus_p.h \
    src/devicehosting/devicehost/hdevicehost_ssdp_handler_p.h \
    src/devicehosting/devicehost/hdevicehost_http_server_p.h \
    src/devicehosting/devicehost/hpresence_announcer_p.h \
    src/devicehosting/devicehost/hevent_subscriber_p.h

SOURCES += \
    src/devicehosting/hdevicestorage_p.cpp \
    src/devicehosting/hddoc_parser_p.cpp \
    src/devicehosting/hmodelcreation_p.cpp \
    src/devicehosting/messages/hcontrol_messages_p.cpp \
    src/devicehosting/messages/hevent_messages_p.cpp \
    src/devicehosting/messages/hnt_p.cpp \
    src/devicehosting/messages/hsid_p.cpp \
    src/devicehosting/messages/htimeout_p.cpp \
    src/devicehosting/controlpoint/hcontrolpoint.cpp \
    src/devicehosting/controlpoint/hclientmodel_creator_p.cpp \
    src/devicehosting/controlpoint/hdevicebuild_p.cpp \
    src/devicehosting/controlpoint/hcontrolpoint_configuration.cpp \
    src/devicehosting/controlpoint/hcontrolpoint_dataretriever_p.cpp \
    src/devicehosting/controlpoint/hevent_subscription_p.cpp \
    src/devicehosting/controlpoint/hevent_subscriptionmanager_p.cpp \
    src/devicehosting/devicehost/hdevicehost.cpp \
    src/devicehosting/devicehost/hservermodel_creator_p.cpp \
    src/devicehosting/devicehost/hdevicehost_dataretriever_p.cpp \
    src/devicehosting/devicehost/hevent_notifier_p.cpp \
    src/devicehosting/devicehost/hdevicehost_configuration.cpp \
    src/devicehosting/devicehost/hdevicehost_ssdp_handler_p.cpp \
    src/devicehosting/devicehost/hdevicehost_http_server_p.cpp \
    src/devicehosting/devicehost/hevent_subscriber_p.cpp
HEADERS += \
    src/http/hhttp_p.h \
    src/http/hhttp_header_p.h \
    src/http/hhttp_utils_p.h \
    src/http/hhttp_server_p.h \
    src/http/hhttp_asynchandler_p.h \
    src/http/hhttp_messaginginfo_p.h \
    src/http/hhttp_messagecreator_p.h

SOURCES += \
    src/http/hhttp_utils_p.cpp \
    src/http/hhttp_header_p.cpp \
    src/http/hhttp_server_p.cpp \
    src/http/hhttp_asynchandler_p.cpp \
    src/http/hhttp_messaginginfo_p.cpp \
    src/http/hhttp_messagecreator_p.cpp

HEADERS += \
    src/general/hupnp_defs.h \
    src/general/hupnp_fwd.h \
    src/general/hlogger_p.h \
    src/general/hupnp_global_p.h \
    src/general/hupnp_global.h \
    src/general/hclonable.h \
    src/general/hupnpinfo.h \
    src/general/hupnp_datatypes.h \
    src/general/hupnp_datatypes_p.h

SOURCES += \
    src/general/hupnp_global.cpp \
    src/general/hclonable.cpp \
    src/general/hlogger_p.cpp \
    src/general/hupnpinfo.cpp \
    src/general/hupnp_datatypes.cpp

HEADERS += \
    src/dataelements/hactioninfo.h \
    src/dataelements/hactioninfo_p.h \
    src/dataelements/hdeviceinfo.h \
    src/dataelements/hdeviceinfo_p.h \
    src/dataelements/hserviceinfo.h \
    src/dataelements/hserviceinfo_p.h \
    src/dataelements/hserviceid.h \
    src/dataelements/hudn.h \
    src/dataelements/hresourcetype.h \
    src/dataelements/hproduct_tokens.h \
    src/dataelements/hdiscoverytype.h \
    src/dataelements/hstatevariableinfo.h \
    src/dataelements/hstatevariableinfo_p.h \
    src/dataelements/hvaluerange_p.h

SOURCES += \
    src/dataelements/hactioninfo.cpp \
    src/dataelements/hdeviceinfo.cpp \
    src/dataelements/hserviceinfo.cpp \
    src/dataelements/hserviceid.cpp \
    src/dataelements/hudn.cpp \
    src/dataelements/hresourcetype.cpp \
    src/dataelements/hproduct_tokens.cpp \
    src/dataelements/hdiscoverytype.cpp \
    src/dataelements/hstatevariableinfo.cpp \
    src/dataelements/hvaluerange_p.cpp
HEADERS += \
    src/ssdp/hssdp.h \
    src/ssdp/hssdp_p.h \
    src/ssdp/hdiscovery_messages.h \
	src/ssdp/hssdp_messagecreator_p.h

SOURCES += \
    src/ssdp/hssdp.cpp \
    src/ssdp/hdiscovery_messages.cpp \
	src/ssdp/hssdp_messagecreator_p.cpp
HEADERS += \
    src/socket/hmulticast_socket.h \
    src/socket/hendpoint.h

SOURCES += \
    src/socket/hendpoint.cpp \
    src/socket/hmulticast_socket.cpp

includes.files += ./include/HUpnpCore/H*

