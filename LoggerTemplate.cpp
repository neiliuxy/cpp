#include <memory>
class sink
{
public:
    virtual void sink_it() = 0;
};
class sinkA : public sink
{
public:
    void sink_it()
    {
        printf("sinkA_it!\n");
    }
};
class sinkB : public sink
{
public:
    void sink_it()
    {
        printf("sinkB_it");
    }
};

template <typename T>
class logger
{
private:
    // logger()
    // {

    // }
    // ~logger()
    // {

    // }
    //static logger * log;
    static std::shared_ptr<logger> log;
    static std::shared_ptr<T> sink_;

public:
    static std::shared_ptr<logger> Instance(void)
    {
        if (log == nullptr)
        {
            log = std::make_shared<logger>();
            sink_ = std::make_shared<T>();
        }
        return log;
    }

    void logit()
    {
        logger::sink_->sink_it();
    }

    // static logger *Instance(void)
    // {
    //     if (log == nullptr)
    //     {
    //         log = new logger();
    //     }
    //     return log;
    // }
};

//logger *logger::log = nullptr;
template <typename T>
std::shared_ptr<logger<T>> logger<T>::log;
template <typename T>
std::shared_ptr<T> logger<T>::sink_;

int main(int argc, const char *argv[])
{
    std::shared_ptr<logger<sinkA>> mylog = logger<sinkA>::Instance();
    mylog->logit();
    std::shared_ptr<logger<sinkA>> mylog1 = logger<sinkA>::Instance();
    mylog1->logit();
    return 0;
}