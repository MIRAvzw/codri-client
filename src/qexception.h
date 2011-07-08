//
// Configuration
//

// Include guard
#ifndef EXCEPTION_H
#define EXCEPTION_H

// Library includes
#include <QtCore/QString>
#include <svnqt/exception.h>

class QException
{
public:
    QException(const QString& iMessage, const QException& iCause = QException()) throw() : mMessage(iMessage), mNull(false), mCause(iCause)
    {

    }
    QException() : mNull(true), mCause(QException())
    {

    }
    QException(const svn::Exception& iException) : mMessage("SVN exception -- " + iException.msg()), mNull(false), mCause(QException())
    {

    }

    const QString& what() const
    {
        return mMessage;
    }
    const QException& who() const
    {
        return mCause;
    }

    bool null() const
    {
        return mNull;
    }

    QString string() const
    {
        QString oMessage = what();
        if (! who().null())
            oMessage += "\nCaused by: " + who().string();
        return oMessage;
    }

private:
    QString mMessage;
    bool mNull;
    const QException& mCause;
};

#endif // EXCEPTION_H
