#include "GameEngine.h"
#include "Orders.h"
// Dummy classes
Player::Player(){};
Player::Player(string name){
    this->name = name;
}
Player::~Player(){
    cout << "Player Destructor called" << endl;
}
string Player::getName(){
    return this->name;
}
Territory::Territory(){};
Territory::Territory(string name){
    this->name = name;
}
Territory::~Territory(){
    cout << "Territory Destructor called" << endl;
}
string Territory::getTerritoryName(){
    return this->name;
}

///////////////////////////////////////////////////// ORDER CLASS /////////////////////////////////
Order::Order(){}; // Empty constructor
Order::Order(const Order& order){ // Parameter Constructor
    this->name = order.name;
    this->description = order.description;
    this->effect = order.effect;
    this->player = order.player;
}
Order::~Order(){
    cout << "Order Destructor called" << endl;
}                // Destructor
Order& Order::operator=(const Order& o){ // Assignment Operator
    this->name = o.name;
    this->description = o.description;
    this->effect = o.effect;
    this->player = o.player;
    return *this;
}
// Getters
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
// Promise that they will be reinitialized in sub orders
bool Order::validate(){return true;}
bool Order::execute(){return true;}
// Friend method to print order's description and effect
std::ostream& operator<<(ostream& out, const Order& o){
    return out << "Order: " << o.description << o.effect;
}
//////////////////////////////////////////////////// DeployOrder /////////////////////////////////////////////////////
DeployOrder::DeployOrder(Player* player, int numOfArmies, Territory* destination){ // Parameter Constructor
    this->name = "Deploy";
    this->description = "Deploy " + to_string(numOfArmies) + " solders to " + destination->getTerritoryName()
                        + " by " + player->getName();
    this->armies = numOfArmies;
    this->player = player;
    this->destination = destination;
}
DeployOrder::DeployOrder(const DeployOrder& deployOrder){   // Copy Constructor
    this->name = deployOrder.name;
    this->description = deployOrder.description;
    this->effect = deployOrder.effect;
    this->armies = deployOrder.armies;
    this->player = deployOrder.player;
    this->destination = deployOrder.destination;
}
DeployOrder::~DeployOrder(){
    cout << "DeployOrder Destructor called" << endl;
}   // Destructor
DeployOrder& DeployOrder::operator=(const DeployOrder& dOrder){ // Assignment Operator
    this->name = dOrder.name;
    this->description = dOrder.description;
    this->effect = dOrder.effect;
    this->armies = dOrder.armies;
    this->player = dOrder.player;
    this->destination = dOrder.destination;
    return *this;
}
bool DeployOrder::validate(){
    // TODO: Check members of deploy to be proper aka check if territory belongs to the user and user has that army
    cout << "Deploy Validated for "<< this->armies << " armies\n";
    return true;
}
bool DeployOrder::execute(){    // Triggers validate
    if (validate()){
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are being deployed on " 
                        + this->destination->getTerritoryName() + " by " + this->player->getName();
        return true;
    }
    return false;
}
/////////////////////////////////////////////////// AdvanceOrder ////////////////////////////////////////////////////
AdvanceOrder::AdvanceOrder(Player* player, int armies, Territory* source, Territory* destination){  // Parameter constructor
    this->name = "Advance";
    this->description = "Advancing " + to_string(armies) + " solders from " + source->getTerritoryName()
                        + " to " + destination->getTerritoryName() + " by " + player->getName();
    this->armies = armies;
    this->player = player;
    this->source = source;
    this->destination = destination;
}
AdvanceOrder::AdvanceOrder(const AdvanceOrder& advanceOrder){   // Copy constructor
    this->name = advanceOrder.name;
    this->description = advanceOrder.description;
    this->effect = advanceOrder.effect;
    this->armies = advanceOrder.armies;
    this->player = advanceOrder.player;
    this->source = advanceOrder.source;
    this->destination = advanceOrder.destination;
}
AdvanceOrder::~AdvanceOrder(){
    cout << "AdvanceOrder Destructor called" << endl;
} // Destructor
AdvanceOrder& AdvanceOrder::operator=(const AdvanceOrder& aOrder){  // Assignment operator
    this->name = aOrder.name;
    this->description = aOrder.description;
    this->effect = aOrder.effect;
    this->armies = aOrder.armies;
    this->player = aOrder.player;
    this->source = aOrder.source;
    this->destination = aOrder.destination;
    return *this;
}
bool AdvanceOrder::validate(){
    // TODO: check that source belongs to user and that he has the amount or soldiers needed
    // check if source and dest are connected
    cout << "Advance Order is validated\n";
    return true;
}
bool AdvanceOrder::execute(){   // Triggers validate
    if (validate()){
        // if both territories belong to one user then move if not attack TODO:
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are being advanced from "
                        + this->source->getTerritoryName() + " to " + this->destination->getTerritoryName()
                        + " by " + this->player->getName();
        return true;
    }
    return false;
}
/////////////////////////////////////////////////// BombOrder //////////////////////////////////////////////////////
BombOrder::BombOrder(Player* player, Territory* destination){   // Parameter constructor
    this->name = "Bomb";
    this->description = "Bombs half of the army on " + destination->getTerritoryName() + " by " + player->getName();
    this->player = player;
    this->destination = destination;
}
BombOrder::BombOrder(const BombOrder& bombOrder){   // Copy constructor
    this->name = bombOrder.name;
    this->description = bombOrder.description;
    this->effect = bombOrder.effect;
    this->player = bombOrder.player;
    this->destination = bombOrder.destination;
}
BombOrder::~BombOrder(){
    cout << "BombOrder Destructor called" << endl;
}   // Destructor 
BombOrder& BombOrder::operator=(const BombOrder& bOrder){   // Assignment operator
    this->name = bOrder.name;
    this->description = bOrder.description;
    this->effect = bOrder.effect;
    this->player = bOrder.player;
    this->destination = bOrder.destination;
    return *this;
}
bool BombOrder::validate(){
    // TODO check that the destination is adjacent to any territory belonging to the user and that its not his territory
    cout << "Bomb Order is validated\n";
    return true;
}
bool BombOrder::execute(){ // Will trigger validate method 
    if (validate()){
        this->effect = "\nEffect: half of the army is destroyed on " + this->destination->getTerritoryName()
                        + " by " + this->player->getName();
        return true;
    }
    return false;
}
//////////////////////////////////////////////// BlockadeOrder /////////////////////////////////////////////////////
BlockadeOrder::BlockadeOrder(Player* player, Territory* destination){   // Parameter constructor
    this->name = "Blockade";
    this->description = "Tripples the army on " + destination->getTerritoryName() + " by " + player->getName();
    this->player = player;
    this->destination = destination;
}
BlockadeOrder::BlockadeOrder(const BlockadeOrder& blOrder){     // Copy constructor
    this->name = blOrder.name;
    this->description = blOrder.description;
    this->effect = blOrder.effect;
    this->player = blOrder.player;
    this->destination = blOrder.destination;
}
BlockadeOrder::~BlockadeOrder(){
    cout << "BlockadeOrder Destructor called" << endl;
}       // Destructor
BlockadeOrder& BlockadeOrder::operator=(const BlockadeOrder& blOrder){  // Assignment operator
    this->name = blOrder.name;
    this->description = blOrder.description;
    this->effect = blOrder.effect;
    this->player = blOrder.player;
    this->destination = blOrder.destination;
    return *this;
}
bool BlockadeOrder::validate(){
    // TODO check that the territory belongs to the user
    cout << "Blockade Order is validated\n";
    return true;
}
bool BlockadeOrder::execute(){  // Will trigger validate method
    if (validate()){
        this->effect = "\nEffect: the army is trippled on " + this->destination->getTerritoryName()
                        + " by " + this->player->getName();
        return true;
    }
    return false;
}
////////////////////////////////////////////// AirliftOrder /////////////////////////////////////////////////////
AirliftOrder::AirliftOrder(Player* player, int army, Territory* source, Territory* destination){    // Parameter constructor
    this->name = "Airlift";
    this->description = "Advances " + to_string(army) + " solders from " + source->getTerritoryName() +
                        " to " + destination->getTerritoryName() + " even if they are not adjacent";
    this->player = player;
    this->armies = army;
    this->source = source;
    this->destination = destination;
}
AirliftOrder::AirliftOrder(const AirliftOrder& aiOrder){    // Copy constructor
    this->name = aiOrder.name;
    this->description = aiOrder.description;
    this->effect = aiOrder.effect;
    this->armies = aiOrder.armies;
    this->player = aiOrder.player;
    this->source = aiOrder.source;
    this->destination = aiOrder.destination;
}
AirliftOrder::~AirliftOrder(){
    cout << "AirliftOrder Destructor called" << endl;
} // Destructor
AirliftOrder& AirliftOrder::operator=(const AirliftOrder& aiOrder){ // Assignment operator
    this->name = aiOrder.name;
    this->description = aiOrder.description;
    this->effect = aiOrder.effect;
    this->armies = aiOrder.armies;
    this->player = aiOrder.player;
    this->destination = aiOrder.destination;
    this->source = aiOrder.source;
    return *this;
}
bool AirliftOrder::validate(){
    // check if source belongs to user and that he has that army on it
    cout << "Airlift Order is validated\n";
    return true;
}
bool AirliftOrder::execute(){   // Will trigger validate method
    if (validate()){
        this->effect = "\nEffect: "+to_string(this->armies)+" solders are moved from " + 
                        this->source->getTerritoryName() + " to " + this->destination->getTerritoryName()
                        + " by " + this->player->getName();
        return true;
    }
    return false;
}
///////////////////////////////////////////// NegotiateOrder ///////////////////////////////////////////////////
NegotiateOrder::NegotiateOrder(Player* player, Player* player2){    // Parameter constructor
    this->name = "Negotiate";
    this->description = "Prevent attacks between " + player->getName() + " and " + player2->getName();
    this->player = player;
    this->second = player2;
}
NegotiateOrder::NegotiateOrder(const NegotiateOrder& nOrder){   // Copy constructor
    this->name = nOrder.name;
    this->description = nOrder.description;
    this->effect = nOrder.effect;
    this->player = nOrder.player;
    this->second = nOrder.second;
}
NegotiateOrder::~NegotiateOrder(){
    cout << "NegotiateOrder Destructor called" << endl;
} // Destructor
NegotiateOrder& NegotiateOrder::operator=(const NegotiateOrder& nOrder){    // Assignment oprator
    this->name = nOrder.name;
    this->description = nOrder.description;
    this->effect = nOrder.effect;
    this->player = nOrder.player;
    this->second = nOrder.second;
    return *this;
}
bool NegotiateOrder::validate(){
    // Check that two players exist?
    cout << "Negotiate Order is validated\n";
    return true;
}
bool NegotiateOrder::execute(){     // Will trigger validate
    if (validate()){
        this->effect = "\nEffect: no attacks can be done between " + this->player->getName()
                        + " and " + this->second->getName() + "until the end of the round";
        return true;
    }
    return false;
}

// ***************************** ORDER LIST ***********************************
OrderList::OrderList(){cout << "Created an empty order list\n";} // Empty constructor
OrderList::~OrderList(){
    cout << "OrderList Destructor called" << endl;
};  // Destructor
OrderList& OrderList::operator=(const OrderList& oList){    // Assignment operator
    this->orderList = oList.orderList;
    return *this;
}
// Getter
vector <Order*> OrderList::getOrders(){
    return this->orderList;
}
OrderList::OrderList(const OrderList &copyOL){  // Copy constructor
    this->orderList = copyOL.orderList;
}
std::ostream& operator << (std::ostream& strm,const OrderList& orderList) { // Assignment operator
    for(Order* order : orderList.orderList){
        cout << *order << endl;
    }
  
    return strm << "";
}
// Pushes the elemnt to the end of list
void OrderList::push(Order* order){
    orderList.push_back(order);
}
// Removes an element from the list
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

// This is a more use friendly methods for move which will call move
bool OrderList::moveUp(Order *order){
    return move(order, true);
}
bool OrderList::moveDown(Order *order){
    return move(order, false);
}
