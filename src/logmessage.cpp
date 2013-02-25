#include "logmessage.h"

LogMessage::LogMessage() :
    m_lineNumber(0)
{
    m_dateTime = QDateTime::currentDateTime();
}

LogMessage::~LogMessage()
{
}

void LogMessage::setSender(const QString &sender)
{
    m_sender = sender;
}

QString LogMessage::sender() const
{
    return m_sender;
}

void LogMessage::setLineNumber(int number)
{
    m_lineNumber = number;
}

int LogMessage::lineNumber()
{
    return m_lineNumber;
}

void LogMessage::setFunction(const QString &function)
{
    m_function = function;
}

QString LogMessage::function() const
{
    return m_function;
}

void LogMessage::setText(const QString &text)
{
    m_text = text;
}

QString LogMessage::text() const
{
    return m_text;
}

void LogMessage::setCategoryName(const QString &logName)
{
    m_categoryName = logName;
}

QString LogMessage::categoryName() const
{
    return m_categoryName;
}

void LogMessage::setLevel(MessageLevel level)
{
    m_level = level;
}

void LogMessage::setLevel(QtMsgType type)
{
    switch (type) {
    case QtDebugMsg:
        m_level = DebugLevel;
        break;
    case QtWarningMsg:
        m_level = WarningLevel;
        break;
    case QtCriticalMsg:
        m_level = CriticalLevel;
        break;
    case QtFatalMsg:
        m_level = FatalLevel;
        break;
    default:
        m_level = DebugLevel;
    }
}

LogMessage::MessageLevel LogMessage::level() const
{
    return m_level;
}

QDateTime LogMessage::dateTime() const
{
    return m_dateTime;
}

QString LogMessage::levelToString(MessageLevel level)
    {
        switch (level) {
        case DebugLevel:
            return "debug";
        case WarningLevel:
            return "warning";
        case CriticalLevel:
            return "critical";
        case FatalLevel:
            return "fatal";
        case LogLevel:
            return "log";
        case TraceLevel:
            return "trace";
        default:
            return "";
        }
    }
