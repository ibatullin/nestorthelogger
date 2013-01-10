#include <QString>
#include <QtTest>

#include "logmanager.h"
#include "logconfigreader.h"

class LogConfigReaderTest : public QObject
{
    Q_OBJECT
    
public:
    LogConfigReaderTest();
    
private Q_SLOTS:
    void testCase1();
};

LogConfigReaderTest::LogConfigReaderTest()
{
}

void LogConfigReaderTest::testCase1()
{
    LogManager *logManager = LogManager::instance();
    LogConfigReader reader;
    QVERIFY2(reader.read(":/config.xml"), "config.xml");

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(LogConfigReaderTest)

#include "tst_logconfigreadertest.moc"
