#pragma once
using namespace std;
#include <string>
#include <vector>

// Dummy classes for Territory, Order, Card, DeployOrder, BombOrder
class Territory {
public:
    Territory();
    Territory(int territoryId, string territoryName, string continentName, int numberOfArmies, vector<Territory*> adjacentTerritories);
    vector<Territory*> getAdjacentTerritory();
    void addAdjacentTerritory(Territory* t);
    friend ostream& operator<<(ostream& output, const Territory& territory);
private:
    int territoryId;
    string territoryName;
    string continentName;
    int numberOfArmies;
    vector<Territory*> adjacentTerritories; // Store adjacent territory pointers in vector.
};

class Order {
public:
    Order();
protected:
    string name;
};

class OrderList {
public:
    // Empty Constructor
    OrderList();
    // Inserts an order at the end (as they supposed to)
    vector <Order*> getOrders();
    void push(Order* order);
    // comparing pointers of 
private:
    vector <Order*> orderList;
};

class DeployOrder : public Order {
public:
    DeployOrder(int numOfArmies, Territory* destination); // Parameter Constructor
   private:
    // Data members
    int armies;
    Territory* destination;
};
class BombOrder : public Order {
public:
    BombOrder(Territory* destination);  // Parameter constructor
   private:
    // Data members
    Territory* destination;
};


class Card {
public:
    Card(string type);
private:
    string type;
};





class Player {
public:
    Player(); //Default Constructor
    Player(string player_name);
    ~Player();
    Player(const Player& p);
    Player& operator=(const Player& order);

    //getters
    vector <Card*> getHand();
    OrderList* getOrders();
    vector <Territory*> getTerritories();
    string getName();
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