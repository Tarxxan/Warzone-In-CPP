#pragma once
using namespace std;
#include <string>
#include <vector>
#include <math.h> 
#include <algorithm>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"

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

// -------------------------------------------Player--------------------------------------------------
class Player {
public:
    //Constructors
    Player(); 
    Player(string player_name);
    ~Player();
    Player(const Player& p);
    Player& operator=(const Player& order);

    //getters
    Hand* getPlayerHand();
    OrderList* getOrders();
    vector <Territory*> getTerritories();
    string getName();
    int getAvailableArmies();

    friend ostream& operator<<(ostream& out, const Player& player);
    
    //adders
    void addCard(Card* card);
    void addTerritory(Territory* territory);
    void addOrder(Order* order);
    void removeSolders(int amount);

    // //member functions
    void computeAvailableArmies();
    vector <Territory*> toDefend(); // return an arbitrary list of territories to be defended
    vector <Territory*> toAttack(); // returns arbitrary list of territories that are to be attacked.
    void issueOrder(Order* order);  // creates an Order object and puts it in the player's list of orders.
    void advance(Territory* from, Territory* to);

private:
    OrderList* orders;
    vector <Territory*> territories;
    Hand* playerHand;
    string name;
    int availableArmies;
};