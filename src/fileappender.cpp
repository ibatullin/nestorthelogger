#include "fileappender.h"

#include <QDate>

FileAppender::FileAppender(const QString &dirPath, QObject *parent) :
    AbstractAppender(parent)
{
    setLogDirectory(dirPath);
    setFileNameFormat("yyyy-MM-dd");
}

FileAppender::FileAppender(QObject *parent) :
    AbstractAppender(parent)
{
    setLogDirectory(".");
    setFileNameFormat("yyyy-MM-dd");
}

bool FileAppender::open()
{
    qDebug() << dir.absolutePath();

    QScopedPointer<QFile> file(new QFile);
    file->setFileName(QString("%1/%2").arg(dir.absolutePath()).arg(getLogFileName()));
    if (!file->open(QFile::Append)) {
        qDebug() << "Can't open log file " << file->fileName();
        return false;
    }

    stream.setDevice(file.take());
    return true;
}

void FileAppender::close()
{
    stream.flush();
}

void FileAppender::writeData(const QString &data)
{
    stream << data;
    stream.flush();
}

void FileAppender::setFileName(const QString &fileName)
{
    this->fileName = fileName;
}

void FileAppender::setFileNameFormat(const QString &format)
{
    fileNameFormat= format;
}

QString FileAppender::getFileNameFormat() const
{
    return fileNameFormat;
}

void FileAppender::setLogDirectory(const QString &dirPath)
{
    dir.setPath(dirPath);
    if (!dir.exists()) {
        if (!dir.mkpath(dir.absolutePath())) {
            qDebug() << "Can't create directory " << dir.absolutePath();
            dir.setPath(".");
        }
    }
}

QString FileAppender::getLogFileName() const
{
    QString logFileName;
    logFileName += QDate::currentDate().toString(fileNameFormat);
    logFileName += ".log";
    return logFileName;
}

void FileAppender::clearAfterDays(int days)
{
    QFileInfoList fileInfoList = dir.entryInfoList(QStringList("*.log"), QDir::Files);
    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();
    dateTime = dateTime.addDays(-days);
    foreach (const QFileInfo &fileInfo, fileInfoList) {
        if (fileInfo.created() <= dateTime) {
            qDebug() << "Log removed " << fileInfo.fileName();
            dir.remove(fileInfo.fileName());
        }
    }
}
