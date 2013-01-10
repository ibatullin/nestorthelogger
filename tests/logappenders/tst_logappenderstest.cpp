#include <QString>
#include <QtTest>

#include "memoryappender.h"

class LogAppendersTest : public QObject
{
    Q_OBJECT
    
public:
    LogAppendersTest();
    
private Q_SLOTS:
    void memoryAppender();
};

LogAppendersTest::LogAppendersTest()
{
}

void LogAppendersTest::memoryAppender()
{
    MemoryAppender memoryAppender;
    memoryAppender.write("Test string");

    QCOMPARE(memoryAppender.readAll(), QString("Test string"));
    memoryAppender.clear();
    QCOMPARE(memoryAppender.readAll(), QString());

    LogMessage logMessage;
    logMessage.setText("Test String");
    logMessage.setCategoryName("category");
    logMessage.setFunction("memoryTest");
    logMessage.setLineNumber(10);
    logMessage.setSender("LogAppendersTest");

    QSharedPointer<LogPattern> pattern = memoryAppender.pattern();
    pattern->setPattern("%sender %line %function %category %text");
    memoryAppender.write(logMessage);
    QCOMPARE(memoryAppender.readAll(), QString("LogAppendersTest 10 memoryTest category Test String"));

}

QTEST_APPLESS_MAIN(LogAppendersTest)

#include "tst_logappenderstest.moc"
