#include "PlayerStrategies.h"
#include <iostream>
using namespace std;

class Territory;
////////////////////////////////////////////// Virtual Base Class /////////////////////////////////////
/**
 * PlayerStrategy (Base class) empty constructor
 *
 */
PlayerStrategy::PlayerStrategy() {}
/**
 * PlayerStrategy  (Base class) Constructor with assigning player
 *
 * @param  {Player*} player :
 */
PlayerStrategy::PlayerStrategy(Player *player)
{
    this->player = player;
}
/**
 * ~PlayerStrategy  (Base class) destructor
 *
 */
PlayerStrategy::~PlayerStrategy()
{
    delete this->player;
    this->player = nullptr;
}
/**
 * PlayerStrategy  (Base class) Copy
 *
 * @param  {PlayerStrategy} ps : the copy
 */
PlayerStrategy::PlayerStrategy(const PlayerStrategy &ps)
{
    this->player = ps.player;
}
/**
 * PlayerStrategy  (Base class) Assignment operator
 *
 * @param  {PlayerStrategy} playerStrategy : the object to copy
 * @return {PlayerStrategy}                : the copied object
 */
PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &playerStrategy)
{
    this->player = playerStrategy.player;
    return *this;
}
/**
 * Necessary for proper printing
 * @param  {ostream} out                   : the stream to use
 * @param  {PlayerStrategy} playerStrategy : the object to print
 * @return {std::ostream}                  : the stream with description of player
 */
std::ostream &operator<<(ostream &out, const PlayerStrategy &playerStrategy)
{
    return out << playerStrategy.player << endl;
}
/**
 * PlayerStrategy player getter
 *
 * @return {Player*}  : player assigned to the object
 */
Player *PlayerStrategy::getPlayer()
{
    return this->player;
}
/**
 * PlayerStrategy name getter
 *
 * @return {string}  : the name assigned to the strategy
 */
string PlayerStrategy::getName()
{
    return this->strategyName;
}
/////////////////////////////////////////// Human Player //////////////////////////////////////////
/**
 * HumanPlayerStrategy constructor with player
 *
 * @param  {Player*} player : the player to be assigned to the strategy
 */
HumanPlayerStrategy::HumanPlayerStrategy(Player *player)
{
    this->player = player;
    this->strategyName = "human";
}
/**
 * virtual method from base class toDefend
 * @return {vector*}  : list of territories owned by the player
 */
vector<Territory *> HumanPlayerStrategy::toDefend()
{
    return this->player->getTerritories();
}
/**
 * virtual method from base class toAttack
 * @return {vector*}  : list of territories player can attack
 */
vector<Territory *> HumanPlayerStrategy::toAttack()
{
    cout << "The following territories are available to attack..." << endl;
    vector<Territory *> adjacentTerritoriesNonDup;
    // looping through all player's owned territories and get all their adjacent territories
    for (auto territory : this->player->getTerritories())
    {
        vector<Territory *> adjacentTerritories = territory->getAdjacentTerritory();
        for (auto t : adjacentTerritories)
            // looping through each adjacent territory, if it hasn't been added to the adjacentTerritories vector
            // then add it, this way it prevents duplicates.
            if (find(adjacentTerritoriesNonDup.begin(), adjacentTerritoriesNonDup.end(), t) != adjacentTerritoriesNonDup.end() == 0)
            {
                adjacentTerritoriesNonDup.push_back(t);
            }
    }

    // remove all territories belonging to the player
    vector<Territory *> territoriesToAttack;
    for (auto territory : adjacentTerritoriesNonDup)
    {
        if (find(this->player->getTerritories().begin(), this->player->getTerritories().end(), territory) != this->player->getTerritories().end() == 0)
        {
            territoriesToAttack.push_back(territory);
        }
    }

    return territoriesToAttack;
}
/**
 * HumanPlayerStrategy virtual method from base class issueOrder
 * Deploy phase -> Attack/deffend/card phase
 *
 */
void HumanPlayerStrategy::issueOrder()
{
    std::cout << this->getName() << " is issuing orders ..." << endl;
    std::cout << this->getName() << ", are you ready?" << endl;
    ;
    string ready = "";
    std::cin >> ready;
    // issuing deploy order
    int dummy_availableArmies = this->player->getAvailableArmies(); // creating a dummy available armies since the value of availableArmies
                                                                    // will not decrease until the deploy order is executed
    int initial_val_availableArmies = this->player->getAvailableArmies();

    while (true)
    {
        while (dummy_availableArmies > 0)
        {
            std::cout << "Deploying Order... you have " << dummy_availableArmies << " armies to deploy" << endl;
            std::cout << "These are the territories that are available to deploy your soliders"
                      << "\n\n ------Please choose one of the following index to deploy armies ------" << endl;
            this->player->printOwnedTerritories();
            int choice = 0;
            int numberOfArmies = 0;
            while (true)
            {
                std::cout << " ------Please choose one of the following index to deploy armies ------(" << dummy_availableArmies << ") remaining" << endl;
                std::cin >> choice;
                if (choice < 0 || choice >= this->player->getTerritories().size())
                {
                    std::cout << "Invalid input.. Please try again" << endl;
                }
                else
                {
                    break;
                }
            }
            while (true)
            {
                std::cout << "How many armies would you like to deploy ? You have " << dummy_availableArmies << " remaining" << endl;
                std::cin >> numberOfArmies;
                if (numberOfArmies > 0 && numberOfArmies <= dummy_availableArmies)
                {
                    break;
                }
                else
                {
                    std::cout << "Invalid input.. Please try again" << endl;
                }
            }

            std::cout << "Deploy Order " << numberOfArmies << " solders to \n"
                      << this->player->getTerritories().at(choice) << endl;
            DeployOrder *d = new DeployOrder(this->player, numberOfArmies, this->player->getTerritories().at(choice));
            dummy_availableArmies -= numberOfArmies;
            this->player->addOrder(d);
        }

        // ---------------------------issuing attack / defend / useCard  order------------------------------------
        int decision = -1;
        std::cout << "Please enter \n1 : to attack\n2 : to defend\n3 : to use card\n0 : to finish issuing orders " << endl;
        std::cin >> decision;
        int sourceIndex = 0;
        int targetIndex = 0;
        if (decision == 1)
        {
            this->player->advance();
        }
        else if (decision == 2)
        {
            this->player->defend();
        }
        else if (decision == 3)
        {
            this->player->useCard();
            // check if the value of availableArmies has changed due to reinforcementCard, therefore modify dummyAvailabeArmies value
            if (this->player->getAvailableArmies() != initial_val_availableArmies)
            {
                dummy_availableArmies += (this->player->getAvailableArmies() - initial_val_availableArmies);
            }
        }
        else
        {
            std::cout << this->player->getName() << "'s turn is finished" << endl;
            break;
        }
    }
}
/////////////////////////////////////// Aggressive Player /////////////////////////////////////////
/**
 * AggressivePlayerStrategy constructor to assign player
 *
 * @param  {Player*} player : player to assign to the strategy
 */
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *player)
{
    this->player = player;
    this->strategyName = "aggressive";
}
/**
 * virtual method from base class toDefend()
 * @return {vector*}  : list of player's territories
 */
vector<Territory *> AggressivePlayerStrategy::toDefend()
{
    return this->player->getTerritories();
}
/**
 * virtual method from base class toAttack
 * @return {vector*}  : list of territories that can be attacked
 */
vector<Territory *> AggressivePlayerStrategy::toAttack()
{
    vector<Territory *> adjacentTerritoriesNonDup;
    // looping through all player's owned territories and get all their adjacent territories
    for (auto territory : this->player->getTerritories())
    {
        vector<Territory *> adjacentTerritories = territory->getAdjacentTerritory();
        for (auto t : adjacentTerritories)
            // looping through each adjacent territory, if it hasn't been added to the adjacentTerritories vector
            // then add it, this way it prevents duplicates.
            if (find(adjacentTerritoriesNonDup.begin(), adjacentTerritoriesNonDup.end(), t) != adjacentTerritoriesNonDup.end() == 0)
            {
                adjacentTerritoriesNonDup.push_back(t);
            }
    }
    // filter out all territories belonging to the player
    vector<Territory *> territoriesToAttack;
    for (auto territory : adjacentTerritoriesNonDup)
    {
        if (find(this->player->getTerritories().begin(), this->player->getTerritories().end(), territory) != this->player->getTerritories().end() == 0)
        {
            territoriesToAttack.push_back(territory);
        }
    }
    return territoriesToAttack;
}
/**
 * virtual method from base class issueOrder
 * deploy -> attack orders
 *
 */
void AggressivePlayerStrategy::issueOrder()
{
    cout << "I am aggressive !" << endl;
    cout << this->player->getName() << " is issuing orders ..." << endl;
    // int strongestTerritoryIndex = 0;

    //// assign strongest territory index to the one with biggest number of armies
    // for (int i = 0; i < this->player->getTerritories().size(); i++) {
    //     if (this->player->getTerritories()[i]->getNumberOfArmies() > this->player->getTerritories()[strongestTerritoryIndex]->getNumberOfArmies()) {
    //         strongestTerritoryIndex = i;
    //     }
    // }
    // vector <Territory*> territoriesToAttack = this->toAttack();
    //// deploy all available solders to the strongest territory
    // DeployOrder* d = new DeployOrder(this->player, this->player->getAvailableArmies(), this->player->getTerritories()[strongestTerritoryIndex]);
    // this->player->addOrder(d);

    // for (auto t : this->player->getTerritories()[strongestTerritoryIndex]->getAdjacentTerritory()) {
    //     if (find(territoriesToAttack.begin(), territoriesToAttack.end(), t) != territoriesToAttack.end() == 0)
    //     {
    //         AdvanceOrder* a = new AdvanceOrder(this->player, this->player->getTerritories()[strongestTerritoryIndex]->getNumberOfArmies(), this->player->getTerritories()[strongestTerritoryIndex], t);
    //         this->player->addOrder(a);
    //         return;
    //     }
    // }

    // int randTargetIndex = rand() % this->player->getTerritories()[strongestTerritoryIndex]->getAdjacentTerritory().size();
    // AdvanceOrder* a = new AdvanceOrder(this->player, this->player->getTerritories()[strongestTerritoryIndex]->getNumberOfArmies(), this->player->getTerritories()[strongestTerritoryIndex], this->player->getTerritories()[strongestTerritoryIndex]->getAdjacentTerritory()[randTargetIndex]);
    // this->player->addOrder(a);
}
////////////////////////////////////// Benevolent Player //////////////////////////////////////////
/**
 * BenevolentPlayerStrategy constructor to assign player
 *
 * @param  {Player*} player : player to be assigned to the strategy
 */
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *player)
{
    this->player = player;
    this->strategyName = "benevolent";
}
/**
 * virtual method from base class toDefend
 * @return {vector*}  : list of player's territories
 */
vector<Territory *> BenevolentPlayerStrategy::toDefend()
{
    vector<Territory *> temp = this->player->getTerritories();
    std::sort(temp.begin(), temp.end(), [](Territory *a, Territory *b) -> bool
              { return (a->getNumberOfArmies() < b->getNumberOfArmies()); });

    return temp;
}
/**
 * virtual method from base class toAttack
 * @return {vector*}  : list of territories that can be attacked
 */
vector<Territory *> BenevolentPlayerStrategy::toAttack()
{
    vector<Territory *> temp = this->player->getTerritories();
    std::sort(temp.begin(), temp.end(), [](Territory *a, Territory *b) -> bool
              { return (a->getNumberOfArmies() > b->getNumberOfArmies()); });
    return temp;
}
/**
 * virtual method from base class issueOrder
 * Deploy order -> never attacks but moves army from strongest to weakest
 *
 */
void BenevolentPlayerStrategy::issueOrder()
{

    cout << this->player->getName() << "'s turn to issue orders!" << endl;
    cout << this->player->getName() << " is issuing orders ..." << endl;
    cout << "**---- Deploy Phase ----**" << endl;
    vector<Territory *> temp = this->toDefend();
    // Deploys to weakest territories until the amount of available armies is exhausted
    for (auto it = temp.begin(); it != std::prev(temp.end()); it++)
    {
        int armiesNeeded = it[1]->getNumberOfArmies() - it[0]->getNumberOfArmies();
        int armies = this->player->getAvailableArmies();
        cout << this->player->getName() << " has: " << armies << " armies available to use." << endl;

        if (armies <= 0)
        {
            break;
        }
        if (armies >= armiesNeeded)
        {
            this->player->addOrder(new DeployOrder(this->player, armiesNeeded, it[0]));
            cout << this->player->getName() << " Deploying onto " << it[0]->getTerritoryName() << endl;
            this->player->setAvailableArmies(armies - armiesNeeded);
        }
        else
        {
            this->player->addOrder(new DeployOrder(this->player, armies, it[0]));
            cout << this->player->getName() << " Deploying onto " << it[0]->getTerritoryName() << endl;
            this->player->setAvailableArmies(0);
        }
    }

    cout << "**---- Advance Phase ----**" << endl;
    temp = this->toAttack();
    // Advance armies from stronger territories to weaker territories
    vector<Territory *> tempAdj;
    for (auto it = temp.begin(); it != temp.end(); it++)
    {
        tempAdj = it[0]->getAdjacentTerritory();
        for (auto i = tempAdj.begin(); i != tempAdj.end(); i++)
        {
            if (i[0]->getOwnerOfTerritory()->getName() == this->player->getName())
            {
                int armyDifference = it[0]->getNumberOfArmies() - i[0]->getNumberOfArmies();
                if (armyDifference > 1)
                {
                    cout << "\nADVANCING on " << i[0]->getTerritoryName();
                    this->player->addOrder(new AdvanceOrder(this->player, armyDifference / 2, it[0], i[0]));
                }
            }
        }
    }

    // Hand* playerHand = this->player->getPlayerHand();
    // int playerHandSize = playerHand->getHand().size();

    // if (playerHandSize > 0) {
    // for (int i = 0; i < playerHandSize; i++) {
    // string cardType = playerHand->getHand().at(i)->getType();

    // if (cardType == "reinforcement") {

    // playerHand->getHand().at(i)->play(this->player->getGameDeck(), -1, nullptr, nullptr, nullptr);
    // break;
    // }
    // else if (cardType == "blockade") {

    // playerHand->getHand().at(i)->play(this->player->getGameDeck(), -1, toDefend().at(0), nullptr, nullptr);
    // break;
    // }
    // else if (cardType == "airlift") {
    // if (toDefend().size() > 1) {
    // playerHand->getHand().at(i)->play(this->player->getGameDeck(), toDefend().at(1)->getNumberOfArmies(), toDefend().at(0), toDefend().at(1), nullptr);
    // break;
    // }
    // }
    // else if (cardType == "diplomacy") {
    // Player* opponent;
    // for (auto it = this->toDefend().begin(); it != this->toDefend().end(); it++) {
    // for (auto i = it[0]->getAdjacentTerritory().begin(); i != it[0]->getAdjacentTerritory().end(); i++) {
    // if (i[0]->getOwnerOfTerritory() != this->player) {
    // opponent = i[0]->getOwnerOfTerritory();
    // break;
    // }
    // }

    // if (opponent) {
    // break;
    // }
    // }
    // playerHand->getHand().at(i)->play(this->player->getGameDeck(), -1, nullptr, nullptr, opponent);
    // break;
    // }
    // else {
    // cout << "Benevolent Player will not use a Bomb Card!" << endl;
    // break;
    // }
    // }

    // }
    // else {
    // cout << this->player->getName() << " has no Cards to play!" << endl;
    // }
    cout << this->player->getName() << " has issued their Orders!\n";
}
/////////////////////////////////////// Neutral Player ////////////////////////////////////////////
/**
 * NeutralPlayerStrategy constructor to assign player
 *
 * @param  {Player*} player : player to be assigned to the strategy
 */
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *player)
{
    this->player = player;
    this->strategyName = "neutral";
}
/**
 * virtual method from base class toDefend
 * @return {vector*}  : list of player's territories
 */
vector<Territory *> NeutralPlayerStrategy::toDefend()
{
    vector<Territory *> temp = this->player->getTerritories();
    std::sort(temp.begin(), temp.end(), [](Territory *a, Territory *b) -> bool
              { return (a->getNumberOfArmies() < b->getNumberOfArmies()); });
    return temp;
}
/**
 * virtual method from base class toAttack
 * @return {vector*}  : the list of terries that can be attacked
 */
vector<Territory *> NeutralPlayerStrategy::toAttack()
{
    return vector<Territory *>();
}

// Neutral Player never issues or creates any orders
/**
 * virtual method from base class issueOrder
 * this strategy doesnt do any orders
 *
 */
void NeutralPlayerStrategy::issueOrder()
{

    cout << this->player->getName() << "'s turn to issue orders!" << endl;
    cout << this->player->getName() << " is issuing orders ..." << endl;
    cout << "**---- Deploy Phase ----**" << endl;
    cout << this->player->getName() << " has: " << this->player->getAvailableArmies() << " available to use." << endl;
    cout << this->player->getName() << " will not deploy any armies" << endl;

    cout << "**---- Advance Phase ----**" << endl;
    cout << this->player->getName() << " will not advance any armies" << endl;
    cout << "**---- Card Phase ----**" << endl;
    cout << this->player->getName() << " will not use any cards" << endl;
    cout << "End of " << this->player->getName() << "'s turn!" << endl;
}
/////////////////////////////////////// Cheater Player ////////////////////////////////////////////
/**
 * CheaterPlayerStrategy constructor to assign player
 *
 * @param  {Player*} player : player to be assigned to the strategy
 */
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *player)
{
    this->player = player;
    this->strategyName = "cheater";
}
/**
 * virtual method from base class toDefend
 * @return {vector*}  : list of player's territories
 */
vector<Territory *> CheaterPlayerStrategy::toDefend()
{
    return this->player->getTerritories();
}
/**
 * virtual method from base class toAttack
 * @return {vector*}  : list of territories that can be attacked
 */
vector<Territory *> CheaterPlayerStrategy::toAttack()
{
    return this->player->getTerritories();
}
/**
 * virtual method from base class issueOrder
 * conquering all the adjacent territories
 */
void CheaterPlayerStrategy::issueOrder()
{
    cout << "I am cheating !" << endl;
    cout << this->player->getName() << " is issuing orders ..." << endl;
    int randomTerritoryIndex = 0;
    if (this->player->getAvailableArmies() > 0 && this->player->getTerritories().size() != 0)
    {
        randomTerritoryIndex = rand() % this->player->getTerritories().size();
    }

    // deploy all available solders to a random territory
    DeployOrder *d = new DeployOrder(this->player, this->player->getAvailableArmies(), this->player->getTerritories()[randomTerritoryIndex]);

    this->player->addOrder(d);
    cout << "Cheater will now cheat and automatically conquer all territories that are adjacent to its own territories" << endl;
    for (auto territory : this->player->getTerritories())
    {
        for (auto adj : territory->getAdjacentTerritory())
        {
            /*   cout << "--------------\n" << *adj << " now belongs to " << player->getName() << "\n" << endl;*/
            adj->getOwnerOfTerritory()->removeTerritory(adj); // remove from previous owner's territories list
            adj->setOwnerOfTerritory(this->player);           // set ownership of territory to current player
            this->player->addTerritory(adj);                  // add this territory into territories list
        }
    }
}