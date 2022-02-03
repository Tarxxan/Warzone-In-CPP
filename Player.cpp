// A player owns a collection of territories (from the map)
// A player owns a hand of Cards
// A player has their own list of orders to be created and executed in the current turn
// The player should contain a method named toDefend() that return a list of territories that are to be defended, as well as a method named
// toAttack() that returns a list of territories that are to be attacked
// Player contains a issueOrder() method that creates an order object and adds it to the list of
// orders. 
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <list>
#include <fstream> // file stream
#include <string> // Needed for Getline method
using namespace std;

Player::Player() {
} //Default Constructor


std::list<Order> orders;
std::list<Territory> territories;
std::list<Card> cards;

Player::Player(std::list<Order> orders, std::list<Territory> territories, std::list<Card> cards)
{
    this->orders = orders;
    this->territories = territories;
    this->cards = cards;

}

Player::~Player()
{
    cout << "~Player destructed" << endl;

}


ostream& operator<<(ostream& output, Player& p)
{
    /*
    output << "Player has cards: " << p.getCards() << endl;
    output << "Player has cards: " << p.getOrders() << endl;
    output << "--Territory ID: " << p.getTerritories() << endl;
    */
    return output;
}

//member functions
list<Order> Player:: getOrders() {
    return orders;
}

list<Card> Player::getCards() {
    return cards;
}


list<Territory> Player::toDefend() {// return a list of territories that are to be defended
    list<Territory> territories_to_defend;
    cout << "calling toDefend()" << endl;
    return territories_to_defend;
}

list<Territory> Player::toAttack() { //  returns a list of territories that are to be attacked
    list<Territory> territories_to_attack;
    cout << "calling toAttack()" << endl;
    return territories_to_attack;
}
                            // establish an arbitrary list of territories to be defended, and an
                            // arbitrary list of territories that are to be attacked.
void Player:: issueOrder(string new_order) {   //creates an Order object and puts it in the player’s list of orders.
    Order *newOrder = new Order(new_order);
    cout << "calling issueOrder()" << endl;
    orders.push_back(*newOrder);
}


