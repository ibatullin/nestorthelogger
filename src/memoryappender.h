#ifndef MEMORYAPPENDER_H
#define MEMORYAPPENDER_H

#include "abstractappender.h"
#include <QBuffer>

class MemoryAppender : public AbstractAppender
{
    Q_OBJECT
public:
    explicit MemoryAppender(QObject *parent = 0);
    virtual ~MemoryAppender();
    void clear();
    QString readAll();

signals:
    void readyRead();

protected:
    void writeData(const QString &data);

private:
    QString buf;
};

#endif // MEMORYAPPENDER_H
