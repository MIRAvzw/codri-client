//
// Configuration
//

// Local includes
#include "datamanager.h"

// Library includes
#include "client.h"
#include "repository.h"
#include "repositorylistener.h"
#include "repoparameter.h"
#include "targets.h"
#include "client_parameter.h"

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
}


//
// Functionality
//

void DataManager::downloadData(const QString& iUrl)
{
    mLogger->trace() << Q_FUNC_INFO;

    /*
    QString p = iUrl;
    svn::repository::Repository rp(this);
    try {
        rp.CreateOpen(svn::repository::CreateRepoParameter().path(p).fstype("fsfs"));
    } catch (svn::ClientException e) {
        QString ex = e.msg();
        mLogger->error() << "Could not open repository: " << ex.toUtf8().data();
        return;
    }
    */

    svn::ContextP m_CurrentContext;
    svn::Client* m_Svnclient;
    m_Svnclient=svn::Client::getobject(0,0);
    m_CurrentContext = new svn::Context();
    m_CurrentContext->setListener(this);

    m_Svnclient->setContext(m_CurrentContext);
    svn::CheckoutParameter cparams;
    cparams.moduleName(iUrl).destination("/tmp/test2").revision(svn::Revision::HEAD).peg(svn::Revision::HEAD).depth(svn::DepthInfinity);

    try {
        m_Svnclient->checkout(cparams);
    } catch (svn::ClientException e) {
        QString ex = e.msg();
        mLogger->error() << "Could not checkout repository: " << ex.toUtf8().data();
        return;
    }
}
