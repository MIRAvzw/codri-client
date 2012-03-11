/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "webservicedispatcher.h"


//
// Construction and destruction
//

MIRA::WebserviceDispatcher::WebserviceDispatcher(const QHostAddress &iHost, quint16 iPort)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("WebserviceDispatcher");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Start webservice
    QxtHttpSessionManager(this);
    mRootService = new Resource(this, this);
    setPort(iPort);
    setListenInterface(iHost);
    setConnector(HttpServer);
    setStaticContentService(mRootService);
}

MIRA::WebserviceDispatcher::~WebserviceDispatcher()
{
    delete mRootService;
}


//
// Functionality
//


void MIRA::WebserviceDispatcher::addService(QString iUri, Resource* iSubService)
{
    mRootService->addService(iUri, iSubService);
}

