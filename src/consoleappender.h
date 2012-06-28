#ifndef CONSOLEAPPENDER_H
#define CONSOLEAPPENDER_H

#include "abstractappender.h"

class ConsoleAppender : public AbstractAppender
{
    Q_OBJECT
public:
    explicit ConsoleAppender(QObject *parent = 0);
    virtual ~ConsoleAppender();
    void writeData(const QString &data);
};

#endif // CONSOLEAPPENDER_H
