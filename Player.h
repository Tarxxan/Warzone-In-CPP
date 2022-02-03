#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"

using namespace std;
using std::list;

class Player {
   

public:
    Player(); //Default Constructor
    ~Player();
    Player(std::list<Order> orders, std::list<Territory> territories, std::list<Card> cards);
    friend ostream& operator<<(ostream& output, const Player& Player); // Stream insertion operator <<  // This is made friend to access private members of Territory
    
    //member functions
    list<Order> getOrders();
    list<Territory> getTerritories();
    list<Card> getCards();
    list<Territory> toDefend(); // return a list of territories that are to be defended
    list<Territory> toAttack(); //  returns a list of territories that are to be attacked
                                // establish an arbitrary list of territories to be defended, and an
                                // arbitrary list of territories that are to be attacked.
    void issueOrder(string new_order);   //creates an Order object and puts it in the player’s list of orders.
    


private:
    std::list<Order> orders;
    std::list<Territory> territories;
    std::list<Card> cards;

};
