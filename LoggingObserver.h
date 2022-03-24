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
    ~LogObserver();
    void Update(ILoggable *s);
    void writeToFile(string s);
private:
    Subject *subject;
};

class FakeCommand : public Subject, public ILoggable
{

public:
    FakeCommand();
    ~FakeCommand();
    string stringToLog();
    void saveCommand();
};

class fakeOrder : public Subject, public ILoggable
{
public:
    fakeOrder();
    ~fakeOrder();
    string stringToLog();
    void execute();
};