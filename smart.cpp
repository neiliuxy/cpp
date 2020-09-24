#include <stdio.h>

#include <utility>
#include <vector>
#include <memory>
class basedata
{
public:
    int a;

    basedata()
    {
        a = 0;
        printf("basedata constructor!\n");
    }
    virtual ~basedata() { printf("basedata destroy!\n"); }
};

class childdata : public basedata
{
public:
    int b;

    childdata()
    {
        b = 0;
        printf("childdata constructor!\n");
    }
    ~childdata() { printf("childdata destroy!\n"); }
};
class datacount
{
public:
    datacount() : count(1) {}

    int getcount() { return count; }
    void addcount() { count++; }
    int decount()
    {
        count--;
        return count;
    }

private:
    int count;
};

class dataptr
{
public:
    dataptr(basedata *ptr)
    {
        p = ptr;
        count = new datacount();
        printf("dataptr(basedata *ptr) p is %d\n", p);
        printf("count p is %d\n", count->getcount());
    }
    dataptr(dataptr &&other)
    {
        p = other.p;

        printf("dataptr(dataptr &other) move p is %d\n", p);
        if (p)
        {
            other.count->addcount();
            count = other.count;
            other.reset();
        }
    }
    dataptr(const dataptr &other)
    {
        p = other.p;
        printf("dataptr(dataptr &other) copy p is %d\n", p);
        if (p)
        {
            other.count->addcount();
            count = other.count;
            printf("count p is %d\n", count->getcount());
        }
    }
    ~dataptr()
    {
        count->decount();
        printf("~dataptr() p is %d\n", p);
        printf("count p is %d\n", count->getcount());
        if (p && (count->getcount() == 0))
        {
            delete p;
            delete count;
            p = nullptr;
            printf("~dataptr() delete\n");
        }
    }

    basedata *get()
    {
        printf("get() p is %d\n", p);
        return p;
    }
    void reset()
    {

        p = nullptr;
        printf("reset() p is %d\n", p);
    }

private:
    basedata *p;
    datacount *count;
};
typedef std::shared_ptr<basedata> shareddata;
class base
{
public:
    base() { printf("base constructor!\n"); }
    virtual ~base() { printf("base destroy!\n"); }

    virtual basedata *getdata() = 0;
    virtual void putdata(basedata *data) = 0;
    virtual void processdata(basedata *data) = 0;
    virtual void finish(basedata *data) = 0;

    std::vector<dataptr> datas;
    std::vector<shareddata> shareddatas;

    void process(void)
    {
        printf("process\n");
        printf("dataptr manager\n");
        basedata *data = getdata();
        dataptr smart(data);
        processdata(smart.get());
        putdata(smart.get());
        datas.push_back(std::move(smart));
        printf("shared_ptr manager\n");
        basedata *sdata = getdata();
        shareddata sdataptr = std::make_shared<basedata>(*sdata);
        processdata(sdataptr.get());
        putdata(sdataptr.get());
        shareddatas.push_back(sdataptr);
        printf("process over\n");
    }
    void terminate(void)
    {
        printf("terminate()\n");
        printf("dataptr manager\n");
        for (auto iter : datas)
        {
            finish(iter.get());
        }
        printf("shared_ptr manager\n");
        for (auto iter : shareddatas)
        {
            finish(iter.get());
        }
         printf("terminate() over\n");
    }
};

class child : public base
{
public:
    child() { printf("child constructor!\n"); }
    ~child() { printf("child destroy!\n"); }

    basedata *getdata()
    {
        return new childdata();
    }
    void putdata(basedata *data)
    {
        childdata *childd = (childdata *)data;
        printf("putdata data=%d\n", data);
        printf("putdata data->b=%d\n", childd->b);
        childd->b++;
    }
    void processdata(basedata *data)
    {
        printf("processdata data=%d\n", data);
        printf("processdata data->a=%d\n", data->a);

        data->a++;
    }
    void finish(basedata *data)
    {
        childdata *childd = (childdata *)data;
        printf("finish data=%d\n", data);
        printf("finish data->a=%d\n", childd->a);
        printf("finish data->b=%d\n", childd->b);
        //delete data;
    }
};

int main(int argc, char *argv[])
{
    base *pb = new child();

    pb->process();
    pb->terminate();
    printf("delete pb below\n");
    delete pb;

    return 0;
}