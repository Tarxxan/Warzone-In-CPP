// Driver that creates orders of every kind, places them in an OrdersList object, and
// demonstrates that the above features are available. 

#include <iostream>
#include "Orders.h"
#include <memory>
using namespace std;


int main() {
    Player* p1 = new Player("Tom");
    Player* p2 = new Player("John");
    
    vector<Territory*> list1;
    vector<Territory*> list2;
    vector<Territory*> list3;
    vector<Territory*> list4;

    Territory* t1 = new Territory(1, "Australia", "Oceanie", 5, list1);
    Territory* t2 = new Territory(2, "Canada", "America", 3, list2);
    Territory* t3 = new Territory(3, "United States", "America", 6, list3);
    Territory* t4 = new Territory(4, "China", "Asia", 2, list4);
    
    // Link A & B
    t1->addAdjacentTerritory(t2);
    t2->addAdjacentTerritory(t1);
    // A & C
    t1->addAdjacentTerritory(t3);
    t3->addAdjacentTerritory(t1);
    // A & D belong to Tom
    p1->addTerritory(t1);
    p1->addTerritory(t4);
    // B & C belong to John
    p2->addTerritory(t2);
    p2->addTerritory(t3);
    // Add players army
    p1->computeAvailableArmies();
    p2->computeAvailableArmies();


    // Testing valid deploy order
    DeployOrder* deploy = new DeployOrder(p1, 1, t1);
    cout << "Testing valid Deploy Order: \nAfter creation:\n";
    cout << *deploy << endl;
    cout << "The territory before deploy of 1 extra solder\n";
    cout << *t1 << endl;
    cout << "Will now use execute method which should validate and add 1 extra solder\n";
    deploy->execute();
    cout << "Printing the territory\n";
    cout << *t1 << endl;
    // Testing deploy order when the territory doesnt belong to user
    deploy = new DeployOrder(p2, 1, t1);
    cout << "Testing deploy order when the territory doesnt belong to user: \nAfter creation:\n";
    cout << *deploy << endl;
    cout << "The territory before deploy of 1 extra solder\n";
    cout << *t1 << endl;
    cout << "Will now use execute method which should validate and not add 1 extra solder\n";
    deploy->execute();
    cout << "Printing the territory\n";
    cout << *t1 << endl;
    // Testing deploy order when use does not have enough army
    deploy = new DeployOrder(p1, 6, t1);
    cout << "Testing deploy order when the territory doesnt belong to user: \nAfter creation:\n";
    cout << *deploy << endl;
    cout << "The territory before deploy of 1 extra solder\n";
    cout << *t1 << endl;
    cout << "Will now use execute method which should validate and not add 1 extra solder\n";
    deploy->execute();
    cout << "Printing the territory\n";
    cout << *t1 << endl;
    delete deploy;
    deploy = nullptr;

    // TODO: Advance & Airlift
    // AdvanceOrder* advance = new AdvanceOrder(p1, 5, t1, t2);
    // cout << "\n\nTesting Advance Order: \nAfter creation:\n";
    // cout << *advance << endl;
    // cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    // advance->execute();
    // cout << "Printing the order: \n";
    // cout << *advance << endl;
    // AirliftOrder* air = new AirliftOrder(p1, 5, t1, t2);
    // cout << "\n\nTesting Airlift Order: \nAfter creation:\n";
    // cout << *air << endl;
    // cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    // air->execute();
    // cout << "Printing the order: \n";
    // cout << *air << endl;

    // Testing valid bomb order
    BombOrder* bomb = new BombOrder(p2, t1);
    cout << "\n\nTesting valid Bomb Order: \nAfter creation:\n";
    cout << *bomb << endl;
    cout << "The territory before bombing\n";
    cout << *t1 << endl;
    cout << "Will now use execute method which should validated and remove half of the army \n";
    bomb->execute();
    cout << "Printing the territory\n";
    cout << *t1 << endl;
    // Testing bomb order on the territory belonging to user
    bomb = new BombOrder(p1, t1);
    cout << "\nTesting bomb order on the territory belonging to user: \nAfter creation:\n";
    cout << *bomb << endl;
    cout << "The territory before bombing\n";
    cout << *t1 << endl;
    cout << "Will now use execute method which should validated and not remove half of the army \n";
    bomb->execute();
    cout << "Printing the territory\n";
    cout << *t1 << endl;
    // Testing bomb order on the territory not adjacent to user's territories
    bomb = new BombOrder(p2, t4);
    cout << "\nTesting bomb order on the territory not adjacent to user's territories: \nAfter creation:\n";
    cout << *bomb << endl;
    cout << "The territory before bombing\n";
    cout << *t1 << endl;
    cout << "Will now use execute method which should validated and not remove half of the army \n";
    bomb->execute();
    cout << "Printing the territory\n";
    cout << *t1 << endl;
    delete bomb;
    bomb = nullptr;

    // BlockadeOrder* block = new BlockadeOrder(p1, t1);
    // cout << "\n\nTesting Blockade Order: \nAfter creation:\n";
    // cout << *block << endl;
    // cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    // block->execute();
    // cout << "Printing the order: \n";
    // cout << *block << endl;

    // NegotiateOrder* neg = new NegotiateOrder(p1, p2);
    // cout << "\n\nTesting Negotiate Order: \nAfter creation:\n";
    // cout << *neg << endl;
    // cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    // neg->execute();
    // cout << "Printing the order: \n";
    // cout << *neg << endl;

    cout << "Desctructing players and territories\n";
    delete p1;
    p1 = nullptr;
    delete p2;
    p2 = nullptr;
    delete t1;
    t1 = nullptr;
    delete t2;
    t2 = nullptr;
    delete t3;
    t3 = nullptr;
    delete t4;
    t4 = nullptr;
    system("pause");
    
}

// g++ "OrdersDriver.cpp" "Orders.cpp" -o "orders.exe"
