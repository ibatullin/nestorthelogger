#include <QString>
#include <QtTest>

#include "logmanager.h"
#include "logpattern.h"

class LogPatternTest : public QObject
{
    Q_OBJECT
    
public:
    LogPatternTest();
    
private Q_SLOTS:
    void initTestCase();
    void pattern();
    void pattern_data();

private:
    LogPattern logPattern;
    LogMessage message;
};

LogPatternTest::LogPatternTest()
{
}

void LogPatternTest::initTestCase()
{
    LogManager::instance()->disableMessageHandler();
    qApp->setApplicationName("LogPatternTest");
    message.setSender("sender");
    message.setCategoryName("category");
    message.setFunction("test_function()");
    message.setLevel(LogMessage::TraceLevel);
    message.setLineNumber(30);
    message.setText("log text");
}

void LogPatternTest::pattern()
{
    QFETCH(QString, pattern);
    QFETCH(QString, result);

    logPattern.setPattern(pattern);
    QCOMPARE(logPattern.replace(message), result);
}

void LogPatternTest::pattern_data()
{
    QTest::addColumn<QString>("pattern");
    QTest::addColumn<QString>("result");

    QTest::newRow("%{appname}") << QString("%{appname}") << "LogPatternTest";
    QTest::newRow("%{sender}") << QString("%{sender}") << "sender";
    QTest::newRow("%{file}") << QString("%{file}") << "sender";
    QTest::newRow("%{function}") << QString("%{function}") << "test_function()";
    QTest::newRow("%{line}") << QString("%{line}") << QString::number(30);
    QTest::newRow("%{message}") << QString("%{message}") << QString("log text");
    QTest::newRow("%{pid}") << QString("%{pid}") << QString::number(QCoreApplication::applicationPid());
    QTest::newRow("%{threadid}") << "%{threadid}" << "0x" + QString::number(qlonglong(QThread::currentThread()->currentThread()), 16);
    QTest::newRow("%{type}") << QString("%{type}") << LogMessage::levelToString(message.level());
    QTest::newRow("%{category}") << QString("%{category}") << "category";

    QTest::newRow("%{sender}%{message}") << QString("%{sender}%{message}") << QString("senderlog text");
    QTest::newRow("%%{sender}%%{message}") << QString("%%{sender}%%{message}") << QString("%sender%log text");
    QTest::newRow("%{message") << QString("%{message") << QString("%{message");

    qWarning() << "The test is time dependent!";
    QTest::newRow("%{date}") << QString("%{date}") << QDate::currentDate().toString("yyyy-MM-dd");
    QTest::newRow("%{time}") << QString("%{time}") << QTime::currentTime().toString("hh:mm:ss");
    QTest::newRow("%{datetime}") << QString("%{datetime}") <<  QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss");
    QTest::newRow("%{textdate}") << QString("%{textdate}") <<  QDateTime::currentDateTime().toString("ddd MMM dd hh:mm:ss yyyy");
    QTest::newRow("%{utc}") << QString("%{utc}") <<  QDateTime::currentDateTimeUtc().toString("yyyy-MM-ddThh:mm:ssZ");

}

QTEST_MAIN(LogPatternTest)

#include "tst_logpatterntest.moc"
