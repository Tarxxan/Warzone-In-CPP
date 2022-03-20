#include "LoggingObserver.h"


int main()
{
    LogObserver *obs = new LogObserver();
    FakeCommand *test = new FakeCommand();
    test->Attach(obs);

    test->saveCommand();
    
    delete obs;
    delete test;



    return 0;
}
