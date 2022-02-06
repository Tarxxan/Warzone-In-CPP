#include "Orders.h"
#include <iostream>
#include <string>
using namespace std;

Order::Order(){};
Order::Order(const Order& order){
    this->name = order.name;
    this->description = order.description;
    this->effect = order.effect;
}
Order::~Order(){}
Order& Order::operator=(const Order& o){
    this->name = o.name;
    this->description = o.description;
    this->effect = o.effect;
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
bool Order::validate(){return true;}
bool Order::execute(){return false;}
//ostream& operator<<(ostream& output, const Territory& t)
std::ostream& operator<<(ostream& strm,Order& o){
    return strm << "Order: " << o.getDescription() << o.getEffect();
}

// TODO: Add player & territory
DeployOrder::DeployOrder(int numOfArmies){
    this->name = "Deploy";
    this->description = "Deploy " + to_string(numOfArmies) + " solders to territoty_name";
    this->armies = numOfArmies;
}
DeployOrder::DeployOrder(const DeployOrder& deployOrder){
    this->name = deployOrder.name;
    this->description = deployOrder.description;
    this->effect = deployOrder.effect;
    this->armies = deployOrder.armies;
}
DeployOrder::~DeployOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// DeployOrder& DeployOrder::operator=(const DeployOrder& dOrder){
//     this->name = dOrder.name;
//     this->description = dOrder.description;
//     this->effect = dOrder.effect;
//     this->armies = dOrder.armies;
//     return *this;
// }
bool DeployOrder::validate(){
    // TODO: Check members of deploy to be proper aka check if territory belongs to the user and user has that army
    cout << "Deploy Validated for "<< this->armies << " armies\n";
    return true;
}
bool DeployOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are being deployed on territory_name";
        return true;
    }
    return false;
}

AdvanceOrder::AdvanceOrder(int armies){
    this->name = "Advance";
    this->description = "Advancing " + to_string(armies) + " solders from source to destination";
    this->armies = armies;
}
AdvanceOrder::AdvanceOrder(const AdvanceOrder& advanceOrder){
    this->name = advanceOrder.name;
    this->description = advanceOrder.description;
    this->effect = advanceOrder.effect;
    this->armies = advanceOrder.armies;
}
AdvanceOrder::~AdvanceOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& aOrder){
//     this->name = aOrder.name;
//     this->description = aOrder.description;
//     this->effect = aOrder.effect;
//     this->armies = aOrder.armies;
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
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are being advanced from source to destination";
        return true;
    }
    return false;
}

BombOrder::BombOrder(){
    this->name = "Bomb";
    this->description = "Bombs half of the army on territoty_name";
}
BombOrder::BombOrder(const BombOrder& bombOrder){
    this->name = bombOrder.name;
    this->description = bombOrder.description;
    this->effect = bombOrder.effect;
}
BombOrder::~BombOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// BombOrder& BombOrder::operator=(const BombOrder& bOrder){
//     this->name = bOrder.name;
//     this->description = bOrder.description;
//     this->effect = bOrder.effect;
//     this->armies = bOrder.armies;
//     return *this;
// }
bool BombOrder::validate(){
    // TODO check that the destination is adjacent to any territory belonging to the user and that its not his territory
    return false;
}
bool BombOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: half of the army is destroyed on territory_name";
        return true;
    }
    return false;
}

BlockadeOrder::BlockadeOrder(){
    this->name = "Blockade";
    this->description = "Tripples the army on territoty_name";
}
BlockadeOrder::BlockadeOrder(const BlockadeOrder& blOrder){
    this->name = blOrder.name;
    this->description = blOrder.description;
    this->effect = blOrder.effect;
}
BlockadeOrder::~BlockadeOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& blOrder){
//     this->name = blOrder.name;
//     this->description = blOrder.description;
//     this->effect = blOrder.effect;
//     return *this;
// }
bool BlockadeOrder::validate(){
    // TODO check that the territory belongs to the user
    return false;
}
bool BlockadeOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: the army is trippled on territory_name";
        return true;
    }
    return false;
}

AirliftOrder::AirliftOrder(int army){
    this->name = "Airlift";
    this->description = "Advances " + to_string(army) + " solders from source to destination even if they are not adjacent";
}
AirliftOrder::AirliftOrder(const AirliftOrder& aiOrder){
    this->name = aiOrder.name;
    this->description = aiOrder.description;
    this->effect = aiOrder.effect;
}
AirliftOrder::~AirliftOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// AirliftOrder& AirliftOrder::operator=(const AirliftOrder& aiOrder){
//     this->name = aiOrder.name;
//     this->description = aiOrder.description;
//     this->effect = aiOrder.effect;
//     this->armies = aiOrder.armies;
//     return *this;
// }
bool AirliftOrder::validate(){
    // check if source belongs to user and that he has that army on it
    return false;
}
bool AirliftOrder::execute(){
    if (validate()){
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are moved from source to destination";
        return true;
    }
    return false;
}


NegotiateOrder::NegotiateOrder(){
    this->name = "Negotiate";
    this->description = "Prevent attacks between user1 and user2";
}
NegotiateOrder::NegotiateOrder(const NegotiateOrder& nOrder){
    this->name = nOrder.name;
    this->description = nOrder.description;
    this->effect = nOrder.effect;
}
NegotiateOrder::~NegotiateOrder(){}
// The assignment operator doesnt work for some reason TOASK:
// NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& nOrder){
//     this->name = nOrder.name;
//     this->description = nOrder.description;
//     this->effect = nOrder.effect;
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
// TODO: ask TA if we can do this
// This is a more use friendly methods for move which will call move
bool OrderList::moveUp(Order *order){
    return move(order, true);
}
bool OrderList::moveDown(Order *order){
    return move(order, false);
}
