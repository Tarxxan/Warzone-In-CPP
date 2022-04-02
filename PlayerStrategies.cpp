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


   
}
vector <Territory*> HumanPlayerStrategy::toAttack(){

}
void HumanPlayerStrategy::issueOrder(){

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

    for(auto it = this->toAttack().begin(); it!= this->toAttack().end(); it++){
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

            // if(cardType == "reinforcement"){
                

            //     playerHand->getHand().at(i)->play()

            // }else if(cardType == "blockade"){

            //     playerHand->getHand().at(i)->play()
            // }else if(cardType == "airlift"){


            //     playerHand->getHand().at(i)->play()
            // } else if("diplomacy"){



            //     playerHand->getHand().at(i)->play()
            // }else{
            //     break;
            // }
        }


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