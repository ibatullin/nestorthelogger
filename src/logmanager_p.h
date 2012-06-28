#ifndef LOGMANAGER_P_H
#define LOGMANAGER_P_H

#include "logconfigreader.h"

class LogManagerPrivate
{
public:
    LogManagerPrivate();
    virtual ~LogManagerPrivate();

    void clear();
    void write(Logger *logger, const QString &message,
               const QString &logName, LogMessage::MessageLevel level);
    bool reportError(const QString &errorString);
    QSharedPointer<LogCategory> findCategory(const QString &categoryName) const;
    void deleteCategory(const QString &categoryName);

    bool hasError;
    QString errorString;
    QList<QSharedPointer<LogCategory> > categories;
    QSharedPointer<AbstractAppender> defaultAppender;
    QTime lifetime;
};

#endif // LOGMANAGER_P_H
