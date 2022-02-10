// A player owns a collection of territories (from the map)
// A player owns a hand of Cards
// A player has their own list of orders to be created and executed in the current turn
// The player should contain a method named toDefend() that return a list of territories that are to be defended, as well as a method named
// toAttack() that returns a list of territories that are to be attacked
// Player contains a issueOrder() method that creates an order object and adds it to the list of
// orders. 
#include "GameEngine.h"

Player::Player() {}; //Default Constructor
Player::~Player()
{
    cout << "~Player destructed" << endl;

};
Player::Player(int id, string player_name){
    this->id = id;
    this->name = player_name;
}
Player& Player::operator=(const Player& p){
    this->name = p.name;
    this->id = p.id;
    this->hand = p.hand;
    this->orders = p.orders;
    this->territories = p.territories;
    return *this;
}
// Player::Player(vector <Order*> orders, vector <Territory*> territories, vector <Card*> cards)// why do you need this constructor?
// {
//     this->orders = orders;
//     this->territories = territories;
//     this->hand = cards;
// }
Player::Player(const Player& p){
    this->name = p.name;
    this->id = p.id;
    this->hand = p.hand;
    this->orders = p.orders;
    this->territories = p.territories;
}

ostream& operator<<(ostream& output, Player& p)
{
    return output << "Player: " << p.getName() << endl;
    /*
    output << "Player has cards: " << p.getCards() << endl;
    output << "Player has cards: " << p.getOrders() << endl;
    output << "--Territory ID: " << p.getTerritories() << endl;
    */
    // return output;
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
void addCard(Card* card){
    // add to players hand
}
void addTerritory(Territory* territory){
    // add to players territories
}
void addOrder(Order* order){
    //ad to players orders
}
//member functions
// list<Territory> Player::toDefend() {// return a list of territories that are to be defended
//     list<Territory> territories_to_defend;
//     cout << "calling toDefend()" << endl;
//     return territories_to_defend;
// }

// list<Territory> Player::toAttack() { //  returns a list of territories that are to be attacked
//     list<Territory> territories_to_attack;
//     cout << "calling toAttack()" << endl;
//     return territories_to_attack;
// }

//                             // establish an arbitrary list of territories to be defended, and an
//                             // arbitrary list of territories that are to be attacked.
// void Player:: issueOrder() {   //creates an Order object and puts it in the player�s list of orders.
//     Order *newOrder = new Order();
//     cout << "calling issueOrder()" << endl;
//     playerOrders.push_back(*newOrder);
// }
// bool Player::addPlayerTerritories(Territory territory){ // return true if territory is successfully added
//     return true;
// }



   
    




