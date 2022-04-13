#include "GameEngine.h"
#include "Orders.h"
#include <string>
#include <time.h>

class Player;
class Territory;

///////////////////////////////////////////////////// ORDER CLASS /////////////////////////////////
Order::Order(){
    LogObserver *observer = new LogObserver(this);
}; // Empty constructor
Order::Order(const Order& order){ // Parameter Constructor
    LogObserver *observer = new LogObserver(this);
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
string Order::stringToLog(){
    return "Order Executed: " + this->effect;
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
    delete this->player;
    this->player = nullptr;
    delete this->destination;
    this->destination = nullptr;
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
    if (this->destination->getOwnerOfTerritory() == this->player){
        if (this->player->getAvailableArmies() >= this->armies){
            cout << "Deploy Order was validated.\n" << this->destination->getTerritoryName() <<
            " belongs to the user and the user has enough army";
            return true;
        }
        cout << "The user does not have enough solders to perform this operation\n";
        return false;
    }
    cout << "This territory does not belong to the user\n";
    return false;
}
bool DeployOrder::execute(){    // Triggers validate
    this->player->getOrders()->remove(this);
    if (validate()){
        this->effect = "\n"+to_string(this->armies)+" solders are being deployed on " 
                        + this->destination->getTerritoryName() + " by " + this->player->getName();
        this->destination->setNumberOfArmies(this->destination->getNumberOfArmies()+this->armies);
        this->player->removeSolders(this->armies);
        cout << "\nDeploy Order executed\n" << endl;
        Notify(this);
        return true;
    }
    this->effect = this->player->getName() + " was unable to deploy " +to_string(this->armies)+" solders to " + this->destination->getTerritoryName();
    Notify(this);
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
    delete this->player;
    this->player = nullptr;
    delete this->destination;
    this->destination = nullptr;
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
    if (this->source->getOwnerOfTerritory() == this->player){
        if (this->source->isAdjacent(this->destination)){
            if (this->source->getNumberOfArmies() >= this->armies){
                cout << "Advance order validated" << endl;
                return true;
            }
            cout << "Not enough solders on the territory to perform the operation" << endl;
            return false;
        }
        cout << "The 2 territories are not adjacent to each other" << endl;
        return false;
    }
    cout << "The source territory does not belong to the player" << endl;
    return false;
}
bool AdvanceOrder::execute(){   // Triggers validate
    this->player->getOrders()->remove(this);
    if (validate()){
        if (this->destination->getOwnerOfTerritory() == this->player){ // we already know the source belongs to user from validate
            this->effect = "\n"+to_string(this->armies)+" solders are being moved from "
                        + this->source->getTerritoryName() + " to " + this->destination->getTerritoryName()
                        + " by " + this->player->getName();
            this->destination->setNumberOfArmies(this->destination->getNumberOfArmies()+this->armies);
            this->source->setNumberOfArmies(this->source->getNumberOfArmies()-this->armies);
            Notify(this);
            return true;
        }
        this->attack();
        Notify(this);
        return true;
    }
    this->effect = this->player->getName() + " was unable to advance " +to_string(this->armies)+" solders from " + this->source->getTerritoryName() + " to "+ this->destination->getTerritoryName();
    Notify(this);
    return false;
}
void AdvanceOrder::attack(){



    if (!this->player->canAttack(this->destination->getOwnerOfTerritory())){
        cout << "The player cannot attack the opponent as the negotiate card was used" << endl;
        this->effect = "The player cannot attack the opponent as the negotiate card was used";
        return;
    }
    string log =  "Attack is performed between " + this->source->getTerritoryName() + " and "
                + this->destination->getTerritoryName() + "\n " + to_string(this->armies) + " solders against "
                + to_string(this->destination->getNumberOfArmies());
    
    cout << log << endl;

    if(this->destination->getOwnerOfTerritory()->getStrategy()->getName() == "neutral"){
        delete this->destination->getOwnerOfTerritory()->getStrategy();
        this->destination->getOwnerOfTerritory()->setStrategy(new AggressivePlayerStrategy(this->destination->getOwnerOfTerritory()));
        cout << "A neutral player has been attacked and changed into an aggressive player!\n";
    }


    int conquered = 0;
    for (int i = 0; i < this->armies; i++){
        int prob = (rand() % 10) +1 ;
        if (prob <= 6){ // 60% chance of being true
            conquered ++; // One solder more killed
        }
    }
    int defended = 0;
    for (int i = 0; i < this->destination->getNumberOfArmies(); i++){
        int prob = (rand() % 10) +1 ;
        if (prob <= 7){ // 70% chance of being true
            defended ++; // One attacking solder more killed
        }
    }
    if (defended > this->armies){
        defended = this->armies; // Cannot kill more than actually came tothe territory
    }
    if (conquered > this->destination->getNumberOfArmies()){
        conquered = this->destination->getNumberOfArmies();
    }
    cout << to_string(conquered) << " killed by " << this->player->getName() << endl;
    cout << to_string(defended) << " killed by " << this->destination->getOwnerOfTerritory()->getName() << endl;
    this->effect = log;
    if (this->destination->getNumberOfArmies() <= conquered){
        cout << "The territory now belongs to " << this->player->getName();
        this->destination->getOwnerOfTerritory()->removeTerritory(this->destination);
        this->player->addTerritory(this->destination);
        this->destination->setNumberOfArmies(this->armies-defended); // setting the leftover army to this territory
        this->player->drawCard();
        this->source->setNumberOfArmies(this->source->getNumberOfArmies() - defended);
        return;
    }
    cout << this->destination->getOwnerOfTerritory()->getName() << " defended their territory" << endl;
    this->destination->setNumberOfArmies(this->destination->getNumberOfArmies() - conquered);
    this->source->setNumberOfArmies(this->source->getNumberOfArmies() - defended);

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
    delete this->player;
    this->player = nullptr;
    delete this->destination;
    this->destination = nullptr;
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
    if (this->destination->getOwnerOfTerritory() != this->player){
        for (Territory* t : this->player->getTerritories()){
            if (t->isAdjacent(this->destination)){ // Check if any of players territories is adjaccent to the destination territory
                cout << "Bomb order was successfuly validated\n";
                return true;
            }
        }
        cout << "The destination territory is not adjacent to any of the users territories\n";
        return false;
    }
    cout << "The territory belongs to the user, wont bomb.\n";
    return false;
}
bool BombOrder::execute(){ // Will trigger validate method 
    this->player->getOrders()->remove(this);
    if (validate()){
        this->effect = "\nHalf of the army is destroyed on " + this->destination->getTerritoryName()
                        + " by " + this->player->getName();
        
        int future = int(floor(this->destination->getNumberOfArmies()/2));
        this->destination->setNumberOfArmies(future);
        Notify(this);
        return true;
    }
    this->effect = this->player->getName() + " was unable to bomb " + this->destination->getTerritoryName();
    Notify(this);
    return false;
}
//////////////////////////////////////////////// BlockadeOrder /////////////////////////////////////////////////////
BlockadeOrder::BlockadeOrder(Player* player, Territory* destination){   // Parameter constructor
    this->name = "Blockade";
    this->description = "Doubles the army on " + destination->getTerritoryName() + " by " + player->getName();
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
    delete this->player;
    this->player = nullptr;
    delete this->destination;
    this->destination = nullptr;
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
    if (this->destination->getOwnerOfTerritory() == this->player){
        cout << "Blockade order was validated";
        return true;
    }
    cout << "The territory does not belong to the player.\n";
    return false;
}
bool BlockadeOrder::execute(){  // Will trigger validate method
    this->player->getOrders()->remove(this);
    if (validate()){
        this->effect = "\nThe army is doubled on " + this->destination->getTerritoryName()
                        + " by " + this->player->getName();
        this->destination->setNumberOfArmies(this->destination->getNumberOfArmies() * 2);
        Player* neutral = new Player("Neutral");
        this->destination->setOwnerOfTerritory(neutral);
        this->player->removeTerritory(this->destination);
        Notify(this);
        return true;
    }
    this->effect = this->player->getName() + " was unable to blockade " + this->destination->getTerritoryName();
    Notify(this);
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
    delete this->player;
    this->player = nullptr;
    delete this->destination;
    this->destination = nullptr;
    delete this->source;
    this->source = nullptr;
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
    if (this->source->getOwnerOfTerritory() == this->player){
        if (this->destination->getOwnerOfTerritory() == this->player){
            if (this->source->getNumberOfArmies() >= this->armies){
                cout << "Airilift order vallidated" << endl;
                return true;
            }
            cout << "Not enough army to perform this operation" << endl;
            return false;
        }
        cout << "Destination territory does not belong to user" << endl;
        return false;
    }
    cout << "Source territory does not belong to user" << endl;
    return false;
}
bool AirliftOrder::execute(){   // Will trigger validate method
    this->player->getOrders()->remove(this);
    if (validate()){
        this->effect = "\n"+to_string(this->armies)+" solders are moved from " + 
                        this->source->getTerritoryName() + " to " + this->destination->getTerritoryName()
                        + " by " + this->player->getName();
        this->source->setNumberOfArmies(this->source->getNumberOfArmies()-this->armies);
        this->destination->setNumberOfArmies(this->destination->getNumberOfArmies()+this->armies);
        Notify(this);
        return true;
    }
    this->effect = this->player->getName() + " was unable to airlift " +to_string(this->armies)+" solders from " + this->source->getTerritoryName() + " to "+ this->destination->getTerritoryName();
    Notify(this);
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
    delete this->player;
    this->player = nullptr;
    delete this->second;
    this->second = nullptr;
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
    if(this->second == this->player){
        cout << "The two players are the same user" << endl;
        return false;
    }
    cout << "Negotiate Order is validated\n";
    return true;
}
bool NegotiateOrder::execute(){     // Will trigger validate
    this->player->getOrders()->remove(this);
    if (validate()){
        this->effect = "\nNo attacks can be done between " + this->player->getName()
                        + " and " + this->second->getName() + "until the end of the round";
        this->player->negotiatePlayer(this->second);
        this->second->negotiatePlayer(this->player);
        Notify(this);
        return true;
    }
    return false;
}

// ***************************** ORDER LIST ***********************************
OrderList::OrderList(){
    LogObserver *observer = new LogObserver(this);
} // Empty constructor
OrderList::~OrderList(){
    cout << "OrderList Destructor called" << endl;
    for(Order* order : this->orderList){
        delete order;
        order = nullptr;
    }
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
    Notify(this);
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
string OrderList::stringToLog(){
    Order* last_added = this->orderList.back();
    return "Added order: " + last_added->getDescription();
}
