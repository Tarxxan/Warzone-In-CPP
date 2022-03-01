// A player has their own list of orders to be created and executed in the current turn
// The player should contain a method named toDefend() that return a list of territories that are to be defended, as well as a method named
// toAttack() that returns a list of territories that are to be attacked
// Player contains a issueOrder() method that creates an order object and adds it to the list of
// orders.

#include "Player.h"
#include <iostream>
using namespace std;
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
Player::Player() {}; //Default Constructor

Player::Player(string player_name) {
    this->name = player_name;
    this->playerHand = new Hand();
    this->orders = new OrderList();
    this->territories = vector<Territory*>();
}

Player::~Player()   //Destructor
{   //  To avoid memory leak, delete all pointer objects and assign them to nullptr
    delete orders;
    orders = nullptr;
    delete playerHand;
    playerHand = nullptr;
    for (int i = 0; i < territories.size(); i++) {
        delete territories[i];
        territories[i] = nullptr;
    }
    cout << "~Player destructed" << endl;
};


//assignment operator
Player& Player::operator=(const Player &p) {
    this->name = p.name;
    this->playerHand = p.playerHand;
    this->orders = p.orders;
    this->territories = p.territories;
    return *this;
}

//Copy constructor
Player::Player(const Player& p) {
    cout << "Copy constructor called" << endl;
    this->name = p.name;
    this->availableArmies = p.availableArmies;
    this->playerHand = p.playerHand;
    this->orders = p.orders;
    this->territories = p.territories;
    this->playerHand = p.playerHand;
}

ostream& operator<<(ostream& out, const Player& p)
{
    out << "Player " << p.name << " details:" << endl;
    out << p.name << " has the following cards " << endl;
    out << p.name << " has " << p.playerHand->getHand().size() << " cards" << endl;
    cout << "--------------------------" << endl;
    cout << *p.playerHand ;
    cout << "--------------------------" << endl;
    out << p.name << " has "<< p.territories.size() << " territories" << endl;

    for (int i = 0; i < p.territories.size(); i++) {
        cout << *p.territories[i] << endl;
    }

    out << p.name << " has " << p.orders->getOrders().size() << " orders" << endl;
    cout << "-----------------------------------------------------" << endl;
    return out;
}


// getters
Hand* Player::getPlayerHand(){
    return this->playerHand;
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
int Player::getAvailableArmies() {
    return availableArmies;
}


// adders
void Player::addTerritory(Territory* territory) {
    territories.push_back(territory);
    territory->setOwnerOfTerritory(this);   // Setting this player as the owner of territory
}

void Player::addOrder(Order* order) {
    orders->push(order);
}
void Player::issueOrder(Order* order) {
    orders->push(order);
}

void Player::addCard(Card* card) {
    playerHand->push(card);
}

void Player::computeAvailableArmies() {
    // assign the number of armies
    availableArmies = int(floor(territories.size()/3));
    // In any case, the minimal number of reinforcement armies for any player is 3
    if (availableArmies < 3) {
        availableArmies = 3;
    }
}

void Player::advance(Territory *from, Territory *to) {
    // confirm that this *from territory belongs to the player
    if(std::find(territories.begin(), territories.end(), from) != territories.end()) {
        if (std::find(territories.begin(), territories.end(), to) != territories.end()) {
            // will reinforce
            return;
        }
        else {
            //will attack
            return;
        }
    }
}

vector<Territory*> Player::toDefend() {
    cout << "The following territories are owned by the player and to be defended..." << endl;
    return territories;
}
 
vector<Territory*> Player::toAttack() {
    cout << "The following territories are available to attack..." << endl;
    vector <Territory*> adjacentTerritoriesNonDup;
    // looping through all player's owned territories and get all their adjacent territories
    for (auto territory : territories) {
        vector <Territory*> adjacentTerritories = territory->getAdjacentTerritory();
        for (auto t : adjacentTerritories)
        // looping through each adjacent territory, if it hasn't been added to the adjacentTerritories vector
        // then add it, this way it prevents duplicates.
        if (find(adjacentTerritoriesNonDup.begin(), adjacentTerritoriesNonDup.end(), t) != adjacentTerritoriesNonDup.end() == 0)
        {
            adjacentTerritoriesNonDup.push_back(t);
        }

    }
    return adjacentTerritoriesNonDup;
}

void Player::removeSolders(int amount){
    this->availableArmies = this->availableArmies - amount;
}
