#include "logpattern.h"
#include <QDateTime>
#include <QCoreApplication>
#include <QThread>
#include "logmessage.h"
#include "logmanager.h"

LogPattern::LogPattern()
{
}

LogPattern::~LogPattern()
{
}

void LogPattern::setName(const QString &name)
{
    m_name = name;
}

QString LogPattern::name() const
{
    return m_name;
}

void LogPattern::setPattern(const QString &pattern)
{
    m_pattern = pattern;
}

QString LogPattern::pattern() const
{
    return m_pattern;
}

QString LogPattern::replace(LogMessage message)
{
    QString output = m_pattern;

    output = output.replace("%{appname}", QCoreApplication::applicationName());
    output = output.replace("%{sender}", message.sender());
    output = output.replace("%{file}", message.sender());
    output = output.replace("%{function}", message.function());
    output = output.replace("%{line}", QString::number(message.lineNumber()));
    output = output.replace("%{message}", message.text());
    output = output.replace("%{pid}", QString::number(QCoreApplication::applicationPid()));
    QString threadId = "0x" + QString::number(qlonglong(QThread::currentThread()->currentThread()), 16);
    output = output.replace("%{threadid}", threadId);
    output = output.replace("%{type}", LogMessage::levelToString(message.level()));
    output = output.replace("%{category}", message.categoryName());
    output = output.replace("%{lifetime}", LogManager::instance()->lifetime());

    QString datePattern = "%d{";
    int datePatternSize = datePattern.size();

    int startPos = output.indexOf(datePattern);
    int endPos = output.indexOf("}", startPos + 1);
    if (startPos == -1 && endPos == -1)
        return output;

    QString format = output.mid(startPos + datePatternSize, endPos - startPos - datePatternSize);
    output.remove(endPos, 1);
    output.remove(startPos, datePatternSize);
    QString dateTime = message.dateTime().toString(format);
    output = output.replace(format, dateTime);
    return output;
}

