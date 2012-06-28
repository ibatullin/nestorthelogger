#ifndef LOGPATTERN_H
#define LOGPATTERN_H

#include <QString>
#include "logmessage.h"

class LogPattern
{
public:
    LogPattern();
    virtual ~LogPattern();
    void setName(const QString &name);
    QString name() const;
    void setPattern(const QString &pattern);
    QString pattern() const;
    QString replace(LogMessage message);

private:
    QString m_name;
    QString m_pattern;
};

#endif // LOGPATTERN_H
