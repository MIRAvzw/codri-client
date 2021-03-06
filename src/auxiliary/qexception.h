/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef AUXILIARY_QEXCEPTION_H_
#define AUXILIARY_QEXCEPTION_H_

// Library includes
#include <QtCore/QMetaType>
#include <QtCore/QString>
#include <svnqt/exception.h>
#include <QtCore/QStringList>

class QException {
public:
    // Destructor
    ~QException() {
        if (hasCause()) {
            delete mCause;
        }
    }

    // Copy constructor
    QException(const QException& iException)
        : mMessage(iException.what()), mCause(iException.hasCause() ? new QException(iException.cause()) : 0) {
    }

    // Value constructors
    QException(const QString &iMessage, const QException &iCause) throw()
        : mMessage(iMessage), mCause(new QException(iCause)) {
    }
    QException(const QString &iMessage) throw() : mMessage(iMessage), mCause(0) {
    }

    // Default constructor
    QException() : mCause(0) {
    }

    // Convertors
    static QException fromSVNException(const svn::Exception &iException) {
        return QException("SVN exception -- " + iException.msg());
    }

    // Getters
    const QString &what() const {
        return mMessage;
    }
    const QException &cause() const {
        return *mCause;
    }

    // Flags
    bool hasCause() const {
        return mCause != 0;
    }

    QStringList causes() const {
        QStringList tCauses;
        if (hasCause()) {
            tCauses << cause().what();
            tCauses << cause().causes();
        }
        return tCauses;
    }

private:
    QString mMessage;
    QException const* const mCause;
};

Q_DECLARE_METATYPE(QException)

#endif  // AUXILIARY_QEXCEPTION_H_
