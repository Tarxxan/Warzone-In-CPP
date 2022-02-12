// Driver creates players and demonstrates that the above features are available. 

#include <iostream>
#include "Player.h"
/*
int main() {
    Player* p = new Player("Will");
    Territory* t1 = new Territory();
    Territory* t2 = new Territory();
    t1->setNumberOfArmies(10);
    t2->setNumberOfArmies(20);
    t1->addAdjacentTerritory(t2);
    
    Order* o = new Order();
    //p->issueOrder(o);
    p->addTerritory(t1);
    p->addTerritory(t2);
    
    for(Territory *t : p->getTerritories()) {
        for (Territory* adj : t->getAdjacentTerritory()) {
            cout << adj << endl;
        }
    }
    //cout << p->getTerritories() << endl;
    //cout << p->getOrders() << endl;
    cout << "Currently have " << p->toDefend().size() << " Territories to defend" << endl;
    cout << "Currently have " << p->toAttack().size() << " Territories to attack" << endl;
    
    return 0;
}*/