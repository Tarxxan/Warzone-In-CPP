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

    // Testing valid advance attack order
    t1->setNumberOfArmies(2);
    t2->setNumberOfArmies(8);
    AdvanceOrder* advance = new AdvanceOrder(p1, 2, t1, t2);
    cout << "\n\nTesting valid Advance (attack) Orderwhich should lose: \nAfter creation:\n";
    cout << *advance << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Will now use execute method which should validate and perform attack\n";
    advance->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    // Testing defintely win
    t1->setNumberOfArmies(8);
    t2->setNumberOfArmies(2);
    advance = new AdvanceOrder(p1, 6, t1, t2);
    cout << "\n\nTesting valid Advance (attack) Order which should win: \nAfter creation:\n";
    cout << *advance << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Will now use execute method which should validate and perform attack\n";
    advance->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    // Testing invalid advance order where source doesnt belong to player
    advance = new AdvanceOrder(p2, 6, t1, t2);
    cout << "\n\nTesting invalid Advance Order where source doesnt belong to player: \nAfter creation:\n";
    cout << *advance << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Will now use execute method which should validate and perform attack\n";
    advance->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    // Testing invalid advance order where source doesnt have enough army
    advance = new AdvanceOrder(p1, 6, t1, t2);
    cout << "\n\nTesting invalid Advance Order where source doesnt have enough army: \nAfter creation:\n";
    cout << *advance << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Will now use execute method which should validate and perform attack\n";
    advance->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    // Testing valid advance order to move from one territory to another
    advance = new AdvanceOrder(p1, 1, t1, t2);
    cout << "\n\nTesting valid advance order to move from one territory to another: \nAfter creation:\n";
    cout << *advance << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Will now use execute method which should validate and perform attack\n";
    advance->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    // Testing invalid advance order to move from one territory to non adjacent
    advance = new AdvanceOrder(p1, 1, t1, t4);
    cout << "\n\nTesting invalid advance order to move from one territory to non adjacent: \nAfter creation:\n";
    cout << *advance << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t4 << endl;
    cout << "Will now use execute method which should validate and perform attack\n";
    advance->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t4 << endl;
    delete advance;
    advance = nullptr;
    
    // Testing valid airilift order on adjacent
    AirliftOrder* air = new AirliftOrder(p1, 1, t1, t2);
    cout << "\n\nTesting valid airilift order on adjacent: \nAfter creation:\n";
    cout << *air << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Will now use execute method which should move 1 solder\n";
    air->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    // Testing valid airilift order on non adjacent
    air = new AirliftOrder(p1, 1, t1, t4);
    cout << "\n\nTesting valid airilift order on non adjacent: \nAfter creation:\n";
    cout << *air << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t4 << endl;
    cout << "Will now use execute method which should move 1 solder\n";
    air->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t4 << endl;
    p2->addTerritory(t2);
    // Testing invalid airilift order where source doesnt belong to user
    air = new AirliftOrder(p1, 1, t2, t1);
    cout << "\n\nTesting invalid airilift order where source doesnt belong to user: \nAfter creation:\n";
    cout << *air << endl;
    cout << "The source territory\n";
    cout << *t2 << endl;
    cout << "The destination territory\n";
    cout << *t1 << endl;
    cout << "Will now use execute method which should move 1 solder\n";
    air->execute();
    cout << "The source territory\n";
    cout << *t2 << endl;
    cout << "The destination territory\n";
    cout << *t1 << endl;
    // Testing invalid airilift order where destination doesnt belong to user
    air = new AirliftOrder(p1, 1, t1, t2);
    cout << "\n\nTesting invalid airilift order where destination doesnt belong to user: \nAfter creation:\n";
    cout << *air << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Will now use execute method which should move 1 solder\n";
    air->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    // Testing invalid airilift order where destination doesnt have enough army
    air = new AirliftOrder(p1, 15, t1, t4);
    cout << "\n\nTesting invalid airilift order where destination doesnt have enough army: \nAfter creation:\n";
    cout << *air << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t4 << endl;
    cout << "Will now use execute method which should move 1 solder\n";
    air->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t4 << endl;
    delete air;
    air = nullptr;

    t1->setNumberOfArmies(6);
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

    // Testing valid blockade order
    BlockadeOrder* block = new BlockadeOrder(p1, t1);
    cout << "\n\nTesting valid Blockade Order: \nAfter creation:\n";
    cout << *block << endl;
    cout << "The territory before blockade\n";
    cout << *t1 << endl;
    cout << "Printing the player's territories before blockade\n";
    p1->printTerritories();
    cout << "Will now use execute method which should validate and double the army and set the territory to neutral\n";
    block->execute();
    cout << "Printing the territory\n";
    cout << *t1 << endl;
    cout << "Printing the player's territories\n";
    p1->printTerritories();
    // Testing blockade order with not player's territory
    t1->setOwnerOfTerritory(p2);
    block = new BlockadeOrder(p1, t1);
    cout << "\n\nTesting valid Blockade Order: \nAfter creation:\n";
    cout << *block << endl;
    cout << "The territory before blockade\n";
    cout << *t1 << endl;
    cout << "Printing the player's territories before blockade\n";
    p1->printTerritories();
    cout << "Will now use execute method which should validate and do nothing\n";
    block->execute();
    cout << "Printing the territory\n";
    cout << *t1 << endl;
    cout << "Printing the player's territories\n";
    p1->printTerritories();
    delete block;
    block = nullptr;

    // Testing invalid negotiate order (where both players are the same user)
    NegotiateOrder* neg = new NegotiateOrder(p1, p1);
    cout << "\n\nTesting invalid negotiate order: \nAfter creation:\n";
    cout << *neg << endl;
    cout << "Will now use execute method which should get validated and do nothing\n";
    neg->execute();
    // Testing valid negotiate order
    neg = new NegotiateOrder(p1, p2);
    cout << "\n\nTesting valid negotiate order: \nAfter creation:\n";
    cout << *neg << endl;
    cout << "Will now use execute method which should get validated and set the two players to not attack each other\n";
    neg->execute();
    cout << "Will try to perform attack from p1 to p2" << endl;
    p1->addTerritory(t1);
    p2->addTerritory(t2);
    AdvanceOrder* newAdv = new AdvanceOrder(p1, 1, t1, t2);
    cout << *newAdv << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Executing..." << endl;
    newAdv->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Will try to perform attack from p2 to p1" << endl;
    newAdv = new AdvanceOrder(p2, 1, t2, t1);
    cout << *newAdv << endl;
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;
    cout << "Executing..." << endl;
    newAdv->execute();
    cout << "The source territory\n";
    cout << *t1 << endl;
    cout << "The destination territory\n";
    cout << *t2 << endl;

    delete newAdv;
    delete neg;
    newAdv = nullptr;
    neg = nullptr;

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

// g++ "OrdersDriver.cpp" "Orders.cpp" "Player.cpp" "Map.cpp" "Cards.cpp" "LoggingObserver.cpp" -o "orders.exe"
