#include "Cards.h"






Order::Order(){};
Order::Order(string type){
    this->name = type;
    this->description = type + " Order";
}
Order::Order(const Order& order){
    this->name = order.name;
    this->description = order.description;
    this->effect = order.effect;
    // this->player = order.player;
}
Order::~Order(){}
Order& Order::operator=(const Order& o){
    this->name = o.name;
    this->description = o.description;
    this->effect = o.effect;
    // this->player = o.player;
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
// Player* Order::getPlayer(){
//     return this->player;
// }
bool Order::validate(){return true;}
bool Order::execute(){return true;}
std::ostream& operator<<(ostream& strm,Order& o){
    return strm << "Order: " << o.getDescription() << o.getEffect();
}






// DUMMY ORDER LIST

OrderList::OrderList(){};
OrderList::~OrderList(){};
OrderList& OrderList::operator=(const OrderList& oList){
    this->orderList = oList.orderList;
    return *this;
}
vector <Order*> OrderList::getOrders(){
    return this->orderList;
}
OrderList::OrderList(const OrderList &copyOL){
    this->orderList = copyOL.orderList;
}
std::ostream& operator << (std::ostream& strm,const OrderList& orderList) {
    for(Order* order : orderList.orderList){
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

// This is a more use friendly methods for move which will call move
bool OrderList::moveUp(Order *order){
    return move(order, true);
}
bool OrderList::moveDown(Order *order){
    return move(order, false);
}
















////////////////////////////////////////// CARD //////////////////////////////////////////////////////
Card::Card(string type){
    this->type = type;
}
Card::~Card(){};
Card::Card(const Card& card){
    this->type = card.type;
    // this->player = card.player;
}
Card& Card::operator=(const Card& card){
    // this->player = card.player;
    this->type = card.type;
    return *this;
}
void Card::setPlayer(Player* player){
    this->player = player;
}
void Card::play(Deck* deck){
    this->player->hand->remove(this);
    cout << this->type << " Card played!\n";
    Order* newOrder = new Order(this->type);
    this->player->orders->push(newOrder);
    deck->push(this);

}
string Card::getType(){
    return this->type;
}
string Card::getPlayerName(){
    return "";
    // return this->player->getName(); // the get Nme doesnt exist yet
}
std::ostream& operator<<(ostream& strm, Card& card){
    return strm << "Card type: " << card.getType() << card.getPlayerName();
}


//////////////////////////////////// HAND ///////////////////////////////////////////////////////
Hand::Hand(){};
vector <Card*> Hand::getHand(){
    return this->hand;
}
Hand::Hand(const Hand& handO){
    this->hand = handO.hand;
}
void Hand::push(Card* card){
    this->hand.push_back(card);
};
void Hand::remove(Card* actual){
    int index = 0;
    for(Card* card : this->hand){
        if(card == actual){
            auto posIt = this->hand.begin()+index;
            this->hand.erase(posIt); // will delete the thing we are looking for
            return;
        }
        index ++;
    }
}
void Hand::fill(Deck* deck){
    for(int i = 0;i<5;i++){
        this->hand.push_back(deck->dummyDraw());
    }
}



std::ostream& operator << (ostream& strm,const Hand& hO){
    for(Card* card : hO.hand){
        cout << *card << endl;
    }
    return strm << "";
}



// Dummy Player class
Player::Player()
{
    name = "";
}

Player::Player(string name)
{
    this->name = name;
    this->orders = new OrderList();
}

void Player::setPlayerName(string s)
{
    this->name = s;
}
void Player::setHand(Hand* newHand){
    this->hand = newHand;
}
Player::~Player(){}

ostream &operator<<(ostream &output, const Player &p)
{
    output << "--Player Name: " << p.name << endl;
    return output;
}
void Player::addCard(Card* card) {
    this->hand->push(card);
}
void Player::fillHand(Deck* deck){
    for(int i = 0;i<5;i++){
        Card* temp = deck->dummyDraw();
        temp->setPlayer(this);
        this->hand->push(temp);
    }
}
void Player::chooseCard(string orderType, Deck* deck){
    for(Card* card : this->hand->getHand()){
        if(card->getType() == orderType){
            card->play(deck);
            return;
        }
    }
    cout << "ORDER TYPE NOT FOUND\n";
}


/////////////////////////////////////// DECK //////////////////////////////////////////////////////
Deck::Deck(){};
vector <Card*> Deck::getDeck(){
    return this->deck;
}
// Deck::Deck(const Deck& deckO){
//     this->deck = deckO.getDeck();
// }
void Deck::initalizeDeck(){
    for(int i = 0; i< 6;i++){
        Card* tempCard = new Card("bomb");
        this->deck.push_back(tempCard);
    }
    for(int i = 0; i< 6;i++){
        Card* tempCard = new Card("reinforcement");
        this->deck.push_back(tempCard);
    }
    for(int i = 0; i< 6;i++){
        Card* tempCard = new Card("blockade");
        this->deck.push_back(tempCard);
    }
    for(int i = 0; i< 6;i++){
        Card* tempCard = new Card("blockade");
        this->deck.push_back(tempCard);
    }
    for(int i = 0; i< 6;i++){
        Card* tempCard = new Card("airlift");
        this->deck.push_back(tempCard);
    }
    for(int i = 0; i< 6;i++){
        Card* tempCard = new Card("diplomacy");
        this->deck.push_back(tempCard);
    }

}
void Deck::push(Card* card){
    this->deck.push_back(card);
}
void Deck::draw(Player* player){
    int index = rand() % this->deck.size();
    auto posIt = this->deck.begin()+index;

    Card* temp = this->deck.at(index);
    this->deck.erase(posIt);
    player->addCard(temp);
    // gets a random card, rem  oves it from the list and assigns it to the players hand
}
Card* Deck::dummyDraw(){
    srand(time(NULL));
    int index = rand() % this->deck.size();
    auto posIt = this->deck.begin()+index;
    Card* temp = this->deck.at(index);
    this->deck.erase(posIt);
    return temp;
}
void Deck::remove(Card* actual){
    int index = 0;
    for(Card* card : this->deck){
        if(card == actual){
            auto posIt = this->deck.begin()+index;
            this->deck.erase(posIt); // will delete the thing we are looking for
            return;
        }
        index ++;
    }
}
std::ostream& operator << (ostream& strm,const Deck& dO){
    for(Card* card : dO.deck){
        cout << *card << endl;
    }
    return strm << "";
}






