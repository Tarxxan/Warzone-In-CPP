#pragma once
#include <list>
#include <string>
using namespace std;

class ILoggable;

class Observer
{
public:
    virtual ~Observer();
    virtual void Update(ILoggable *s) = 0;

protected:
    Observer();
};

class Subject
{
public:
    virtual void Attach(Observer *observer);
    virtual void Detach(Observer *observer);
    virtual void Notify(ILoggable *s);
    Subject();
    virtual ~Subject();

private:
    list<Observer *> *observers;
};

class ILoggable
{
public:
    virtual string stringToLog() = 0;

private:
    string toLog;
};

class LogObserver : public Observer
{
public:
    LogObserver();
    LogObserver(Subject *s);
    LogObserver(const LogObserver &o);
    ~LogObserver();
    void Update(ILoggable *s);
    void writeToFile(string s);
private:
    Subject *subject;
};
