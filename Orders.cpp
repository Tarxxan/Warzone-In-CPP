#include "Orders.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;
// TODO: ALl the validate methods & description & effect once player is setup
Order::Order(){};
Order::Order(const Order& order){
    this->name = order.name;
    this->description = order.description;
    this->effect = order.effect;
    this->player = order.player;
}
Order::~Order(){}
Order& Order::operator=(const Order& o){
    this->name = o.name;
    this->description = o.description;
    this->effect = o.effect;
    this->player = o.player;
    return *this;
}
//Assignment operator // It can be used to create an object just like the copy constructor
string Order::getName(){
    return this->name;
}
string Order::getDescription(){
    return this->description;
}
string Order::getEffect(){
    return this->effect;
}
Player* Order::getPlayer(){
    return this->player;
}
bool Order::validate(){return true;}
bool Order::execute(){return true;}
std::ostream& operator<<(ostream& strm,Order& o){
    return strm << "Order: " << o.getDescription() << o.getEffect();
}

DeployOrder::DeployOrder(Player* player, int numOfArmies, Territory* destination){
    this->name = "Deploy";
    this->description = "Deploy " + to_string(numOfArmies) + " solders to " + destination->getTerritoryName();
    this->armies = numOfArmies;
    this->player = player;
    this->destination = destination;
}
DeployOrder::DeployOrder(const DeployOrder& deployOrder){
    this->name = deployOrder.name;
    this->description = deployOrder.description;
    this->effect = deployOrder.effect;
    this->armies = deployOrder.armies;
    this->player = deployOrder.player;
    this->destination = deployOrder.destination;
}
DeployOrder::~DeployOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// DeployOrder& DeployOrder::operator=(const DeployOrder& dOrder){
//     this->name = dOrder.name;
//     this->description = dOrder.description;
//     this->effect = dOrder.effect;
//     this->armies = dOrder.armies;
//     this->player = dOrder.player;
//     this->destination = dOrder.destination;
//     return *this;
// }
bool DeployOrder::validate(){
    // TODO: Check members of deploy to be proper aka check if territory belongs to the user and user has that army
    cout << "Deploy Validated for "<< this->armies << " armies\n";
    return true;
}
bool DeployOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are being deployed on " 
                        + this->destination->getTerritoryName();
        return true;
    }
    return false;
}

AdvanceOrder::AdvanceOrder(Player* player, int armies, Territory* source, Territory* destination){
    this->name = "Advance";
    this->description = "Advancing " + to_string(armies) + " solders from " + source->getTerritoryName()
                        + " to " destination->getTerritoryName();
    this->armies = armies;
    this->player = player;
    this->source = source;
    this->destination = destination;
}
AdvanceOrder::AdvanceOrder(const AdvanceOrder& advanceOrder){
    this->name = advanceOrder.name;
    this->description = advanceOrder.description;
    this->effect = advanceOrder.effect;
    this->armies = advanceOrder.armies;
    this->player = advanceOrder.player;
    this->source = advanceOrder.source;
    this->destination = advanceOrder.destination;
}
AdvanceOrder::~AdvanceOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& aOrder){
//     this->name = aOrder.name;
//     this->description = aOrder.description;
//     this->effect = aOrder.effect;
//     this->armies = aOrder.armies;
//     this->player = aOrder.player;
//     this->source = aOrder.source;
//     this->destination = aOrder.destination;
//     return *this;
// }
bool AdvanceOrder::validate(){
    // TODO: check that source belongs to user and that he has the amount or soldiers needed
    // check if source and dest are connected
    cout << "Advance Order is validated\n";
    return true;
}
bool AdvanceOrder::execute(){
    if (validate()){
        // if both territories belong to one user then move if not attack TODO:
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are being advanced from "
                        + this->source->getTerritoryName() + " to " + this->destination->getTerritoryName();
        return true;
    }
    return false;
}

BombOrder::BombOrder(Player* player, Territory* destination){
    this->name = "Bomb";
    this->description = "Bombs half of the army on " + destination->getTerritoryName();
    this->player = player;
    this->destination = destination;
}
BombOrder::BombOrder(const BombOrder& bombOrder){
    this->name = bombOrder.name;
    this->description = bombOrder.description;
    this->effect = bombOrder.effect;
    this->player = bombOrder.player;
    this->destination = bombOrder.destination;
}
BombOrder::~BombOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// BombOrder& BombOrder::operator=(const BombOrder& bOrder){
//     this->name = bOrder.name;
//     this->description = bOrder.description;
//     this->effect = bOrder.effect;
//     this->armies = bOrder.armies;
//     this->player = bOrder.player;
//     this->destination = bOrder.destination;
//     return *this;
// }
bool BombOrder::validate(){
    // TODO check that the destination is adjacent to any territory belonging to the user and that its not his territory
    return false;
}
bool BombOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: half of the army is destroyed on " + this->destination->getTerritoryName();
        return true;
    }
    return false;
}

BlockadeOrder::BlockadeOrder(Player* player, Territory* destination){
    this->name = "Blockade";
    this->description = "Tripples the army on " + destination->getTerritoryName();
    this->player = player;
    this->destination = destination;
}
BlockadeOrder::BlockadeOrder(const BlockadeOrder& blOrder){
    this->name = blOrder.name;
    this->description = blOrder.description;
    this->effect = blOrder.effect;
    this->player = blOrder.player;
    this->destination = blOrder.destination;
}
BlockadeOrder::~BlockadeOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& blOrder){
//     this->name = blOrder.name;
//     this->description = blOrder.description;
//     this->effect = blOrder.effect;
//     this->player = blOrder.player;
//     this->destination = blOrder.destination;
//     return *this;
// }
bool BlockadeOrder::validate(){
    // TODO check that the territory belongs to the user
    return false;
}
bool BlockadeOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: the army is trippled on " + this->destination->getTerritoryName();
        return true;
    }
    return false;
}

AirliftOrder::AirliftOrder(Player* player, int army, Territory* source, Territory* destination){
    this->name = "Airlift";
    this->description = "Advances " + to_string(army) + " solders from " + source->getTerritoryName() +
                        " to " + destination->getTerritoryName() + " even if they are not adjacent";
    this->player = player;
    this->armies = army;
    this->source = source;
    this->destination = destination;
}
AirliftOrder::AirliftOrder(const AirliftOrder& aiOrder){
    this->name = aiOrder.name;
    this->description = aiOrder.description;
    this->effect = aiOrder.effect;
    this->armies = aiOrder.armies;
    this->player = aiOrder.player;
    this->source = aiOrder.source;
    this->destination = aiOrder.destination;
}
AirliftOrder::~AirliftOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// AirliftOrder& AirliftOrder::operator=(const AirliftOrder& aiOrder){
//     this->name = aiOrder.name;
//     this->description = aiOrder.description;
//     this->effect = aiOrder.effect;
//     this->armies = aiOrder.armies;
//     this->player = aiOrder.player;
//     this->destination = aiOrder.destination;
//     this->source = aiOrder.source;
//     return *this;
// }
bool AirliftOrder::validate(){
    // check if source belongs to user and that he has that army on it
    return false;
}
bool AirliftOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are moved from " + 
                        this->source->getTerritoryName() + " to " + this->destination->getTerritoryName();
        return true;
    }
    return false;
}


NegotiateOrder::NegotiateOrder(Player* player, Player* player2){
    this->name = "Negotiate";
    this->description = "Prevent attacks between user1 and user2";
    this->player = player;
    this->second = player2;
}
NegotiateOrder::NegotiateOrder(const NegotiateOrder& nOrder){
    this->name = nOrder.name;
    this->description = nOrder.description;
    this->effect = nOrder.effect;
    this->player = nOrder.player;
    this->second = nOrder.second;
}
NegotiateOrder::~NegotiateOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& nOrder){
//     this->name = nOrder.name;
//     this->description = nOrder.description;
//     this->effect = nOrder.effect;
//     this->player = nOrder.player;
//     this->second = nOrder.second;
//     return *this;
// }
bool NegotiateOrder::validate(){
    // Check that two players exist?
    return false;
}
bool NegotiateOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: no attacks can be done between user1 and user2 until the end of the round";
        return true;
    }
    return false;
}

// ***************************** ORDER LIST ***********************************
OrderList::OrderList(){cout << "Created an empty order list\n";};
std::ostream& operator << (std::ostream& strm,const OrderList& ol) {
    for(Order* order : ol.orderList){
        cout << *order << endl;
    }
  
    return strm << "";
}
void OrderList::push(Order* order){
    orderList.push_back(order);
}
int OrderList::remove(Order *actual){
    int index = 0;
    for(Order* order : this->orderList){
        if(order == actual){
            auto posIt = this->orderList.begin()+index;
            this->orderList.erase(posIt); // will delete the thing we are looking for
            return index;
        }
        index++;
    }
    return -1;
}
// So if True it will move up if false it will move down
bool OrderList::move(Order *order, bool moveUp){
    int index = remove(order);
    if (index == -1){
        cout << "Could not find the element in the list" <<endl;
        return false;
    }
    // If we try to move the first up
    if (index == 0 && (moveUp || this->orderList.size() == 0)){
        this->orderList.insert(this->orderList.begin(), order);
        return true;
    }
    //if we try to move the last one down
    if (index == this->orderList.size() && !moveUp){
        push(order);
        return true;
    }
    if (moveUp){
        this->orderList.insert(this->orderList.begin()+index-1, order);
    }
    else{
        this->orderList.insert(this->orderList.begin()+index+1, order);
    }
    return true;
}
// TOASK: ask TA if we can do this
// This is a more use friendly methods for move which will call move
bool OrderList::moveUp(Order *order){
    return move(order, true);
}
bool OrderList::moveDown(Order *order){
    return move(order, false);
}
