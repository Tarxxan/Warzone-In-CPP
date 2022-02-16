#pragma once
using namespace std;
#include <string>
#include <vector>
#include <math.h> 
#include <algorithm>

// -----------------------------Dummy class for Territory-------------------------------------------
class Territory {
public:
    Territory();
    ~Territory();
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

// -----------------------------Dummy class for Order-------------------==------------------------
class Order {
public:
    Order();
    ~Order();
protected:
    string name;
};

// -----------------------------Dummy class for OrderList-------------------------------------------
class OrderList {
public:
    // Empty Constructor
    OrderList();
    ~OrderList();
    // Inserts an order at the end (as they supposed to)
    vector <Order*> getOrders();
    void push(Order* order);
    // comparing pointers of 
private:
    vector <Order*> orderList;
};

// -----------------------------Dummy class for DeployOrder-------------------------------------------
class DeployOrder : public Order {
public:
    DeployOrder(int numOfArmies, Territory* destination); // Parameter Constructor
    ~DeployOrder();
   private:
    // Data members
    int armies;
    Territory* destination;
};

// -----------------------------Dummy class for BombOrder---------------------------------------------
class BombOrder : public Order {
public:
    BombOrder(Territory* destination);  // Parameter constructor
    ~BombOrder();
   private:
    // Data members
    Territory* destination;
};

// -----------------------------Dummy class for Card--------------------------------------------------
class Card {
public:
    Card(string type);
    ~Card();
    friend ostream& operator << (ostream& out, const Card&);
private:
    string type;
};


// -----------------------------Dummy class for Hand--------------------------------------------------
class Hand {
public:
    Hand();
    ~Hand();
    vector <Card*> getHand();
    void pushCard(Card* card);

    friend std::ostream& operator << (ostream& out, const Hand& ol);
    
private:
    vector <Card*> hand;
};



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