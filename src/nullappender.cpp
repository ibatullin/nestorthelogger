#include "nullappender.h"

NullAppender::NullAppender(QObject *parent) :
    AbstractAppender(parent)
{
}

NullAppender::~NullAppender()
{
}
