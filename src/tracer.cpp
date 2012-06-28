#include "tracer.h"

#include "logmanager.h"
#include "logmessage.h"

Tracer::Tracer(const char *categoryName, const char *fileName, int lineNumber, const char *function) :
    categoryName(categoryName), sender(fileName), function(function), lineNumber(lineNumber)
{
}

void Tracer::write(const QString &text)
{
    LogMessage message;
    message.setCategoryName(categoryName);
    message.setSender(sender);
    message.setText(text);
    message.setLineNumber(lineNumber);
    message.setFunction(function);
    message.setLevel(LogMessage::TraceLevel);
    LogManager::instance()->write(message);
}
