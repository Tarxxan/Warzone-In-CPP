// Driver creates players and demonstrates that the above features are available. 

#include "Player.h"
#include <iostream>

int main() {
    Player* p = new Player("Test");
    Order* o = new Order();
    Territory* t0 = new Territory(1, "Labrador", "Canada", 10, vector<Territory*>());
    Territory* t1 = new Territory(2, "Ontario", "Canada", 8, vector<Territory*>());
    Territory* t2 = new Territory(0, "Quebec", "Canada", 1, vector<Territory*>() = {t0,t1});
    t0->addAdjacentTerritory(t2);
    t1->addAdjacentTerritory(t2);
    p->addTerritory(t2);

    OrderList orders;
    AirliftOrder* dep = new AirliftOrder(p, 1, t1, t2);
    cout << "creating orders" << endl;
    orders.push(dep);
    cout << orders << endl;
    orders.moveDown(dep);
    cout << orders << endl;
    orders.remove(dep);

    cout << "Issuing the orders" << endl;
    p->issueOrder(o);
    
    cout << *p << endl;

    for (Territory* territory : p->toDefend()) {
        cout << *territory << endl;
    }

    for (Territory* territory : p->toAttack()) {
        cout << *territory << endl;
    }

    return 0;
}