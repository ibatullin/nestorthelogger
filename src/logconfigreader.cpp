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
    LogManager *logManager = LogManager::instance();
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

    QDomElement rootElement = doc.documentElement();
    if (rootElement.tagName() != "logconfig")
        return reportError(QObject::tr("<logconfig> not found"));

    if (rootElement.attribute("version") != "1.0")
        return reportError("Wrong config version");

    QDomElement patternsElement = rootElement.firstChildElement("patterns");
    QDomElement p = patternsElement.firstChildElement("pattern");
    while (!p.isNull()) {
        QSharedPointer<LogPattern> pattern = QSharedPointer<LogPattern>(new LogPattern);
        QString name = p.attribute("name");
        QString patternString = p.text();
        patternString = patternString.trimmed();
        if (name.isEmpty())
            continue;
        pattern->setName(name);
        pattern->setPattern(patternString);
        patterns << pattern;
        p = p.nextSiblingElement();
    }

    if (patterns.isEmpty())
        return reportError(QObject::tr("Patterns not defined"));

    //Appenders
    QDomElement appendersElement = rootElement.firstChildElement("appenders");
    QDomElement a = appendersElement.firstChildElement();
    while (!a.isNull()) {
        QSharedPointer<AbstractAppender> appender;
        if (a.tagName() == "fileAppender")
            appender = readFileAppender(a);
        else if (a.tagName() == "consoleAppender")
            appender = readConsoleAppender(a);
        else
            return reportError(QObject::tr("Unknown appender"));

        QString name = a.attribute("name");
        QString patternName = a.attribute("pattern");
        QSharedPointer<LogPattern> pattern = findPattern(patternName);
        if (!pattern) {
            continue;
        }

        if (appender) {
            appender->setName(name);
            appender->setPattern(pattern);
            appenders << appender;
        }
        a = a.nextSiblingElement();
    }

    //logCategory
    QDomElement logElement = rootElement.firstChildElement("categories");
    QDomElement c = logElement.firstChildElement("category");
    while (!c.isNull()) {
        QString name = c.attribute("name");
        if (name.isEmpty())
            continue;
        QSharedPointer<LogCategory> logCategory = QSharedPointer<LogCategory>(new LogCategory(name));

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

    return true;
}

QSharedPointer<AbstractAppender> LogConfigReader::readFileAppender(QDomElement &fileAppenderElement)
{
    Q_UNUSED(fileAppenderElement);
    return QSharedPointer<FileAppender>(new FileAppender);
}

QSharedPointer<AbstractAppender> LogConfigReader::readConsoleAppender(QDomElement &consoleAppenderElement)
{
    Q_UNUSED(consoleAppenderElement);
    QSharedPointer<ConsoleAppender> appender = QSharedPointer<ConsoleAppender>(new ConsoleAppender);
    return appender.objectCast<AbstractAppender>();
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
    for (auto pattern : patterns)
        if (pattern->name() == patternName)
            return pattern;
    return QSharedPointer<LogPattern>();
}

QSharedPointer<AbstractAppender> LogConfigReader::findAppender(const QString &appenderName) const
{
    for (auto appender : appenders)
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
