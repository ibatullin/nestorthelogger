#include "logpattern.h"
#include <QDateTime>

LogPattern::LogPattern(QObject *parent) :
    QObject(parent)
{
}

void LogPattern::setPattern(const QString &pattern)
{
    m_pattern = pattern;
}

QString LogPattern::replace(const QString &senderName, const QString &message, const QString &type)
{
    QString output = m_pattern;
    output = output.replace("$sender_name$", senderName);
    output = output.replace("$type$", type);
    output = output.replace("$message$", message);

    int startPos = output.indexOf("%");
    int endPos = output.indexOf("%", startPos + 1);
    if (startPos == -1 && endPos == -1)
        return output;

    QString format = output.mid(startPos + 1, endPos - startPos - 1);
    QString dateTime = QDateTime::currentDateTime().toString(format);
    output = output.replace(format, dateTime);
    output.remove(startPos, 1);
    output.remove(endPos - 1, 1);
    return output;
}
