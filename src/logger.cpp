#include "logger.h"
#include "logger_p.h"

#include "logmanager.h"

Logger::Logger(QObject *senderObject, const QString &categoryName) :
    d_ptr(new LoggerPrivate)
{
    Q_D(Logger);
    d->sender = senderObject->metaObject()->className();
    d->categoryName = categoryName;
}

Logger::Logger(const QString &senderName, const QString &categoryName) :
    d_ptr(new LoggerPrivate)
{
    Q_D(Logger);
    d->sender = senderName;
    d->categoryName = categoryName;
}

Logger::~Logger()
{
}

void Logger::write(const QString &text)
{
    Q_D(Logger);
    LogMessage message;
    message.setCategoryName(d->categoryName);
    message.setSender(d->sender);
    message.setText(text);
    message.setLevel(LogMessage::LogLevel);
    LogManager::instance()->write(message);
}

QString Logger::title(const QString &text)
{
    QChar c = '*';
    int titleLength = 50;

    QString decoration;
    decoration.fill(c, titleLength);

    QString output;

    output.append(c);
    QString space;
    space.fill(' ', (titleLength - 2 - text.length()) / 2);
    output.append(space);
    output.append(text);
    output.append(space);

    if (output.size() + 2 <= titleLength)
        output.append(' ');
    output.append(c);
    return QString("\n\n%2\n%1\n%2\n").arg(output).arg(decoration);
}

QString Logger::highlight(const QString &text)
{
    QString output;
    QString highlighter;
    highlighter.fill('*', 10);
    output.append(highlighter);
    output.append(text);
    output.append(highlighter);
    return output;
}

QString Logger::separator()
{
    QString s;
    s.fill('-', 40);
    return s;
}


/*
 * LoggerPrivate
 */

LoggerPrivate::LoggerPrivate()
{
}


LoggerPrivate::~LoggerPrivate()
{
}
