#include "logconfigreader.h"
#include <QDomDocument>
#include <QFile>
#include "logmanager.h"
#include "consoleappender.h"
#include "fileappender.h"
#include "nullappender.h"
#include "logcategory.h"
#include "logpattern.h"

LogConfigReader::LogConfigReader()
{
}

LogConfigReader::~LogConfigReader()
{
}

bool LogConfigReader::read(const QString &fileName)
{
    QDomDocument doc;
    QFile file;
    file.setFileName(fileName);
    if (!file.open(QFile::ReadOnly))
        return reportError(QObject::tr("Cannot open file %1 for reading: %2")
                              .arg(file.fileName())
                              .arg(file.errorString()));

    if (!doc.setContent(&file, false)) {
        file.close();
        return reportError(QObject::tr("Xml error"));
    }
    file.close();

    rootElement = doc.documentElement();
    if (rootElement.tagName() != "logconfig")
        return reportError(QObject::tr("<logconfig> not found"));

    if (rootElement.attribute("version") != "1.0")
        return reportError("Wrong config version");

    readPatterns();
    if (patterns.isEmpty())
        return reportError(QObject::tr("Patterns not defined"));

    readAppenders();
    readCategories();

    return true;
}

void LogConfigReader::readPatterns()
{
    QDomElement patternsElement = rootElement.firstChildElement("patterns");
    QDomElement p = patternsElement.firstChildElement("pattern");
    while (!p.isNull()) {
        QString name = p.attribute("name");
        if (name.isEmpty())
            continue;
        QString patternString = p.text();
        patternString = patternString.trimmed();
        QSharedPointer<LogPattern> pattern(new LogPattern);
        pattern->setName(name);
        pattern->setPattern(patternString);
        patterns << pattern;
        p = p.nextSiblingElement();
    }
}

void LogConfigReader::readAppenders()
{
    QDomElement appendersElement = rootElement.firstChildElement("appenders");
    QDomElement a = appendersElement.firstChildElement();
    while (!a.isNull()) {
        QSharedPointer<AbstractAppender> appender;
        if (a.tagName() == "fileAppender")
            appender = readFileAppender(a);
        else if (a.tagName() == "consoleAppender")
            appender = readConsoleAppender(a);

        if (!appender) {
            warn(QObject::tr("Unknown appender type"));
            continue;
        }

        QString name = a.attribute("name");
        QString patternName = a.attribute("pattern");
        QSharedPointer<LogPattern> pattern = findPattern(patternName);
        if (!pattern)
            continue;

        if (appender) {
            appender->setName(name);
            appender->setPattern(pattern);
            appenders << appender;
        }
        a = a.nextSiblingElement();
    }
}

void LogConfigReader::readCategories()
{
    QDomElement logElement = rootElement.firstChildElement("categories");
    QDomElement c = logElement.firstChildElement("category");
    LogManager *logManager = LogManager::instance();
    while (!c.isNull()) {
        QString name = c.attribute("name");
        if (name.isEmpty())
            continue;

        QSharedPointer<LogCategory> logCategory(new LogCategory(name));

        readLevel(c, "warning", LogMessage::WarningLevel, logCategory);
        readLevel(c, "critical", LogMessage::CriticalLevel, logCategory);
        readLevel(c, "fatal", LogMessage::FatalLevel, logCategory);
        readLevel(c, "debug", LogMessage::DebugLevel, logCategory);
        readLevel(c, "trace", LogMessage::TraceLevel, logCategory);

        QDomElement defaultAppenderElement = c.firstChildElement("default");
        if (defaultAppenderElement.isNull()) {
            logCategory->setDefaultAppender(QSharedPointer<AbstractAppender>(new NullAppender));
        } else {
            QString appenderName = defaultAppenderElement.attribute("appender");
            QSharedPointer<AbstractAppender> defaultAppender = findAppender(appenderName);
            if (defaultAppender)
                logCategory->setDefaultAppender(defaultAppender);
        }

        logManager->addLogCategory(logCategory);

        c = c.nextSiblingElement();
    }
}

QSharedPointer<AbstractAppender> LogConfigReader::readFileAppender(QDomElement &fileAppenderElement)
{
    Q_UNUSED(fileAppenderElement);
    QSharedPointer<FileAppender> fileAppender(new FileAppender);
    QDomElement e = fileAppenderElement.firstChildElement();
    while (!e.isNull()) {
        if (e.tagName() == "dir") {
            fileAppender->setLogDirectory(e.text());
        } else if (e.tagName() == "fileName") {
            fileAppender->setFileNameFormat(e.text());
        } else if (e.tagName() == "clearAfter") {
            bool ok;
            int days = e.text().toInt(&ok);

            if (ok)
                fileAppender->clearAfterDays(days);
            else
                warn(QObject::tr("clearAfter should be digit"));
        }
    }
    return fileAppender;
}

QSharedPointer<AbstractAppender> LogConfigReader::readConsoleAppender(QDomElement &consoleAppenderElement)
{
    Q_UNUSED(consoleAppenderElement);
    return QSharedPointer<AbstractAppender>(new ConsoleAppender);
}

void LogConfigReader::readLevel(QDomElement &logElement,
                                const QString &levelName,
                                LogMessage::MessageLevel level,
                                QSharedPointer<LogCategory> logCategory)
{
    QDomElement element = logElement.firstChildElement(levelName);

    while (!element.isNull()) {
        QString appenderName = element.attribute("appender");
        QSharedPointer<AbstractAppender> appender = findAppender(appenderName);
        if (appender)
            logCategory->addAppender(appender, level);
        element = element.nextSiblingElement(levelName);
    }
}

QSharedPointer<LogPattern> LogConfigReader::findPattern(const QString &patternName) const
{
#ifdef C11
    for (auto pattern : patterns)
#else
    foreach (QSharedPointer<LogPattern> pattern, patterns)
#endif
        if (pattern->name() == patternName)
            return pattern;
    return QSharedPointer<LogPattern>();
}

QSharedPointer<AbstractAppender> LogConfigReader::findAppender(const QString &appenderName) const
{
#ifdef C11
    for (auto appender : appenders)
#else
    foreach (QSharedPointer<AbstractAppender> appender, appenders)
#endif
    if (appender->name() == appenderName)
            return appender;
    return QSharedPointer<AbstractAppender>();
}

bool LogConfigReader::reportError(const QString &errorString)
{
    hasError = true;
    this->errorString = errorString;
    return false;
}

void LogConfigReader::warn(const QString &message)
{
    qWarning() << "NestorTheLogger: config error(" << message << ")";
}
