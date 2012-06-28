#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <QString>
#include <QDateTime>

class LogMessage
{
public:
    enum MessageLevel {
        DebugLevel,
        WarningLevel,
        CriticalLevel,
        FatalLevel,
        LogLevel,
        TraceLevel
    };

    LogMessage();
    virtual ~LogMessage();
    void setText(const QString &text);
    QString text() const;
    void setCategoryName(const QString &categoryName);
    QString categoryName() const;
    void setSender(const QString &sender);
    QString sender() const;
    void setLineNumber(int number);
    int lineNumber();
    void setFunction(const QString &function);
    QString function() const;
    void setLevel(MessageLevel level);
    void setLevel(QtMsgType type);
    MessageLevel level() const;
    QDateTime dateTime() const;
    static QString levelToString(MessageLevel level);

private:
    QString m_text;
    QString m_categoryName;
    QString m_sender;
    int m_lineNumber;
    QString m_function;
    MessageLevel m_level;
    QtMsgType m_type;
    QDateTime m_dateTime;
};

#endif // LOGMESSAGE_H
