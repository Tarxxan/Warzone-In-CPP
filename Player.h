#pragma once
using namespace std;
#include <string>
#include "Map.h"
#include "Orders.h"
#include "Cards.h"

#include <vector>

class Card;
class OrderList;
class Hand;
class Territory;
class Order;

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
    int getAvailableArmies();

    friend ostream& operator<<(ostream& out, const Player& player);
    
    void addCard(Card* card);
    void addTerritory(Territory* territory);
    void addOrder(Order* order);
    // //member functions
    void computeAvailableArmies();
    vector <Territory*> toDefend(); // return a list of territories that are to be defended
    vector <Territory*> toAttack(); //  returns a list of territories that are to be attacked
    //                             // establish an arbitrary list of territories to be defended, and an
    //                             // arbitrary list of territories that are to be attacked.
    void issueOrder(Order* order);   //creates an Order object and puts it in the player�s list of orders.
    void advance(Territory* from, Territory* to);

private:
    OrderList* orders;
    vector <Territory*> territories;
    vector <Card*> hand;
    string name;
    int availableArmies;
};