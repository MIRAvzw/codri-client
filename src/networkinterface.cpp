/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "networkinterface.h"

// Local includes
#include "mainapplication.h"
#include "network/resources/kioskresource.h"
#include "network/resources/configurationresource.h"
#include "network/resources/presentationresource.h"


//
// Construction and destruction
//

Codri::NetworkInterface::NetworkInterface(QObject *iParent) throw(QException)
    : QObject(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Get webservice port
    unsigned int tPort = mSettings->value("port", 8080).toUInt();
    MainApplication::instance()->kiosk()->setPort(tPort);

    // Start the webservice dispatcher
    // TODO: fix memory
    mLogger->debug() << "Starting webservice";
    mWebserviceDispatcher = new WebserviceDispatcher(QHostAddress::Any, tPort);
    mWebserviceDispatcher->addService("kiosk", new KioskResource(mWebserviceDispatcher, mWebserviceDispatcher));
    mWebserviceDispatcher->addService("configuration", new ConfigurationResource(mWebserviceDispatcher, mWebserviceDispatcher));
    mWebserviceDispatcher->addService("presentation", new PresentationResource(mWebserviceDispatcher, mWebserviceDispatcher));
    mWebserviceDispatcher->start();

    // Instantiate server client
    mServerClient = new ServerClient("http://codri.local:8080/codri", this);

    // Registration controller
    mRegistrationController = new RegistrationController(mServerClient, this);
}

void Codri::NetworkInterface::start() {
    mRegistrationController->start();
}

Codri::NetworkInterface::~NetworkInterface() {
    mServerClient->unregisterKiosk();
}
