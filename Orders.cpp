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
// order classes don't have a parametized constructor for now, but will need to add 
// the params we need to complete that order (map information/armies?)

DeployOrder::DeployOrder(int numOfArmies){
    this->armies = numOfArmies;
    this->effect = "Armies Deployed";
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

// once order is executed we will have to change the effect (so basically what happened)
// The Order class implements a stream insertion operator that outputs a string describing the
// order. If the order has been executed, it should also output the effect of the order, stored as a
// string.
//ostream& operator<<(ostream& output, const Territory& t)
std::ostream& operator<<(ostream& strm,Order& o){
    return strm << "Order: " << o.getName() <<"\n Effect: " << o.getEffect() << endl;
};
OrderList::OrderList(){cout << "Empty Order List\n";};
// std::ostream& operator << (std::ostream& strm,const OrderList& ol) {
//     for (int i = 0; i < ol.orderList->size(); i++){
//             string temp = ol.orderList[i];
// 	       cout << ol << endl;
// 	}
  
//     return strm << "A(";
// };
void OrderList::push(Order* order){
    // AdvanceOrder* temp = new AdvanceOrder();
    // Order* temp2 = new Order();
    orderList.push_back(order);

}
void OrderList::getHead(){
    
    orderList.back()->validate();
    orderList.front()->validate();
    orderList.back()->execute();
    orderList.front()->execute();
}
// // class OrderList{
// //     OrderList(){
// //         cout << "empty constructor";
// //     }
// //     void push(Order* order){
// //         cout << "push";
// //     }
// // };
