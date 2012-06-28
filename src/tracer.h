#ifndef TRACER_H
#define TRACER_H

#include <QVariant>

class Tracer
{
public:
    Tracer(const char *categoryName, const char *fileName, int lineNumber, const char *function);

    template<class T>
    inline const Tracer &operator<<(T t)
    {
        QVariant v(t);
        write(v.toString());
        return *this;
    }

    void operator()()
    {
        write("");
    }

    void write(const QString &text);

private:
    const char *categoryName;
    const char *sender;
    const char *function;
    int lineNumber;
};

#define DECLARE_TRACER_CAT(Category) \
    Tracer create_tracer(const char *fileName, int lineNumber, const char *function) \
    { return Tracer(Category, fileName, lineNumber, function); }

#define DECLARE_TRACER \
    Tracer create_tracer(const char *fileName, int lineNumber, const char *function) \
{ return Tracer("default", fileName, lineNumber, function); }

#define trace create_tracer(__FILE__, __LINE__, Q_FUNC_INFO)

#endif // TRACER_H
