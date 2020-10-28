#include <stdio.h>
#include <utility>

class logger
{
public:
    logger()
    {
        printf("logger()\n");
    }
    logger(logger &) //copy
    {
        printf("logger(logger &)\n");
    }
    logger(const logger &) //copy
    {
        printf("logger(const logger &)\n");
    }
    logger(const logger &&) //move
    {
        printf("logger(const logger &&)\n");
    }

    virtual ~logger()
    {
        printf("~logger()\n");
    }

    // virtual void Operation() = 0;
    // virtual void Operation(int a) = 0;
    // virtual void Operation(int &a) = 0;
    virtual void Operation(int &&a) = 0;
};

class loggerA : public logger
{
public:
    loggerA()
    {
        printf("loggerA()\n");
    }
    loggerA(loggerA &) //copy
    {
        printf("loggerA(loggerA &)\n");
    }
    loggerA(const loggerA &) //copy
    {
        printf("loggerA(const loggerA &)\n");
    }
    loggerA(const loggerA &&) //move
    {
        printf("loggerA(const loggerA &&)\n");
    }
    loggerA &operator=(const loggerA &) //move
    {
        printf("loggerA &operator=(const loggerA &)\n");
    }
    ~loggerA()
    {
        printf("~loggerA()\n");
    }

    // void Operation()
    // {
    //     printf("loggerA Operation()\n");
    // }
    // void Operation(int a)
    // {
    //     printf("loggerA Operation(a)\n");
    // }
    // void Operation(int &a)
    // {
    //     printf("loggerA Operation(&a)\n");
    // }
    void Operation(int &&a)
    {
        printf("loggerA Operation(&&a)\n");
    }
};

class loggerB : public logger
{
public:
    loggerB()
    {
        printf("loggerB()\n");
    }
    loggerB(loggerB &) //copy
    {
        printf("loggerB(loggerB &)\n");
    }
    loggerB(const loggerB &) //copy
    {
        printf("loggerB(const loggerB &)\n");
    }
    loggerB(const loggerB &&) //move
    {
        printf("loggerB(const loggerB &&)\n");
    }
    loggerB &operator=(const loggerB &) //move
    {
        printf("loggerB &operator=(const loggerB &)\n");
    }
    ~loggerB()
    {
        printf("~loggerB()\n");
    }

    // void Operation()
    // {
    //     printf("loggerB Operation()\n");
    // }
    // void Operation(int a)
    // {
    //     printf("loggerB Operation(a)\n");
    // }
    // void Operation(int &a)
    // {
    //     printf("loggerB Operation(&a)\n");
    // }
    void Operation(int &&a)
    {
        printf("loggerB Operation(&&a)\n");
    }
};

template <typename T>
void LoggerOperation(T &t)
{
    int a;
    t.Operation(a);
}

template <typename T>
T &&GetLogger(void)
{
    T newlogger;
    return std::move(newlogger);
}

void run(int & a)
{
    printf("run int &a\n");
}

void run(const int & a)
{
    printf("run const int &a\n");
}

void run(int && a)
{
    printf("run int &&a\n");
}

void run(const int && a)
{
    printf("run const int &&a\n");
}

template <typename T>
void Forwarding(T &&t)
{
    run(std::forward<T>(t));
}

int main(int argc, const char *argv[])
{
    // loggerA mylogA;
    // loggerB mylogB;
    // loggerA a = loggerA(mylogA);
    // loggerB b = mylogB;
    // loggerA &c = mylogA;

    // LoggerOperation(mylogA);
    // LoggerOperation(mylogB);

    // auto logger = GetLogger<loggerA>();
    // LoggerOperation(logger);

    // // loggerB b1,b2;
    // // b1 = b2;

    // loggerA a1;
    // loggerA a2(std::move(a1));
    loggerA a;
    int arg = 55;
    const int arg1 = 66;
    
    Forwarding(arg);
    Forwarding(arg1);
    Forwarding(std::move(arg));
    Forwarding(std::move(arg1));
    return 0;
}