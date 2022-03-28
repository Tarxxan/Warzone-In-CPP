#pragma once
#include <list>
#include <string>
using namespace std;

class ILoggable;

class Observer
{
public:
    virtual ~Observer();                            //Destructor
    virtual void Update(ILoggable *s) = 0;          // Update method to be overridden

protected:
    Observer();                                    //Constructor
};

class Subject
{
public:
    virtual void Attach(Observer *observer);       //insert observer into list
    virtual void Detach(Observer *observer);       //remove observer from list
    virtual void Notify(ILoggable *s);             //notify observers in list
    Subject();                                     //constructor
    virtual ~Subject();                            //destructor

private:
    list<Observer *> *observers;                   //list of observers
};

class ILoggable                                   
{
public:
    virtual string stringToLog() = 0;             //method to be overridden 

};

class LogObserver : public Observer               
{
public:
    LogObserver();                                  //Default Constructor
    LogObserver(Subject *s);                        //Parameterized Constructor
    LogObserver(const LogObserver &o);              //copy Constructor
    ~LogObserver();                                 //Destructor
    void Update(ILoggable *s);                      //trigger write to file
    void writeToFile(string s);                     //write to gamelog
private:
    Subject *subject;                               //subject using this observer
};
