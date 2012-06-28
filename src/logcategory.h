#ifndef LOGCATEGORY_H
#define LOGCATEGORY_H

#include <QObject>
#include "logmessage.h"

class AbstractAppender;

class LogCategory : public QObject
{
    Q_OBJECT
public:
    LogCategory(const QString &name, QObject *parent = 0);
    virtual ~LogCategory();
    QString name() const;
    void setDefaultAppender(QSharedPointer<AbstractAppender> appender);
    QSharedPointer<AbstractAppender> defaultAppender() const;
    void addAppender(QSharedPointer<AbstractAppender> appender,
                     LogMessage::MessageLevel level);
    void write(LogMessage message);
    bool operator==(const LogCategory &category);

private:
    QHash<LogMessage::MessageLevel, QList<QSharedPointer<AbstractAppender> > > appenders;
    QSharedPointer<AbstractAppender> m_defaultAppender;
    QString m_name;
};

#endif // LOGCATEGORY_H
