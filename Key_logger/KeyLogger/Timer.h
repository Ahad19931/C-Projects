#ifndef TIMER_H
#define TIMER_H
#include <thread>
#include <chrono>
#include <functional>

class Timer
{
    std::thread Thread;
    bool Alive=false;
    long Callnumber=-1L;
    long repeat_count=-1L;
    std::chrono::milliseconds interval=std::chrono::milliseconds(0);
    std::function<void(void)> funct=nullptr;

    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);
        if(Alive)
            Function()();
    }
    void ThreadFunc()
    {
        if(Callnumber==infinite)
        {
            while(Alive)
                SleepAndRun();
        }
        else
        {
            while(repeat_count--)
                SleepAndRun();
        }
    }
public:
    static const long infinite=-1L;
    Timer(){}
    Timer(const std::function<void(void)> &f)
        :funct(f){}
    Timer(const std::function<void(void)> &f,const unsigned long &i,const long repeat=Timer::infinite)
        :funct(f),interval(std::chrono::milliseconds(i)),Callnumber(repeat){}
    void Start(bool Async=true)
    {
        if(isAlive())
            return;
        Alive=true;
        repeat_count=Callnumber;
        if(Async)
            Thread=std::thread(ThreadFunc,this);
        else
            this->ThreadFunc();
    }
    void Stop()
    {
        Alive=false;
        Thread.join();
    }
    void SetFunction(const std::function<void(void)> &f)
    {
        funct=f;
    }
    bool isAlive() const{ return Alive; }
    void RepeatCount(const long r)
    {
        if(Alive)
            return;
        Callnumber=r;
    }
    long GetLeftCount() const{ return repeat_count; }
    long RepeatCount() const { return Callnumber; }
    void SetInterval(const unsigned long &i)
    {
        if(Alive)
            return;
        interval=std::chrono::milliseconds(i);
    }
    unsigned long Interval() const{ return interval.count(); }
    const std::function<void(void)> &Function() const
    {
        return funct;
    }
};

#endif // TIMER_H
