#include "logmanager.h"
#include "logmanager_p.h"

#include <QDebug>

#include "logcategory.h"
#include "consoleappender.h"

LogManager *LogManager::self = 0;

/*!
 * \mainpage NestorTheLogger
 *
 * \section intro Introduction
 * \b URL: http://timuribatullin.com/soft/nestorthelogger/
 *
 * \section using Using
 * \subsection using_qobjects Using with QObject classes
 * \include simplelogging/myclass.h
 */

LogManager::LogManager() :
    d_ptr(new LogManagerPrivate)
{
    enableMessageHandler();
    createCategory("default", new ConsoleAppender, "%sender %text%n");
}

LogManager::~LogManager()
{
    self = 0;
}

bool LogManager::setConfig(const QString &fileName)
{
    LogConfigReader configReader;
    return configReader.read(fileName);
}

void LogManager::createCategory(const QString &categoryName, AbstractAppender *appender, const QString &patternString)
{
    QSharedPointer<LogPattern> pattern = QSharedPointer<LogPattern>(new LogPattern);
    pattern->setPattern(patternString);
    QSharedPointer<AbstractAppender> a = QSharedPointer<AbstractAppender>(appender);
    a->setPattern(pattern);
    QSharedPointer<LogCategory> category = QSharedPointer<LogCategory>(new LogCategory(categoryName));
    category->setDefaultAppender(a);
    addLogCategory(category);
}

void LogManager::addLogCategory(QSharedPointer<LogCategory> category)
{
    Q_D(LogManager);
    d->deleteCategory(category->name());
    d->categories << category;
}

void LogManager::clear()
{
    Q_D(LogManager);
    d->clear();
}

QString LogManager::lifetime() const
{
    Q_D(const LogManager);
    double time = d->lifetime.elapsed();
    return QString::number(time/1000, 'f', 3);
}

QSharedPointer<AbstractAppender> LogManager::defaultAppender() const
{
    Q_D(const LogManager);
    return d->defaultAppender;
}

void LogManager::write(LogMessage message)
{
    Q_D(LogManager);
    auto log = d->findCategory(message.categoryName());
    if (!log)
        log = d->findCategory("default");
    if (log)
        log->write(message);
}

void LogManager::enableMessageHandler()
{
    qDebug() << "Message handler defined. All debug messages will prints out to LogManager.";
    qInstallMessageHandler(logMessageHandler);
}


void LogManager::disableMessageHandler()
{
    qDebug() << "Message handler restored.";
    qInstallMessageHandler((QtMessageHandler)0);
}

LogManager *LogManager::instance()
{
    if (self == 0)
        self = new LogManager;
    return self;
}


void LogManager::logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &text)
{
    LogMessage message;
    message.setCategoryName(context.category);
    message.setFunction(context.function);
    message.setSender(context.file);
    message.setLineNumber(context.line);
    message.setLevel(type);
    message.setText(text);
    LogManager::instance()->write(message);
}


/*
 * LogManagerPrivate
 */

LogManagerPrivate::LogManagerPrivate()
{
    lifetime.start();
}

LogManagerPrivate::~LogManagerPrivate()
{
}

void LogManagerPrivate::clear()
{
    hasError = false;
    errorString.clear();
    categories.clear();
    lifetime.restart(); //need or not?
}

bool LogManagerPrivate::reportError(const QString &errorString)
{
    hasError = true;
    this->errorString = errorString;
    return false;
}

QSharedPointer<LogCategory> LogManagerPrivate::findCategory(const QString &categoryName) const
{
    for (auto category : categories)
        if (category->name() == categoryName)
            return category;
    return QSharedPointer<LogCategory>();
}

void LogManagerPrivate::deleteCategory(const QString &categoryName)
{
    for (auto it = categories.begin(); it != categories.end(); ++it)
        if ((*it)->name() == categoryName)
            categories.erase(it);
}
