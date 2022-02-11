// A player has their own list of orders to be created and executed in the current turn
// The player should contain a method named toDefend() that return a list of territories that are to be defended, as well as a method named
// toAttack() that returns a list of territories that are to be attacked
// Player contains a issueOrder() method that creates an order object and adds it to the list of
// orders.
 
#include "Player.h"

#include <iostream>
Player::Player() {}; //Default
 
Player::Player(int id, string player_name) {
    this->id = id;
    this->name = player_name;
}
 
Player::Player(int id, string name, OrderList* orders, vector <Card*> hand, vector <Territory*> territories){
    this->id = id;
    this->name = name;
    this->hand = hand;
    this->territories = territories;
    this->orders = new OrderList();
 
}
 
Player::~Player()
{
    cout << "~Player destructed" << endl;
    delete orders;
    //delete hand;
    //delete territories;
};
 
Player& Player::operator=(const Player& p){
    this->name = p.name;
    this->id = p.id;
    this->hand = p.hand;
    this->orders = p.orders;
    this->territories = p.territories;
    return *this;
}
 
Player::Player(const Player& p){
    this->name = p.name;
    this->id = p.id;
    this->hand = p.hand;
    this->orders = p.orders;
    this->territories = p.territories;
}
 
 
ostream& operator<<(ostream& out, const Player& p)
{
    out << "Player " << p.name << " details:" << endl;
    //out << "Hand: " << p.hand << endl;
    out << "List of orders: " << *p.orders << endl;
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
OrderList* Player::getOrders(){
    return this->orders;
}
vector <Territory*> Player::getTerritories(){
    return this->territories;
}
string Player::getName(){
    return this->name;
}
int Player::getId(){
    return this->id;
}
 
// adders
 
void Player::addTerritory(Territory* territory){
    territories.push_back(territory);
}
void Player::addOrder(Order* order){
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
        vector <Territory*> adjacentTerritories = territory->getAdjacentTerritory();
        for (auto t : adjacentTerritories)
        if (find(adjacentTerritoriesNonDup.begin(), adjacentTerritoriesNonDup.end(), t) != adjacentTerritoriesNonDup.end())
        {
            adjacentTerritoriesNonDup.push_back(t);
        }
    }
}
