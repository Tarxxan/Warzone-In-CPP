#include "Cards.h"
#include <time.h>
//Dummy Order class

Order::Order(){};
Order::Order(string type)
{
    this->name = type;
    this->description = type + " Order";
}
Order::Order(const Order &order)
{
    this->name = order.name;
    this->description = order.description;
    this->effect = order.effect;
    this->player = order.player;
}
Order::~Order() {}
Order &Order::operator=(const Order &o)
{
    this->name = o.name;
    this->description = o.description;
    this->effect = o.effect;
    this->player = o.player;
    return *this;
}
//Assignment operator // It can be used to create an object just like the copy constructor
string Order::getName()
{
    return this->name;
}
string Order::getDescription()
{
    return this->description;
}
string Order::getEffect()
{
    return this->effect;
}
Player *Order::getPlayer()
{
    return this->player;
}
bool Order::validate() { return true; }
bool Order::execute() { return true; }
std::ostream &operator<<(ostream &strm, Order &o)
{
    return strm << "Order: " << o.getDescription() << o.getEffect();
}

// DUMMY ORDER LIST

OrderList::OrderList(){};
OrderList::~OrderList(){};
OrderList &OrderList::operator=(const OrderList &oList)
{
    this->orderList = oList.orderList;
    return *this;
}
vector<Order *> OrderList::getOrders()
{
    return this->orderList;
}
OrderList::OrderList(const OrderList &copyOL)
{
    this->orderList = copyOL.orderList;
}
std::ostream &operator<<(std::ostream &strm, const OrderList &orderList)
{
    for (Order *order : orderList.orderList)
    {
        cout << *order << endl;
    }

    return strm << "";
}
void OrderList::push(Order *order)
{
    orderList.push_back(order);
}
int OrderList::remove(Order *actual)
{
    int index = 0;
    for (Order *order : this->orderList)
    {
        if (order == actual)
        {
            auto posIt = this->orderList.begin() + index;
            this->orderList.erase(posIt); // will delete the thing we are looking for
            return index;
        }
        index++;
    }
    return -1;
}
// So if True it will move up if false it will move down
bool OrderList::move(Order *order, bool moveUp)
{
    int index = remove(order);
    if (index == -1)
    {
        cout << "Could not find the element in the list" << endl;
        return false;
    }
    // If we try to move the first up
    if (index == 0 && (moveUp || this->orderList.size() == 0))
    {
        this->orderList.insert(this->orderList.begin(), order);
        return true;
    }
    //if we try to move the last one down
    if (index == this->orderList.size() && !moveUp)
    {
        push(order);
        return true;
    }
    if (moveUp)
    {
        this->orderList.insert(this->orderList.begin() + index - 1, order);
    }
    else
    {
        this->orderList.insert(this->orderList.begin() + index + 1, order);
    }
    return true;
}

// This is a more use friendly methods for move which will call move
bool OrderList::moveUp(Order *order)
{
    return move(order, true);
}
bool OrderList::moveDown(Order *order)
{
    return move(order, false);
}

////////////////////////////////////////// CARD //////////////////////////////////////////////////////

Card::Card(string type) //parameter constructor
{
    this->type = type;
}

Card::~Card() //deconstructor
{
    cout << "Card Deconstructor Called\n";
};
Card::Card(const Card &card) //copy constructor
{
    this->type = card.type;
    this->player = card.player;
}
Card &Card::operator=(const Card &card) //assignment operator
{
    this->player = card.player;
    this->type = card.type;
    return *this;
}
void Card::setPlayer(Player *player) //assign player to Card
{
    this->player = player;
}
void Card::play(Deck *deck) //play the current card by creating a new order, adding the order to the players orderlist.
                            // remove the current card from the players hand and add it back to the deck;
{

    this->player->hand->remove(this);
    cout << this->type << " Card played!\n";
    Order *newOrder = new Order(this->type);
    this->player->orders->push(newOrder);
    deck->push(this);
}
string Card::getType()
{
    return this->type;
}
string Card::getPlayerName() // get name of owner of this card
{
    return this->player->name;
}
std::ostream &operator<<(ostream &strm, Card &card) //print the card's type and the current owner;
{
    return strm << "Card type: " << card.getType() << "\tOwner: " << card.getPlayerName();
}

//////////////////////////////////// HAND ///////////////////////////////////////////////////////

Hand::Hand(){}; //empty constructor

Hand::Hand(const Hand &handO) //copy constructor
{
    this->hand = handO.hand;
}
Hand::~Hand() //deconstructor
{
    if (this->hand.size() != 0)
    {
        for (int i = 0; i < hand.size(); i++)
        {
            delete hand.at(i);
        }
    }

    hand.clear();
    cout << "Hand Deconstructor Called";
}
void Hand::push(Card *card) //add card to current hand
{
    this->hand.push_back(card);
};
void Hand::remove(Card *actual) //remove card from current hand
{
    int index = 0;
    for (Card *card : this->hand)
    {
        if (card == actual)
        {
            auto posIt = this->hand.begin() + index;
            this->hand.erase(posIt); // will delete the thing we are looking for
            return;
        }
        index++;
    }
}

vector<Card *> Hand::getHand()
{ //return the vector of cards representing the hand
    return this->hand;
}

void Hand::chooseCard(string orderType, Deck *deck) //select card and play it by inputing the type
{
    for (Card *card : hand)
    {
        if (card->getType() == orderType)
        {
            card->play(deck);
            return;
        }
    }
    cout << "ORDER TYPE NOT FOUND\n";
}

std::ostream &operator<<(ostream &strm, const Hand &hO) // print out each card in the hand
{
    for (Card *card : hO.hand)
    {
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
void Player::setHand(Hand *newHand)
{
    this->hand = newHand;
}
Player::~Player()
{
    delete this->hand;
    cout << "Player Deconstructor Called\n";
}

ostream &operator<<(ostream &output, const Player &p)
{
    output << "--Player Name: " << p.name << endl;
    return output;
}
void Player::addCard(Card *card)
{
    this->hand->push(card);
}

/////////////////////////////////////// DECK //////////////////////////////////////////////////////
Deck::Deck(){};                //empty constructor
vector<Card *> Deck::getDeck() //return vector of cards representing the entire deck
{
    return this->deck;
}
// Deck::Deck(const Deck& deckO){
//     this->deck = deckO.getDeck();
// }

Deck::~Deck()
{ //deconstructor
    for (int i = 0; i < deck.size(); i++)
    {
        delete deck.at(i);
    }
    deck.clear();

    cout << "Deck Deconstructor called\n";
}
void Deck::initalizeDeck() //populate the entire deck with 6 cards of each type;
{
    for (int i = 0; i < 6; i++)
    {
        Card *tempCard = new Card("bomb");
        this->deck.push_back(tempCard);
    }
    for (int i = 0; i < 6; i++)
    {
        Card *tempCard = new Card("reinforcement");
        this->deck.push_back(tempCard);
    }
    for (int i = 0; i < 6; i++)
    {
        Card *tempCard = new Card("blockade");
        this->deck.push_back(tempCard);
    }
    for (int i = 0; i < 6; i++)
    {
        Card *tempCard = new Card("blockade");
        this->deck.push_back(tempCard);
    }
    for (int i = 0; i < 6; i++)
    {
        Card *tempCard = new Card("airlift");
        this->deck.push_back(tempCard);
    }
    for (int i = 0; i < 6; i++)
    {
        Card *tempCard = new Card("diplomacy");
        this->deck.push_back(tempCard);
    }
}
void Deck::push(Card *card) //add card to the deck
{
    this->deck.push_back(card);
}
void Deck::draw(Player *player) //draw a random card from the deck and add it to the player's hand;
{
    srand(time(NULL));
    int index = rand() % this->deck.size();
    auto posIt = this->deck.begin() + index;
    Card *temp = this->deck.at(index);
    this->deck.erase(posIt);
    temp->setPlayer(player);
    player->addCard(temp);
}

void Deck::remove(Card *actual) //remove specific card from the deck
{
    int index = 0;
    for (Card *card : this->deck)
    {
        if (card == actual)
        {
            auto posIt = this->deck.begin() + index;
            this->deck.erase(posIt); // will delete the thing we are looking for
            return;
        }
        index++;
    }
}
std::ostream &operator<<(ostream &strm, const Deck &dO) // print out each card in the deck;
{
    for (Card *card : dO.deck)
    {
        cout << *card << endl;
    }
    return strm << "";
}
