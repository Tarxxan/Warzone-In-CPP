#pragma once
#include <list>
#include <string>
using namespace std;

class ILoggable;
class Observer {
    public:
        ~Observer();
        virtual void Update(ILoggable *s) = 0;
    protected:
        Observer();
};

class Subject {
    public:
        virtual void Attach (Observer *observer);
        virtual void Detach (Observer *observer);
        virtual void Notify (ILoggable *s);
        Subject();
        ~Subject();
    private:
        list<Observer*> *observers;
};

class ILoggable {
    public:
        virtual string stringToLog() = 0;
    private:
        string toLog;
};

class LogObserver : public Observer{
    public:
        LogObserver();
        ~LogObserver();
        void Update(ILoggable *s);
        void writeToFile(string s);
        

};

class FakeCommand: public Subject, public ILoggable{

    public:
        FakeCommand();
        ~FakeCommand();
        string stringToLog();
        void saveCommand();
       

};