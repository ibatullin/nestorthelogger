#ifndef NULLAPPENDER_H
#define NULLAPPENDER_H

#include "abstractappender.h"

class NullAppender : public AbstractAppender
{
    Q_OBJECT
public:
    explicit NullAppender(QObject *parent = 0);
    virtual ~NullAppender();
    
protected:
    void writeData(const QString &data)
    {
        Q_UNUSED(data);
    }
};

#endif // NULLAPPENDER_H
