#include "LoggingObserver.h"
#include <iostream>
#include <fstream>
using namespace std;

Observer::Observer(){};

Observer::~Observer(){
};

Subject::Subject()
{
    observers = new list<Observer *>;
}

Subject::~Subject()
{
    delete observers;
}

void Subject::Attach(Observer *observer)
{
    observers->push_back(observer);
}

void Subject::Detach(Observer *observer)
{
    observers->remove(observer);
}

void Subject::Notify(ILoggable *s)
{
    list<Observer *>::iterator i = observers->begin();
    for (; i != observers->end(); ++i)
    {
        (*i)->Update(s);
    }
}

LogObserver::LogObserver(){};
LogObserver::LogObserver(Subject *s){
    subject = s;
    subject->Attach(this);
}
LogObserver::LogObserver(const LogObserver &o){
    subject = o.subject;
    subject->Attach(this);
}
LogObserver::~LogObserver(){
    subject->Detach(this);
};

void LogObserver::writeToFile(string s)
{
    ofstream logfile;
    logfile.open("gamelog.txt", std::ios_base::app);
    logfile << s << '\n';
    logfile.close();
}
void LogObserver::Update(ILoggable *s)
{
    writeToFile(s->stringToLog());
}


