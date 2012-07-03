#ifndef ABSTRACTAPPENDER_H
#define ABSTRACTAPPENDER_H

#include <QObject>
#include <QMutex>
#include <QSharedPointer>
#include "logpattern.h"

class AbstractAppender : public QObject
{
    Q_OBJECT
public:
    explicit AbstractAppender(QObject *parent = 0);
    virtual ~AbstractAppender();
    void setName(const QString &name);
    QString name() const;
    void setPattern(QSharedPointer<LogPattern> pattern);
    QSharedPointer<LogPattern> pattern() const;
    virtual bool open();
    virtual void close();
    bool isOpen() const;
    void write(LogMessage message);
    void write(const QString &data);

protected:
    virtual void writeData(const QString &data) = 0;

private:
    QMutex mutex;
    QString m_name;
    QSharedPointer<LogPattern> m_pattern;
    bool m_open;
};

#endif // ABSTRACTAPPENDER_H
