
#include "LoggingObserver.h"
#include "Orders.h"
#include "GameEngine.h"
#include "CommandProcessor.h"
#include "Player.h"
int main()
{
    Player *p = new Player();
    Territory *t = new Territory();
    CommandProcessor *cp = new CommandProcessor();
    OrderList *ol = new OrderList();
    // GameEngine *ge = new GameEngine();
    Command *comm = new Command("TEST COMMAND");
    BombOrder *bo = new BombOrder(p,t);


    FakeCommand *test = new FakeCommand();
    fakeOrder *testingOrder = new fakeOrder();

    // LogObserver *obs = new LogObserver(cp);
    // LogObserver *ob2 = new LogObserver(ol);
    // // LogObserver *ob3 = new LogObserver(ge);
    // LogObserver *ob4 = new LogObserver(comm);
    // LogObserver *ob5 = new LogObserver(bo);
    
    cp->getCommand("start");
    ol->push(bo);
    bo->execute();
    cp->getCommand("test command");
    comm->saveEffect("TEST EFFECT");
    // ge->transition("TEST STATE");

    delete p;
    delete t;
    delete cp;
    delete ol;
    // delete ge;
    delete comm;
    delete bo;




    return 0;
}
