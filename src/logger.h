#ifndef LOGGER_H
#define LOGGER_H

#include <QVariant>

class LoggerPrivate;

class Logger : public QObject
{
public:
    Logger(QObject *senderObject, const QString &categoryName = QString("default"));
    Logger(const QString &senderName, const QString &categoryName = QString("default"));
    virtual ~Logger();
    void write(const QString &text);

    template<class T>
    inline Logger &operator<<(T t)
    {
        QVariant v(t);
        write(v.toString());
        return *this;
    }

    static QString title(const QString &text);
    static QString highlight(const QString &text);
    static QString separator();

private:
    const QScopedPointer<LoggerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Logger)
};

#endif // LOGGER_H
