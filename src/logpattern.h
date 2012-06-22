#ifndef LOGPATTERN_H
#define LOGPATTERN_H

#include <QObject>

class LogPattern : public QObject
{
    Q_OBJECT
public:
    explicit LogPattern(QObject *parent = 0);
    void setPattern(const QString &pattern);
    QString replace(const QString &senderName, const QString &message, const QString &type);

private:
    QString m_pattern;
};

#endif // LOGPATTERN_H
