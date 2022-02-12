#pragma once
using namespace std;
#include <string>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

#include <vector>

class Order;
class Card;
class OrderList;
class Hand;
class Territory;

class Player {
public:
    Player(); //Default Constructor
    Player(string player_name);
    ~Player();
    Player(const Player& p);
    Player& operator=(const Player& order);

    //getters
  //  vector <Card*> getHand();
    OrderList* getOrders();
    vector <Territory*> getTerritories();
    string getName();
    vector <Card*> getHand();

    friend ostream& operator<<(ostream& output, const Player& Player);
    void addCard(Card* card);
    void addTerritory(Territory* territory);
    void addOrder(Order* order);
    // //member functions
    vector <Territory*> toDefend(); // return a list of territories that are to be defended
    vector <Territory*> toAttack(); //  returns a list of territories that are to be attacked
    //                             // establish an arbitrary list of territories to be defended, and an
    //                             // arbitrary list of territories that are to be attacked.
    void issueOrder(Order* order);   //creates an Order object and puts it in the player�s list of orders.


private:
    OrderList* orders;
    vector <Territory*> territories;
    vector <Card*> hand;
    string name;
};
