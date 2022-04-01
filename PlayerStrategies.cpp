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

}
vector <Territory*> BenevolentPlayerStrategy::toAttack(){

}
void BenevolentPlayerStrategy::issueOrder(){
    
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

}
vector <Territory*> NeutralPlayerStrategy::toAttack(){

}
void NeutralPlayerStrategy::issueOrder(){
    
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