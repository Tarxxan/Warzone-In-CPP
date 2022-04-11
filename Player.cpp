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
// Was scared to include it as parameter as many class use this constructor but we will have to do it eventually 
// (for now we can use the setStrategy method)
Player::Player(string player_name) {
    this->name = player_name;
    this->playerHand = new Hand();
    this->orders = new OrderList();
    this->territories = vector<Territory*>();
    this->availableArmies = 0;
    this->strategy = new HumanPlayerStrategy(this); // Defaults to Human if no other was specified (can be set in setStrategy method)
}
Player::Player(string player_name, PlayerStrategy* strategy) {
    this->name = player_name;
    this->playerHand = new Hand();
    this->orders = new OrderList();
    this->territories = vector<Territory*>();
    this->availableArmies = 0;
    this->strategy = strategy;
}
Player::Player(string player_name, string strategy) {
    this->name = player_name;
    this->playerHand = new Hand();
    this->orders = new OrderList();
    this->territories = vector<Territory*>();
    this->availableArmies = 0;
    if (strategy == "Aggressive") {
        this->strategy = new AggressivePlayerStrategy(this);
    }
    else if (strategy == "Benevolent") {
        this->strategy = new BenevolentPlayerStrategy(this);
    }
    else if (strategy == "Neutral") {
        this->strategy = new NeutralPlayerStrategy(this);
    }
    else if (strategy == "Cheater") {
        this->strategy = new CheaterPlayerStrategy(this);
    }
    else {
        this->strategy = new HumanPlayerStrategy(this);
    }
}

Player::~Player()   //Destructor
{   //  To avoid memory leak, delete all pointer objects and assign them to nullptr
    delete orders;
    orders = nullptr;
    delete playerHand;
    playerHand = nullptr;
    for (int i = 0; i < territories.size(); i++) {
        territories[i] = nullptr;
    }
    
    strategy = nullptr;
    cout << "~Player destructed" << endl;
};


//assignment operator
Player& Player::operator=(const Player& p) {
    this->name = p.name;
    this->playerHand = p.playerHand;
    this->orders = p.orders;
    this->territories = p.territories;
    this->strategy = p.strategy;
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
    this->strategy = p.strategy;
}

ostream& operator<<(ostream& out, const Player& p)
{
    out << "Player " << p.name << " details:" << endl;
    out << p.name << " has the following cards " << endl;
    out << p.name << " has " << p.playerHand->getHand().size() << " cards" << endl;
    cout << "--------------------------" << endl;
    cout << *p.playerHand;
    cout << "--------------------------" << endl;
    out << p.name << " has " << p.territories.size() << " territories" << endl;

    for (int i = 0; i < p.territories.size(); i++) {
        cout << *p.territories[i] << endl;
    }

    out << p.name << " has " << p.orders->getOrders().size() << " orders" << endl;
    cout << "Player is using " << p.strategy->getName() << " strategy" << endl;
    cout << "-----------------------------------------------------" << endl;


    cout << "test- " << p.territories.size() << endl;


    return out;
}


// getters
Hand* Player::getPlayerHand() {
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
void Player::setOpponents(Player* p) {
    opponents.push_back(p);
}

void Player::setAvailableArmies(int i)
{
    this->availableArmies = i;
}

void Player::addAvailableArmies(int n)
{
    this->availableArmies += n;
}

void Player::addTerritory(Territory* territory) {
    territories.push_back(territory);
    territory->setOwnerOfTerritory(this);   // Setting this player as the owner of territory
}

void Player::addOrder(Order* order) {
    orders->push(order);
}

// every round, user's number of reinforcementPoll armies is determined by the number of territories user possesses
void Player::computeReinforcementPool() {
   
    cout << name << " has " << territories.size() << " territories" << endl;
    // assign the number of armies
    int armiesToAdd = int(floor(territories.size() / 3));
    // In any case, the minimal number of reinforcement armies for any player is 3
    if (armiesToAdd < 3) {
        armiesToAdd = 3;
    }
    availableArmies += armiesToAdd;
    cout << armiesToAdd << " armies have been added into " << name << " \'s reinforcement pool " << endl;
    cout << name << " now has " << availableArmies << " in the reinforcement pool " << endl;

}

// function to print all the territories user possesses
void Player::printOwnedTerritories() {
    cout << "drawing card..." << endl;
    drawCard();
    cout << "------------------------------\nHere are your owned territories" << endl;
    for (int i = 0; i < territories.size(); i++) {
        cout << i << *territories[i] << endl;
    }
    if (getOrders()->getOrders().size() > 0) {
        cout << "\nHere are your orderList Queue" << endl;
        for (int j = 0; j < getOrders()->getOrders().size(); j++) {
            cout << *getOrders()->getOrders()[j] << endl;
        }
        cout << endl;
    }
}

// user issues order and add all the orders into order list. All decision-makings are done here
void Player::issueOrder() {
    this->strategy->issueOrder();
}

void Player::addCard(Card* card) {
    playerHand->push(card);
}



void Player::advance() {
    // confirm that this *from territory belongs to the player
    int sourceIndex = 0;
    int targetIndex = 0;
    cout << "Please choose a territory to advance soliders (source)" << endl;
    printOwnedTerritories();
    while (true) {
        cout << "Please choose a territory to advance soliders (source)" << endl;
        cin >> sourceIndex;
        if (sourceIndex < 0 || sourceIndex >= territories.size()) {
            cout << "Invalid input.. Please try again" << endl;
        }
        else {
            break;
        }
    }
    cout << "----------------------" << endl;
    vector <Territory*> territoriesToAttack = this->getStrategy()->toAttack();
    for (int i = 0; i < territoriesToAttack.size(); i++) {
        cout << i << *territoriesToAttack[i] << endl;
    }

    while (true) {
        cout << "\n\nPlease choose a target to attack" << endl;
        cin >> targetIndex;
        if (targetIndex < 0 || targetIndex >= territoriesToAttack.size()) {
            cout << "Invalid input, please select the right index of the territory" << endl;
        }
        else {
            break;
        }
    }
    // prompt user to enter how many armies to advance
    int armiesToSend = 0;
    while (true) {
        cout << "\nPlease choose how many armies you would like to send to attack (" << territories[sourceIndex]->getNumberOfArmies() << ")" << endl;
        cin >> armiesToSend;
        if (armiesToSend < 0 || armiesToSend > territories[sourceIndex]->getNumberOfArmies()) {
            cout << "Invalid input, please select the right amount of armies" << endl;
        }
        else {
            break;
        }
    }
    AdvanceOrder* a = new AdvanceOrder(this, armiesToSend, territories[sourceIndex], territoriesToAttack[targetIndex]);
    orders->push(a);
    cout << *a << endl;
}

void Player::defend() {
    int sourceIndex = 0;
    int targetIndex = 0;
    printOwnedTerritories();

    while (true) {
        cout << "Please choose which territory you would like to send reinforcement from (source)" << endl;
        cin >> sourceIndex;
        if (sourceIndex < 0 || sourceIndex >= territories.size()) {
            cout << "Invalid input, please select the right index of the territory" << endl;
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Please choose a target to send your reinforcement" << endl;
        cin >> targetIndex;
        if (targetIndex < 0 || targetIndex >= territories.size()) {
            cout << "Invalid input, please select the right index of the territory" << endl;
        }
        else {
            break;
        }
    }
    int numberReinforcement = 0;

    while (true) {
        cout << "How many armies would you like to send?" << endl;
        cin >> numberReinforcement;
        if (numberReinforcement <= 0 || numberReinforcement > territories[sourceIndex]->getNumberOfArmies()) {
            cout << "Invalid input, please select the right amount of armies" << endl;
        }
        else {
            break;
        }
    }

    AdvanceOrder* a = new AdvanceOrder(this, numberReinforcement, territories[sourceIndex], territories[targetIndex]);
    orders->push(a);
    cout << "Defense Order " << numberReinforcement << " solders from\n " << *territories[sourceIndex] << " to\n" << *territories[targetIndex] << endl;

}

void Player::useCard() {

    for (int i = 0; i < playerHand->getHand().size(); i++) {
        cout << i << " - " << playerHand->getHand()[i]->getType() << endl;
    }
    int cardChoice = 0;
    string type = "";
    while (true) {
        cout << "\nPlease select the index of the card you would like to use" << endl;
        cin >> cardChoice;
        if (cardChoice == -1) {
            break;
        }
        if (cardChoice < 0 || cardChoice >= playerHand->getHand().size()) {
            cout << "Invalid input, please select the right index of cards" << endl;
        }
        else {
            type = playerHand->getHand()[cardChoice]->getType();
            break;
        }
    }

    // -------------------------------------------Bomb Order---------------------------------------------------
    if (type == "bomb") {
        cout << "Please select one of your adjacent territories to bomb?" << endl;
        vector<Territory*> territoriesToBomb = toAttack();
        for (int i = 0; i < territoriesToBomb.size(); i++) {
            cout << i << *territoriesToBomb[i] << endl;
        }
        int target = 0;
        while (true) {
            cout << "Please select one of your adjacent territories to bomb?" << endl;
            cin >> target;
            if (target < 0 || target >= territoriesToBomb.size()) {
                cout << "Invalid input, please select the right index" << endl;
            }
            else {
                break;
            }
        }

        BombOrder* o = new BombOrder(this, territoriesToBomb[target]);
        orders->push(o);
        cout << "Bomb order at " << *territoriesToBomb[target] << endl;
    }
    // -------------------------------------------Reinforcement Order---------------------------------------------------
    else if (type == "reinforcement") {
        cout << "using reinforcement card" << endl;
        availableArmies += 5;
    }
    // -------------------------------------------Blockade Order---------------------------------------------------
    else if (type == "blockade") {
        cout << "Please select one of your territories to block and double the amount of solders?" << endl;
        for (int i = 0; i < territories.size(); i++) {
            cout << i << *territories[i] << endl;
        }
        int target = 0;

        while (true) {
            cout << "Please select one of your territories to block and double the amount of solders?" << endl;
            cin >> target;
            if (target < 0 || target >= territories.size()) {
                cout << "Invalid input, please select the right index" << endl;
            }
            else {
                break;
            }
        }
        BlockadeOrder* o = new BlockadeOrder(this, territories[target]);
        orders->push(o);
        cout << "Blockade order at " << *territories[target] << endl;
    }
    // -------------------------------------------Airlift Order---------------------------------------------------
    else if (type == "airlift") {
        for (int i = 0; i < territories.size(); i++) {
            cout << i << *territories[i] << endl;
        }
        int sourceIndex = 0;
        int targetIndex = 0;
        int n_solders = 0;
        

        while (true) {
            cout << "Please select the source territory to airlift solders?" << endl;
            cin >> sourceIndex;
            if (sourceIndex < 0 || sourceIndex >= territories.size()) {
                cout << "Invalid input, please select the right index" << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Please select the target territory to airlift solders?" << endl;
            cin >> targetIndex;
            if (targetIndex < 0 || targetIndex >= territories.size()) {
                cout << "Invalid input, please select the right index" << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Please select the number of solders to airlfit?" << endl;
            cin >> n_solders;
            if (n_solders < 0 || n_solders > territories[sourceIndex]->getNumberOfArmies()) {
                cout << "Invalid input, please select the right index" << endl;
            }
            else {
                break;
            }
        }

        AirliftOrder* o = new AirliftOrder(this, n_solders, territories[sourceIndex], territories[targetIndex]);
        orders->push(o);
        cout << "Airlift order " << n_solders << " solders from \n" << *territories[sourceIndex] << " to \n" << *territories[targetIndex] << endl;
    }
    // -------------------------------------------Negotiate Order---------------------------------------------------
    else if (type == "diplomacy") {
        cout << "using diplomacy card" << endl;
        for (int i = 0; i < opponents.size(); i++) {
            cout << i << " - " << opponents[i]->getName() << endl;
        }
        int opponentIndex = 0;
        while (true) {
            cout << "Please select the opponent you would like to negotiate?" << endl;
            cin >> opponentIndex;
            if (opponentIndex < 0 || opponentIndex >= opponents.size()) {
                cout << "Invalid input, please select the right index" << endl;
            }
            else {
                break;
            }
        }
        negotiatePlayer(opponents[opponentIndex]);
        NegotiateOrder* n = new NegotiateOrder(this, opponents[opponentIndex]);
        orders->push(n);
        // DO I call NegotiateOrder like what I did with every other order and push into orderlist?
        // or you have something in mind with this negotiatePlayer function?
    }
    // removing card from hand
    if (cardChoice != -1) {

        cout << "removing " << playerHand->getHand()[cardChoice]->getType() << " card from player's hand " << endl;
        //playerHand.remove(playerHand->getHand()[i]);
        playerHand->getHand()[cardChoice]->setPlayer(nullptr);
        gameDeck->push(playerHand->getHand()[cardChoice]);
        playerHand->remove(playerHand->getHand()[cardChoice]);


    }


}


vector<Territory*> Player::toDefend() {
    return this->strategy->toDefend();
    // cout << "The following territories are owned by the player and to be defended..." << endl;
    // return territories;
}

vector<Territory*> Player::toAttack() {
    return this->strategy->toAttack();
    // cout << "The following territories are available to attack..." << endl;
    // vector <Territory*> adjacentTerritoriesNonDup;
    // // looping through all player's owned territories and get all their adjacent territories
    // for (auto territory : territories) {
    //     vector <Territory*> adjacentTerritories = territory->getAdjacentTerritory();
    //     for (auto t : adjacentTerritories)
    //         // looping through each adjacent territory, if it hasn't been added to the adjacentTerritories vector
    //         // then add it, this way it prevents duplicates.
    //         if (find(adjacentTerritoriesNonDup.begin(), adjacentTerritoriesNonDup.end(), t) != adjacentTerritoriesNonDup.end() == 0)
    //         {
    //             adjacentTerritoriesNonDup.push_back(t);
    //         }
    // }

    // // remove all territories belonging to the player
    // vector <Territory*> territoriesToAttack;
    // for (auto territory : adjacentTerritoriesNonDup) {
    //     if (find(territories.begin(), territories.end(), territory) != territories.end() == 0)
    //     {
    //         territoriesToAttack.push_back(territory);
    //     }
    // }

    // return territoriesToAttack;
}

void Player::removeSolders(int amount) {
    this->availableArmies = this->availableArmies - amount;
}

void Player::removeTerritory(Territory* t) {
    int index = 0;
    for (Territory* ter : this->territories) {
        if (ter == t) {
            auto posIt = this->territories.begin() + index;
            this->territories.erase(posIt); // will delete the thing we are looking for
            break;
        }
        index++;
    }
}

void Player::drawCard() {};
void Player::negotiatePlayer(Player* enemy) {
    this->cannotAttack.push_back(enemy);
}
void Player::setGameDeck(Deck* deck) {
    this->gameDeck = deck;
}
Deck* Player::getGameDeck() {
    return this->gameDeck;
}
bool Player::canAttack(Player* enemy) {
    for (Player* p : this->cannotAttack) {
        if (p == enemy) {
            return false;
        }
    }
    return true;
}
void Player::deleteNegotiate(Player* enemy) {
    int index = 0;
    for (Player* p : this->cannotAttack) {
        if (p == enemy) {
            auto posIt = this->cannotAttack.begin() + index;
            this->cannotAttack.erase(posIt); // will delete the thing we are looking for
            return;
        }
        index++;
    }
}

PlayerStrategy* Player::getStrategy() {
    return this->strategy;
}
void Player::setStrategy(PlayerStrategy* strategy) {
    this->strategy = strategy;
}