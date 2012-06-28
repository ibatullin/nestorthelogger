#ifndef LOGGER_P_H
#define LOGGER_P_H

#include <QString>

class LoggerPrivate {
public:
    LoggerPrivate();
    virtual ~LoggerPrivate();

    QString sender;
    QString categoryName;
};

#endif // LOGGER_P_H
