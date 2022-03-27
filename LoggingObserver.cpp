#include "LoggingObserver.h"
#include <iostream>
#include <fstream>
using namespace std;

Observer::Observer(){};       //Default Constructor and Destructor for the base Observer

Observer::~Observer(){
};

Subject::Subject()          //Default Constructor and Destructor for the base Subject
{
    observers = new list<Observer *>;
}

Subject::~Subject()
{
    delete observers;
}

void Subject::Attach(Observer *observer)             //methods to attach or detach an observer from the list of observers
{
    observers->push_back(observer);
}

void Subject::Detach(Observer *observer)
{
    observers->remove(observer);
}

void Subject::Notify(ILoggable *s)                  //Notify the observer to log a string into the gamelog
{
    list<Observer *>::iterator i = observers->begin();
    for (; i != observers->end(); ++i)
    {
        (*i)->Update(s);
    }
}

LogObserver::LogObserver(){};                     //Default and parametized constructor for the derived Observer class
LogObserver::LogObserver(Subject *s){
    subject = s;
    subject->Attach(this);
}
LogObserver::LogObserver(const LogObserver &o){   // Copy Constructor for the derived Observer
    subject = o.subject;
    subject->Attach(this);
}
LogObserver::~LogObserver(){                      //Deconstructor for the derived Observer
    subject->Detach(this);
};

void LogObserver::writeToFile(string s)          //method that writes the string provided by subject/ILoggable classes to the gamelog
{
    ofstream logfile;
    logfile.open("gamelog.txt", std::ios_base::app);
    logfile << s << '\n';
    logfile.close();
}
void LogObserver::Update(ILoggable *s)           //method called by the Subject to enable writing to the gamelog
{
    writeToFile(s->stringToLog());
}


