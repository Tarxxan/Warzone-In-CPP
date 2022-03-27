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
    void printOwnedTerritories();
    void removeSolders(int amount);
    void removeTerritory(Territory* t);
    void drawCard(); // TODO: Should draw card from the deck and call addCard(card) not sure where we want to locate the deck
    void setAvailableArmies(int i);
    void addAvailableArmies(int n);
    // //member functions
    void computeReinforcementPool();
    vector <Territory*> toDefend(); // return an arbitrary list of territories to be defended
    vector <Territory*> toAttack(); // returns arbitrary list of territories that are to be attacked.
    void issueOrder();  // creates an Order object and puts it in the player's list of orders.
    void advance();
    void defend();
    void useCard();
    void negotiatePlayer(Player* enemy);
    void deleteNegotiate(Player* enemy);
    bool canAttack(Player* enemy);

private:
    OrderList* orders;
    vector <Territory*> territories;
    Hand* playerHand;
    string name;
    int availableArmies;
    vector <Player*> cannotAttack;
};