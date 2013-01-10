#include "memoryappender.h"

MemoryAppender::MemoryAppender(QObject *parent) :
    AbstractAppender(parent)
{
}

MemoryAppender::~MemoryAppender()
{
}

void MemoryAppender::clear()
{
    buf.clear();
}

QString MemoryAppender::readAll()
{
    return buf;
}

void MemoryAppender::writeData(const QString &data)
{
    buf.append(data);
}
