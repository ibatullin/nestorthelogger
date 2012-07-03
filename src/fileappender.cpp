#include "fileappender.h"

#include <QDate>

FileAppender::FileAppender(const QString &dirPath, QObject *parent) :
    AbstractAppender(parent)
{
    setLogDirectory(dirPath);
    setFileNameFormat("yyyy-MM-dd.log");
}

FileAppender::FileAppender(QObject *parent) :
    AbstractAppender(parent)
{
    setLogDirectory(".");
    setFileNameFormat("yyyy-MM-dd.log");
}

bool FileAppender::open()
{
    file.setFileName(QString("%1/%2")
                      .arg(dir.absolutePath()).arg(getLogFileName()));

    QFileInfo info(file);
    qDebug() << "Open " << info.absoluteFilePath();

    if (!file.open(QFile::Append)) {
        qDebug() << "Can't open log file " << file.fileName();
        return false;
    }

    stream.setDevice(&file);
    AbstractAppender::open();
    return true;
}

void FileAppender::close()
{
    stream.flush();
    file.close();
    AbstractAppender::close();
}

void FileAppender::writeData(const QString &data)
{
    stream << data;
    stream.flush();
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
    QString logFileName = fileNameFormat;
    QString datePattern = "%d{";
    int datePatternSize = datePattern.size();

    int startPos = logFileName.indexOf(datePattern);
    int endPos = logFileName.indexOf("}", startPos + 1);
    if (startPos == -1 && endPos == -1)
        return logFileName;

    QString format = logFileName.mid(startPos + datePatternSize, endPos - startPos - datePatternSize);
    logFileName.remove(endPos, 1);
    logFileName.remove(startPos, datePatternSize);
    QString dateTime = QDateTime::currentDateTime().toString(format);
    logFileName = logFileName.replace(format, dateTime);
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
