#include "LoggingObserver.h"

int main()
{
    
    FakeCommand *test = new FakeCommand();
    fakeOrder *testingOrder = new fakeOrder();

    LogObserver *obs = new LogObserver(test);
    LogObserver *obstwo = new LogObserver(testingOrder);
    

    test->saveCommand();
    testingOrder->execute();
    test->saveCommand();

    delete obs;
    delete obstwo;
    delete test;
    delete testingOrder;

    return 0;
}
