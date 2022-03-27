// Driver creates players and demonstrates that the above features are available. 
/*
#include "Player.h"
#include <iostream>
class Card;
class Territory;
class Order;
class OrderList;
class Hand;
class Deck;
class DeployOrder;
class AdvanceOrder;
class NegotiateOrder;
class BombOrder;
class BlockadeOrder;
class AirliftOrder;

int main() {
    Player* p1 = new Player("Jack");
    Player* p2 = new Player("Annie");

    Card* c = new Card("bomb");
    Card* c2 = new Card("airlift");
    Card* c3 = new Card("blockade");

    p1->addCard(c);
    p1->addCard(c2);
    p2->addCard(c2);

    Territory* t0 = new Territory(1, "Labrador", "Canada", 10, vector<Territory*>());
    Territory* t1 = new Territory(2, "Ontario", "Canada", 8, vector<Territory*>());
    Territory* t2 = new Territory(0, "Quebec", "Canada", 1, vector<Territory*>() = {t0,t1});
    Territory* t4 = new Territory(3, "Yukon", "Canada", 1, vector<Territory*>());
    Territory* t5 = new Territory(4, "Alaska", "Canada", 2, vector<Territory*>());

    t0->addAdjacentTerritory(t2);
    t1->addAdjacentTerritory(t2);
    t4->addAdjacentTerritory(t5);
    t5->addAdjacentTerritory(t4);

    t2->addAdjacentTerritory(t4);
    t4->addAdjacentTerritory(t2);

    p1->addTerritory(t2);
    p1->addTerritory(t4);

    p2->addTerritory(t0);
    p2->addTerritory(t1);
   

    cout << "Computing how many armies to be assigned" << endl;
    p1->computeAvailableArmies();
    cout << p1->getAvailableArmies() << " armies can be assigned\n\n" << endl;

    // Check what players it hsould have
   // DeployOrder* deploy = new DeployOrder(p1, 5, t1);
   // BombOrder* bomb = new BombOrder(p1, t1);
    cout << "Issuing the orders" << endl;
    p1->issueOrder();
   

    //cout << *p1 << endl;
    

    system("pause");
    delete p1;

}*/