#include "logcategory.h"

#include "abstractappender.h"
#include "logpattern.h"
#include "logmanager.h"

LogCategory::LogCategory(const QString &name, QObject *parent) :
    QObject(parent), m_name(name)
{
}

LogCategory::~LogCategory()
{
}

QString LogCategory::name() const
{
    return m_name;
}

void LogCategory::setDefaultAppender(QSharedPointer<AbstractAppender> appender)
{
    if (appender) {
        if (!appender->isOpen())
            appender->open();
        m_defaultAppender = appender;
    }
}

QSharedPointer<AbstractAppender> LogCategory::defaultAppender() const
{
    return m_defaultAppender;
}

void LogCategory::addAppender(QSharedPointer<AbstractAppender> appender,
                              LogMessage::MessageLevel level)
{
    if (appender) {
        if (!appender->isOpen())
            appender->open();
        appenders[level] << appender;
    }
}

void LogCategory::write(LogMessage message)
{
    if (appenders.contains(message.level())) {
        for (QSharedPointer<AbstractAppender> appender : appenders[message.level()]) {
            appender->write(message);
        }
    } else {
        if (m_defaultAppender)
            m_defaultAppender->write(message);
        else
            LogManager::instance()->defaultAppender()->write(message);
    }
}

bool LogCategory::operator ==(const LogCategory &category)
{
    return (m_name == category.name());
}
