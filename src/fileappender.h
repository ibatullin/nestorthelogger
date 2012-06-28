#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H

#include "abstractappender.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMutex>

class FileAppender : public AbstractAppender
{
    Q_OBJECT
public:
    explicit FileAppender(QObject *parent = 0);
    FileAppender(const QString &dirPath, QObject *parent = 0);
    bool open();
    void close();
    void setFileName(const QString &fileName);
    void setLogDirectory(const QString &dirPath);
    void setFileNameFormat(const QString &format);
    QString getFileNameFormat() const;
    void clearAfterDays(int days);

protected:
    void writeData(const QString &data);

private:
    QString getLogFileName() const;

    QDir dir;
    QString fileName;
    QTextStream stream;
    QString fileNameFormat;
    QMutex mutex;
};

#endif // FILEAPPENDER_H
