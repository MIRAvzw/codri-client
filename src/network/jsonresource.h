/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORK_JSONRESOURCE_H_
#define NETWORK_JSONRESOURCE_H_

// Library includes
#include <QtCore/QString>
#include <qjson/parser.h>
#include <qjson/serializer.h>

// Local includes
#include "auxiliary/qexception.h"
#include "network/resource.h"

namespace Codri {
    class JsonResource : public Resource {
    Q_OBJECT
    public:
        // Construction and destruction
        JsonResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent, const QVariant& iClassName = QVariant());
        virtual ~JsonResource();

    protected:
        // Result enum
        // TODO: similar way in Resource? Passing ByteArray?
        enum Result {
            VALID,
            INVALID,
            CONFLICT,
            UNSUPPORTED
        };
        void aggregateResult(Result& a, const Result& b) {
            if (b != VALID)
                a = b;
        }

        // Service methods
        virtual Result doJsonGET(QVariant& iReply);
        virtual Result doJsonPUT(const QVariant& iRequest);
        virtual Result doJsonPOST(const QVariant& iRequest);
        virtual Result doJsonDELETE();

        // Helper methods
        void doJsonReply(int iSessionId, int iRequestId, QVariant& iReply, Result iResult);
        void postInvalidPayload(int iSessionId, int iRequestId, QString iMessage);
        void postConflictingPayload(int iSessionId, int iRequestId);
        void postReply(int iSessionId, int iRequestId, QVariant &iData);

    private:
        // Member data
        QJson::Parser *mParser;
        QJson::Serializer *mSerializer;

        // Resource implementation
        void doGET(int iSessionId, int iRequestId);
        void doPUT(int iSessionId, int iRequestId, QIODevice *iContent);
        void doPOST(int iSessionId, int iRequestId, QIODevice *iContent);
        void doDELETE(int iSessionId, int iRequestId);
    };
}

#endif  // NETWORK_JSONRESOURCE_H_
