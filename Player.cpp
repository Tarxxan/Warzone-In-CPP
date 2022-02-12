// A player has their own list of orders to be created and executed in the current turn
// The player should contain a method named toDefend() that return a list of territories that are to be defended, as well as a method named
// toAttack() that returns a list of territories that are to be attacked
// Player contains a issueOrder() method that creates an order object and adds it to the list of
// orders.

#include "Player.h"
#include <iostream>
Player::Player() {}; //Default

Player::Player(string player_name) {
    this->name = player_name;
    orders = new OrderList();
}


Player::~Player()
{
    cout << "~Player destructed" << endl;
    delete orders;
      //delete hand;
      //delete territories;
};

Player& Player::operator=(const Player& p) {
    this->name = p.name;
    this->hand = p.hand;
    this->orders = p.orders;
    this->territories = p.territories;
    return *this;
}

Player::Player(const Player& p) {
    this->name = p.name;
    this->hand = p.hand;
    this->orders = p.orders;
    this->territories = p.territories;
}


ostream& operator<<(ostream& out, const Player& p)
{
    out << "Player " << p.name << " details:" << endl;
    //out << "Hand: " << p.hand << endl;
    //out << "List of orders: " << *p.orders << endl;
    out << "List of territories: ";
    for (auto territory : p.territories) {
        out << *territory << endl;
    }
    out << endl;
    return out;
}
// getters

vector <Card*> Player::getHand(){
    return this->hand;
}

OrderList* Player::getOrders() {
    return this->orders;
}


vector <Territory*> Player::getTerritories() {
    return this->territories;
}
string Player::getName() {
    return this->name;
}


// adders

void Player::addTerritory(Territory* territory) {
    territories.push_back(territory);
}

// same as issueOrder... will be deleted later
void Player::addOrder(Order* order) {
    orders->push(order);
}
void Player::issueOrder(Order* order) {
    orders->push(order);
}

void Player::addCard(Card* card) {
    hand.push_back(card);
}
 
vector<Territory*> Player::toDefend() {
    return territories;
}

vector<Territory*> Player::toAttack() {
    vector <Territory*> adjacentTerritoriesNonDup;

    for (auto territory : territories) {
        cout << "Territory have the following adjacents: " << endl;
        vector <Territory*> adjacentTerritories = territory->getAdjacentTerritory();
        for (auto t : adjacentTerritories)
            if (find(adjacentTerritoriesNonDup.begin(), adjacentTerritoriesNonDup.end(), t) != adjacentTerritoriesNonDup.end())
            {
                adjacentTerritoriesNonDup.push_back(t);
            }
    }
    return adjacentTerritoriesNonDup;
}
