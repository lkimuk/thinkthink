#include "RequestMessage.h"
#include "Utils.hpp"


RequestMessage::RequestMessage()
    : xml(&buffer)
{
    xml.writeStartDocument();
    xml.writeStartElement("ThinkThinkRequest");
}

void RequestMessage::setMessage(RequestBody type, const char* value)
{
    xml.writeTextElement(QtEnumToString(type), value);
}

QByteArray RequestMessage::data()
{
    xml.writeEndElement();
    xml.writeEndDocument();

    return buffer;
}
