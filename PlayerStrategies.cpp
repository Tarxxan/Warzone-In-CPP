#include "PlayerStrategies.h"
#include <iostream>
using namespace std;

class Territory;
////////////////////////////////////////////// Virtual Base Class /////////////////////////////////////
PlayerStrategy::PlayerStrategy(){}
PlayerStrategy::PlayerStrategy(Player* player){
    this->player = player;
}
PlayerStrategy::~PlayerStrategy(){
    delete this->player;
    this->player = nullptr;
}
PlayerStrategy::PlayerStrategy(const PlayerStrategy& ps){
    this->player = ps.player;
}
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& playerStrategy){
    this->player = playerStrategy.player;
    return *this;
}
std::ostream& operator<<(ostream& out, const PlayerStrategy& playerStrategy){
    return out << playerStrategy.player << endl;
}
Player* PlayerStrategy::getPlayer(){
    return this->player;
}
string PlayerStrategy::getName(){
    return this->strategyName;
}
/////////////////////////////////////////// Human Player //////////////////////////////////////////
HumanPlayerStrategy::HumanPlayerStrategy(Player* player){
    this->player = player;
    this->strategyName = "human";
}
vector <Territory*> HumanPlayerStrategy::toDefend(){
    return this->player->getTerritories();
}
vector <Territory*> HumanPlayerStrategy::toAttack(){
    cout << "The following territories are available to attack..." << endl;
    vector <Territory*> adjacentTerritoriesNonDup;
    // looping through all player's owned territories and get all their adjacent territories
    for (auto territory : this->player->getTerritories()) {
        vector <Territory*> adjacentTerritories = territory->getAdjacentTerritory();
        for (auto t : adjacentTerritories)
            // looping through each adjacent territory, if it hasn't been added to the adjacentTerritories vector
            // then add it, this way it prevents duplicates.
            if (find(adjacentTerritoriesNonDup.begin(), adjacentTerritoriesNonDup.end(), t) != adjacentTerritoriesNonDup.end() == 0)
            {
                adjacentTerritoriesNonDup.push_back(t);
            }
    }

    // remove all territories belonging to the player
    vector <Territory*> territoriesToAttack;
    for (auto territory : adjacentTerritoriesNonDup) {
        if (find(this->player->getTerritories().begin(), this->player->getTerritories().end(), territory) != this->player->getTerritories().end() == 0)
        {
            territoriesToAttack.push_back(territory);
        }
    }

    return territoriesToAttack;
}
void HumanPlayerStrategy::issueOrder(){
    std::cout << this->getName() << " is issuing orders ..." << endl;
    std::cout << this->getName() << ", are you ready?" << endl;;
    string ready = "";
    std::cin >> ready;
    // issuing deploy order
    int dummy_availableArmies = this->player->getAvailableArmies();        // creating a dummy available armies since the value of availableArmies
                                                        // will not decrease until the deploy order is executed
    int initial_val_availableArmies = this->player->getAvailableArmies();

    while (true) {
        while (dummy_availableArmies > 0) {
            std::cout << "Deploying Order... you have " << dummy_availableArmies << " armies to deploy" << endl;
            std::cout << "These are the territories that are available to deploy your soliders"
                << "\n\n ------Please choose one of the following index to deploy armies ------" << endl;
            this->player->printOwnedTerritories();
            int choice = 0;
            int numberOfArmies = 0;
            while (true) {
                std::cout << " ------Please choose one of the following index to deploy armies ------(" << dummy_availableArmies << ") remaining" << endl;
                std::cin >> choice;
                if (choice < 0 || choice >= this->player->getTerritories().size()) {
                    std::cout << "Invalid input.. Please try again" << endl;
                }
                else {
                    break;
                }
            }
            while (true) {
                std::cout << "How many armies would you like to deploy ? You have " << dummy_availableArmies << " remaining" << endl;
                std::cin >> numberOfArmies;
                if (numberOfArmies > 0 && numberOfArmies <= dummy_availableArmies) {
                    break;
                }
                else {
                    std::cout << "Invalid input.. Please try again" << endl;
                }
            }

            std::cout << "Deploy Order " << numberOfArmies << " solders to \n" << this->player->getTerritories().at(choice) << endl;
            DeployOrder* d = new DeployOrder(this->player, numberOfArmies, this->player->getTerritories().at(choice));
            dummy_availableArmies -= numberOfArmies;
            this->player->addOrder(d);
        }

        // ---------------------------issuing attack / defend / useCard  order------------------------------------
        int decision = -1;
        std::cout << "Please enter \n1 : to attack\n2 : to defend\n3 : to use card\n0 : to finish issuing orders " << endl;
        std::cin >> decision;
        int sourceIndex = 0;
        int targetIndex = 0;
        if (decision == 1) {
            this->player->advance();
        }
        else if (decision == 2) {
            this->player-> defend();
        }
        else if (decision == 3) {
            this->player->useCard();
            // check if the value of availableArmies has changed due to reinforcementCard, therefore modify dummyAvailabeArmies value
            if (this->player->getAvailableArmies() != initial_val_availableArmies) {
                dummy_availableArmies += (this->player->getAvailableArmies() - initial_val_availableArmies);
            }
        }
        else {
            std::cout << this->player->getName() << "'s turn is finished" << endl;
            break;
        }
    }
}
/////////////////////////////////////// Aggressive Player /////////////////////////////////////////
AgressivePlayerStrategy::AgressivePlayerStrategy(Player* player){
    this->player = player;
    this->strategyName = "agressive";
}
vector <Territory*> AgressivePlayerStrategy::toDefend(){

}
vector <Territory*> AgressivePlayerStrategy::toAttack(){

}
void AgressivePlayerStrategy::issueOrder(){
    
}
////////////////////////////////////// Benevolent Player //////////////////////////////////////////
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player){
    this->player = player;
    this->strategyName = "benevolent";
}
vector <Territory*> BenevolentPlayerStrategy::toDefend(){
    std::sort(this->player->getTerritories().begin(),this->player->getTerritories().end(),[](Territory* a, Territory* b) {
        return (a->getNumberOfArmies() < b->getNumberOfArmies());
    });
    return this->player->getTerritories();
}
vector <Territory*> BenevolentPlayerStrategy::toAttack(){
    std::sort(this->player->getTerritories().begin(),this->player->getTerritories().end(),[](Territory* a, Territory* b) {
        return (a->getNumberOfArmies() > b->getNumberOfArmies());
    });
    return this->player->getTerritories();
}
void BenevolentPlayerStrategy::issueOrder(){
    
    cout << this->player->getName() << "'s turn to issue orders!" << endl;
    cout << this->player->getName()<< " is issuing orders ..." << endl;
    cout << "**---- Deploy Phase ----**" << endl;

    //Deploys to weakest territories until the amount of available armies is exhausted

    for(auto it = this->toDefend().begin(); it != this->toDefend().end(); it++){
       
        int armiesNeeded = it[1]->getNumberOfArmies() - it[0]->getNumberOfArmies();
        int armies = this->player->getAvailableArmies();
        cout << this->player->getName() << " has: " << armies << " available to use." << endl;

        if(armies <= 0){
            break;
        }
        if(armies >= armiesNeeded){
            this->player->addOrder(new DeployOrder(this->player,armiesNeeded,it[0]));
            this->player->setAvailableArmies(armies - armiesNeeded);
        }else{
            this->player->addOrder(new DeployOrder(this->player,armies,it[0]));
            this->player->setAvailableArmies(0);
        }


    }
    
    cout << "**---- Advance Phase ----**" << endl;

    //Advance armies from stronger territories to weaker territories

    for(auto it = this->toAttack().begin(); it!= this->toAttack().end() ; it++){
        for(auto i = it[0]->getAdjacentTerritory().begin(); i != it[0]->getAdjacentTerritory().end(); i++){
            if(i[0]->getOwnerOfTerritory() == this->player){
                int armyDifference = it[0]->getNumberOfArmies() - i[0]->getNumberOfArmies();
                if(armyDifference > 1){
                    this->player->addOrder(new AdvanceOrder(this->player,armyDifference/2,it[0],i[0]));
                }
            }
            
        }

    }

    Hand* playerHand = this->player->getPlayerHand();
    int playerHandSize = playerHand->getHand().size();

    if(playerHandSize > 0){
        for(int i = 0;i< playerHandSize; i++){
            string cardType = playerHand->getHand().at(i)->getType();

            if(cardType == "reinforcement"){
                
                playerHand->getHand().at(i)->play(this->player->getGameDeck(),-1,nullptr,nullptr,nullptr);
                break;
            }else if(cardType == "blockade"){

                playerHand->getHand().at(i)->play(this->player->getGameDeck(),-1,toDefend().at(0),nullptr,nullptr);
                break;
            }else if(cardType == "airlift"){
                if(toDefend().size() > 1){
                    playerHand->getHand().at(i)->play(this->player->getGameDeck(),toDefend().at(1)->getNumberOfArmies(),toDefend().at(0),toDefend().at(1),nullptr);
                    break;
                }
            } else if(cardType == "diplomacy"){
                    Player* opponent;
                    for(auto it = this->toDefend().begin(); it != this->toDefend().end(); it++){
                        for(auto i = it[0]->getAdjacentTerritory().begin(); i != it[0]->getAdjacentTerritory().end(); i++){
                            if(i[0]->getOwnerOfTerritory() != this->player){
                                opponent = i[0]->getOwnerOfTerritory();
                                break;
                            }
                        }

                        if(opponent){
                            break;
                        }
                    }
                playerHand->getHand().at(i)->play(this->player->getGameDeck(),-1,nullptr,nullptr,opponent);
                break;
            }else{
                cout << "Benevolent Player will not use a Bomb Card!" << endl;
                break;
            }
        }


    }else{
        cout << this->player->getName() << " has no Cards to play!"<< endl;
    }


}
/////////////////////////////////////// Neutral Player ////////////////////////////////////////////
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player){
    this->player = player;
    this->strategyName = "neutral";
}
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& oldPlayer){
    this->player = oldPlayer.player;
    this->strategyName = oldPlayer.strategyName;
}
vector <Territory*> NeutralPlayerStrategy::toDefend(){
     std::sort(this->player->getTerritories().begin(),this->player->getTerritories().end(),[](Territory* a, Territory* b) {
        return (a->getNumberOfArmies() < b->getNumberOfArmies());
    });
    return this->player->getTerritories();
}
vector <Territory*> NeutralPlayerStrategy::toAttack(){
    return vector<Territory*>();
}

//Neutral Player never issues or creates any orders

void NeutralPlayerStrategy::issueOrder(){

    cout << this->player->getName() << "'s turn to issue orders!" << endl;
    cout << this->player->getName()<< " is issuing orders ..." << endl;
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
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player){
    this->player = player;
    this->strategyName = "benevolent";
}
vector <Territory*> CheaterPlayerStrategy::toDefend(){

}
vector <Territory*> CheaterPlayerStrategy::toAttack(){

}
void CheaterPlayerStrategy::issueOrder(){
    
}