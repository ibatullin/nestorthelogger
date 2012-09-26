#ifndef LOGCONFIGREADER_H
#define LOGCONFIGREADER_H

#include <QSharedPointer>
#include <QDomElement>

#include "logmessage.h"

class LogCategory;
class LogPattern;
class AbstractAppender;

class LogConfigReader
{
public:
    LogConfigReader();
    virtual ~LogConfigReader();
    bool read(const QString &fileName);

private:
    void createPattern(const QString &patternName, const QString &patternString);

    void readPatterns();
    void readAppenders();
    void readCategories();
    QSharedPointer<AbstractAppender> readFileAppender(QDomElement &fileAppenderElement);
    QSharedPointer<AbstractAppender> readConsoleAppender(QDomElement &consoleAppenderElement);
    void readLevel(QDomElement &element, const QString &levelName,
                   LogMessage::MessageLevel level, QSharedPointer<LogCategory> log);

    QSharedPointer<LogPattern> findPattern(const QString &patternName) const;
    QSharedPointer<AbstractAppender> findAppender(const QString &appenderName) const;
    bool reportError(const QString &errorString);
    void warn(const QString &message);

    QDomElement rootElement;
    bool hasError;
    QString errorString;
    QList<QSharedPointer<LogPattern> > patterns;
    QList<QSharedPointer<AbstractAppender> > appenders;
    QList<QSharedPointer<LogCategory> > log;

};

#endif // LOGCONFIGREADER_H
