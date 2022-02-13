// Driver creates players and demonstrates that the above features are available. 

#include "Player.h"
#include <iostream>

int main() {
    Player* p = new Player("Jack");
    
    Territory* t0 = new Territory(1, "Labrador", "Canada", 10, vector<Territory*>());
    Territory* t1 = new Territory(2, "Ontario", "Canada", 8, vector<Territory*>());
    Territory* t2 = new Territory(0, "Quebec", "Canada", 1, vector<Territory*>() = {t0,t1});
    t0->addAdjacentTerritory(t2);
    t1->addAdjacentTerritory(t2);
    p->addTerritory(t2);

    DeployOrder* deploy = new DeployOrder(5, t1);
    BombOrder* bomb = new BombOrder(t1);
    cout << "Issuing the orders" << endl;
    p->issueOrder(deploy);
    p->issueOrder(bomb);

    cout << *p << endl;
    
    cout << "Computing how many armies to be assigned" << endl;
    p->computeAvailableArmies();
    cout << p->getAvailableArmies() << " armies can be assigned\n\n" << endl;

    for (Territory* territory : p->toDefend()) {
        cout << *territory << endl;
    }

    for (Territory* territory : p->toAttack()) {
        cout << *territory << endl;
    }
    
    return 0;
}