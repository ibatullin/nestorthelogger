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
    output = output.replace("%{date}", QDate::currentDate().toString(Qt::ISODate));
    output = output.replace("%{time}", QTime::currentTime().toString(Qt::ISODate));
    output = output.replace("%{datetime}", QDateTime::currentDateTime().toString(Qt::ISODate));
    output = output.replace("%{textdate}", QDateTime::currentDateTime().toString(Qt::TextDate));
    output = output.replace("%{utc}", QDateTime::currentDateTimeUtc().toString(Qt::ISODate));

    return output;
}

