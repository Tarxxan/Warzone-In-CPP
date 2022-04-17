#include "Cards.h"
#include <time.h>
class Player;
class Order;
class OrderList;
class Deck;
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
void Card::play(Deck* deck, int armies,Territory* dest,Territory* src,Player* opp) //play the current card by creating a new order, adding the order to the players orderlist.                           // remove the current card from the players hand and add it back to the deck;
{

    
    if(this->type == "reinforcement"){
        this->player->getPlayerHand()->remove(this);
        cout << this->type << " Card played!\n";
        this->player->addAvailableArmies(5);
        this->player = nullptr;
        deck->push(this);

    }else if(this->type == "blockade"){
        this->player->getPlayerHand()->remove(this);
        cout << this->type << " Card played!\n";
        BlockadeOrder* o = new BlockadeOrder(this->player,dest);
        cout << "Blockade order at " << dest->getTerritoryName() << endl;
        this->player->addOrder(o);
        this->player = nullptr;
        deck->push(this);
    }else if(this->type == "airlift"){
        this->player->getPlayerHand()->remove(this);
        cout << this->type << " Card played!\n";
        AirliftOrder* a = new AirliftOrder(this->player,armies,src,dest);
        cout << "Airlift order " << armies << " soldiers from \n" << src->getTerritoryName() << " to \n" << dest->getTerritoryName() << endl;
        this->player->addOrder(a);
        this->player = nullptr;
        deck->push(this);
    }else if(this->type == "diplomacy"){
        this->player->getPlayerHand()->remove(this);
        cout << this->type << " Card played!\n";
        this->player->negotiatePlayer(opp);
        NegotiateOrder* n = new NegotiateOrder(this->player, opp);
        this->player->addOrder(n);
        this->player = nullptr;
        deck->push(this);
    }else{
        this->player->getPlayerHand()->remove(this);
        cout << this->type << " Card played!\n";
        BombOrder* b = new BombOrder(this->player,dest);
        this->player->addOrder(b);
        this->player = nullptr;
        deck->push(this);
    }   



}
string Card::getType()
{
    return this->type;
}
string Card::getPlayerName() // get name of owner of this card
{
    return this->player->getName();
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

/////////////////////////////////////// DECK //////////////////////////////////////////////////////
Deck::Deck(){};                //empty constructor
vector<Card *> Deck::getDeck() //return vector of cards representing the entire deck
{
    return this->deck;
}


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
