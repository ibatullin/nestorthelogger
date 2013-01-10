#include "abstractappender.h"

AbstractAppender::AbstractAppender(QObject *parent) :
    QObject(parent)
{
    m_pattern = QSharedPointer<LogPattern>(new LogPattern);
    m_pattern->setName("default");
    m_pattern->setPattern("%text%n");
}

AbstractAppender::~AbstractAppender()
{
}

void AbstractAppender::setName(const QString &name)
{
    m_name = name;
}

QString AbstractAppender::name() const
{
    return m_name;
}

void AbstractAppender::setPattern(QSharedPointer<LogPattern> pattern)
{
    m_pattern = pattern;
}

QSharedPointer<LogPattern> AbstractAppender::pattern() const
{
    return m_pattern;
}

bool AbstractAppender::open()
{
    m_open = true;
    return true;
}

void AbstractAppender::close()
{
    m_open = false;
}

bool AbstractAppender::isOpen() const
{
    return m_open;
}

void AbstractAppender::write(LogMessage message)
{
    QMutexLocker locker(&mutex);
    if (!m_pattern)
        return;
    QString data = m_pattern->replace(message);
    writeData(data);
}

void AbstractAppender::write(const QString &data)
{
    QMutexLocker locker(&mutex);
    writeData(data);
}
