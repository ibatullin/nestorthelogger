#include <QString>
#include <QtTest>

#include "logpattern.h"

class LogPatternTest : public QObject
{
    Q_OBJECT
    
public:
    LogPatternTest();
    
private Q_SLOTS:
    void testCase1();
    void testCase1_data();

private:
    LogPattern logPattern;
    QString senderName;
    QString message;
    QString type;
};

LogPatternTest::LogPatternTest()
{
    senderName = "LogPatternTest";
    message = "test message";
    type = "ok";
}

void LogPatternTest::testCase1()
{
    QFETCH(QString, pattern);
    QFETCH(QString, result);

    logPattern.setPattern(pattern);
    QCOMPARE(logPattern.replace(senderName, message, type), result);
    QVERIFY2(true, "Failure");
}

void LogPatternTest::testCase1_data()
{
    QTest::addColumn<QString>("pattern");
    QTest::addColumn<QString>("result");

    QTest::newRow("only date") << QString("[%dd.MM.yyyy%]") << QString("[%1]")
                                  .arg(QDateTime::currentDateTime()
                                       .toString("dd.MM.yyyy"));
    QTest::newRow("only message") << QString("$message$") << message;
    QTest::newRow("bad marker") << QString("$sender_name$message$")
                                << QString("%1message$")
                                   .arg(senderName);
    QTest::newRow("full") << QString("[%dd.MM.yyyy hh%] -> ($type$)$sender_name$: $message$")
                          << QString("[%1] -> (%2)%3: %4")
                             .arg(QDateTime::currentDateTime()
                                  .toString("dd.MM.yyyy hh"))
                             .arg(type)
                             .arg(senderName)
                             .arg(message);
}

QTEST_APPLESS_MAIN(LogPatternTest)

#include "tst_logpatterntest.moc"
