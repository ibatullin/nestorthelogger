#include <QString>
#include <QtTest>

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
    QVERIFY2(true, "Failure");
}

void LogPatternTest::pattern_data()
{
    QTest::addColumn<QString>("pattern");
    QTest::addColumn<QString>("result");

    QTest::newRow("only date") << QString("[%d{dd.MM.yyyy}]") << QString("[%1]")
                                  .arg(QDateTime::currentDateTime()
                                       .toString("dd.MM.yyyy"));

    QTest::newRow("datetime") << QString("%d{dd.MM.yyyy hh:mm}") << QString("%1")
                                  .arg(QDateTime::currentDateTime()
                                       .toString("dd.MM.yyyy hh:mm"));

    QTest::newRow("only text") << QString("%text") << message.text();
    QTest::newRow("text and end line") << QString("%text%n") << message.text() + "\n";
    QTest::newRow("marker") << QString("%sendera%text%")
                                << QString("%1a%2%")
                                   .arg(message.sender())
                                   .arg(message.text());
    QTest::newRow("full") << QString("[%d{dd.MM.yyyy hh}] -> %sender(%function at line %line) [%category:%level] %text%n")
                          << QString("[%1] -> %2(%3 at line %4) [%5:%6] %7\n")
                             .arg(QDateTime::currentDateTime()
                                  .toString("dd.MM.yyyy hh"))
                             .arg(message.sender())
                             .arg(message.function())
                             .arg(message.lineNumber())
                             .arg(message.categoryName())
                             .arg(LogMessage::levelToString(message.level()))
                             .arg(message.text());
}

QTEST_APPLESS_MAIN(LogPatternTest)

#include "tst_logpatterntest.moc"
