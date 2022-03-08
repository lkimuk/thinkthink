#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H

#include <QByteArray>
#include <QXmlStreamWriter>



class RequestMessage
{
    Q_GADGET

public:
    enum RequestBody {
        RequestType,
    };
    Q_ENUM(RequestBody)
    RequestMessage();

    void setMessage(RequestBody type, const char* value);

    QByteArray data();

private:
    QByteArray buffer;
    QXmlStreamWriter xml;
};

#endif // REQUESTMESSAGE_H
