//
// Configuration
//

// Local includes
#include "datamanager.h"

// Library includes
#include <QtCore/QDir>
#include "repository.h"
#include "repositorylistener.h"
#include "repoparameter.h"
#include "targets.h"
#include "client_parameter.h"
#include "client_update_parameter.h"

// Definitions
#define CHECKOUT_PATH "/tmp"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("Repository");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("Repository");
    mLogger->trace() << Q_FUNC_INFO;

    // Configure subversion
    svn::ContextP tSubversionContext;
    mSubversionClient = svn::Client::getobject(0,0);
    tSubversionContext = new svn::Context();
    tSubversionContext->setListener(this);
    mSubversionClient->setContext(tSubversionContext);
}


//
// Functionality
//

QString DataManager::downloadData(const QString& iIdentifier, const QString& iUrl) throw(QException)
{
    mLogger->trace() << Q_FUNC_INFO;

    // Existing checkout?
    QDir tCheckoutDirectory(QString(CHECKOUT_PATH) + "/" + iIdentifier);
    if (tCheckoutDirectory.exists())
    {
        mLogger->debug() << "Updating media at " << tCheckoutDirectory.absolutePath();
        svn::UpdateParameter tUpdateParameters;
        tUpdateParameters
                .targets(tCheckoutDirectory.absolutePath())
                .revision(svn::Revision::HEAD)
                .depth(svn::DepthInfinity);

        try
        {
            mSubversionClient->update(tUpdateParameters);
        }
        catch (svn::ClientException iException)
        {
            throw QException("could not update the repository", iException);
        }
    }

    // New checkout?
    else
    {
        mLogger->debug() << "Download media into " << tCheckoutDirectory.absolutePath();
        svn::CheckoutParameter tCheckoutParameters;
        tCheckoutParameters
                .moduleName(iUrl)
                .destination(tCheckoutDirectory.absolutePath())
                .revision(svn::Revision::HEAD)
                .peg(svn::Revision::HEAD)
                .depth(svn::DepthInfinity);

        try
        {
            mSubversionClient->checkout(tCheckoutParameters);
        }
        catch (svn::ClientException iException)
        {
            throw QException("could not checkout the repository", iException);
        }
    }
}