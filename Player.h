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
    Player(int id, string player_name);
    Player(std::list<Order> orders, std::list<Territory> territories, std::list<Card> cards);
    friend ostream& operator<<(ostream& output, const Player& Player); 
    
    //member functions
    list<Territory> toDefend(); // return a list of territories that are to be defended
    list<Territory> toAttack(); //  returns a list of territories that are to be attacked
                                // establish an arbitrary list of territories to be defended, and an
                                // arbitrary list of territories that are to be attacked.
    void issueOrder();   //creates an Order object and puts it in the player�s list of orders.
    bool addPlayerTerritories(Territory t);  // return true if territory is successfully added

    //getters
    list<Card> getPlayerCards();
    list<Order> getPlayerOrders();
    list<Territory> getPlayerTerritories();
    string getPlayerName();
    int getPlayerID();  
    

private:
    std::list<Order> playerOrders;
    std::list<Territory> playerTerritories;
    std::list<Card> playerCards;
    int playerID;
    string playerName;
};
