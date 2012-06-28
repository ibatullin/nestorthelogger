#include "consoleappender.h"

#include <iostream>

ConsoleAppender::ConsoleAppender(QObject *parent) :
    AbstractAppender(parent)
{
}

ConsoleAppender::~ConsoleAppender()
{
}

void ConsoleAppender::writeData(const QString &data)
{
    std::cout << data.toUtf8().data() << std::flush;
}
