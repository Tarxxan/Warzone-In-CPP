#include "Orders.h"
#include <iostream>
#include <string>
using namespace std;

Order::Order(){};
Order::Order(string name){
    this->name = name;
};
Order::Order(const Order& order){
    this->name = order.name;
    this->effect = order.effect;
};
Order::~Order(){
    cout << "Destructor called";
};
Order& Order::operator=(const Order& o){
    this->name = o.name;
    this->effect = o.effect;
    return *this;
};  
//Assignment operator // It can be used to create an object just like the copy constructor
string Order::getName(){
    return this->name;
};
string Order::getEffect(){
    return this->effect;
};
bool Order::setEffect(string effect){
    this->effect=effect;
    return true;
}; 
bool Order::setDescription(string desc){
    this->description = desc;
    return true;
}
bool Order::validate(){return true;};
bool Order::execute(){return false;}
//ostream& operator<<(ostream& output, const Territory& t)
std::ostream& operator<<(ostream& strm,Order& o){
    // return strm << "Order: " << o.getName() <<"\n Effect: " << o.getEffect() << endl;
    return strm << "Order: " << o.getEffect() << endl;
};
// order classes don't have a parametized constructor for now, but will need to add 
// the params we need to complete that order (map information/armies?)

DeployOrder::DeployOrder(int numOfArmies){
    this->name = "Deploy";
    this->description = "Armies are being deployed";
    this->effect = to_string(numOfArmies) + " solders are being deploeyd to territory_name by player_name"; // TODO : Add in the territory name
    this->armies = numOfArmies;
    cout << "Deploy Order for " << numOfArmies<< " armies created \n";
}
DeployOrder::DeployOrder(const DeployOrder& DeployOrder){
   
}
DeployOrder::~DeployOrder(){
}
bool DeployOrder::validate(){

    cout << "Deploy Validated for "<< this->armies << " armies\n";
    return true;
}
bool DeployOrder::execute(){
    cout << "Deployment of " << this->armies << " armies executed\n";
    return true;
}


AdvanceOrder::AdvanceOrder(){
    this->name = "Advance";
cout << "Advance Order Created\n";
};
AdvanceOrder::~AdvanceOrder(){
}
bool AdvanceOrder::validate(){
    cout << "Advance Order is validated\n";
    return true;
}
bool AdvanceOrder::execute(){
    cout << "Advance Order executed\n";
    return false;
}


BombOrder::~BombOrder(){
}
bool BombOrder::validate(){
    return false;
}
bool BombOrder::execute(){
    return false;
}

BlockadeOrder::~BlockadeOrder(){
}
bool BlockadeOrder::validate(){
    return false;
}
bool BlockadeOrder::execute(){
    return false;
}


AirliftOrder::~AirliftOrder(){
}
bool AirliftOrder::validate(){
    return false;
}
bool AirliftOrder::execute(){
    return false;
}


NegotiateOrder::~NegotiateOrder(){
}
bool NegotiateOrder::validate(){
    return false;
}
bool NegotiateOrder::execute(){
    return false;
}
OrderList::OrderList(){cout << "Created an empty order list\n";};
std::ostream& operator << (std::ostream& strm,const OrderList& ol) {
    for(Order* order : ol.orderList){
        cout << *order << endl;
    }
  
    return strm << "";
};
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
