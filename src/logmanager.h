#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>

#include "logmessage.h"

class AbstractAppender;
class Logger;
class LogManagerPrivate;
class LogCategory;

class LogManager : public QObject
{
    Q_OBJECT
private:
    explicit LogManager();
    Q_DISABLE_COPY(LogManager)

public:
    virtual ~LogManager();
    bool setConfig(const QString &fileName);
    void createCategory(const QString &categoryName, AbstractAppender *appender, const QString &patternString);
    void addLogCategory(QSharedPointer<LogCategory> category);
    void clear();
    QString lifetime() const;
    QSharedPointer<AbstractAppender> defaultAppender() const;
    void write(LogMessage message);
    void enableMessageHandler();
    void disableMessageHandler();
    static LogManager *instance();

#if QT_VERSION >= 0x050000
    static void logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &text);
#else
    static void logMessageHandler(QtMsgType type, const char *text);
#endif

private:
    const QScopedPointer<LogManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(LogManager)
    static LogManager *self;
};

#endif // LOGMANAGER_H
