
#include "LoggingObserver.h"
#include "Orders.h"
#include "GameEngine.h"
#include "CommandProcessor.h"
#include "Player.h"
int main()
{

    //Initialize all the objects that use the Observer pattern
    vector<Territory*> terrs;

    Player *p = new Player("Joe");
    Territory *t = new Territory(1,"TestLand","TestContinent",5,terrs);
    CommandProcessor *cp = new CommandProcessor();
    OrderList *ol = new OrderList();
    GameEngine *ge = new GameEngine();
    Command *comm = new Command("TEST COMMAND");
    BombOrder *bo = new BombOrder(p,t);


    //Call all the methods in each object that would use *NOTIFY* and trigger the Observer

    cp->getCommand("start");
    ol->push(bo);
    bo->execute();
    cp->getCommand("test command");
    comm->saveEffect("TEST EFFECT");
    ge->transition("TEST STATE");

   
    delete cp;
    delete ol;
    delete ge;
    delete comm;
    




    return 0;
}
