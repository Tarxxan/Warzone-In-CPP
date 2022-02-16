// A Deck object contains a finite collection of Warzone cards.
// Deck has a draw() method that allows a player to draw a card at random from the cards
// remaining in the deck and place it in their hand.

// Once a card has been played, it is removed from the hand and put back into
// the deck.
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Player;
class Deck;

class Order
{
public:
    Order();
    Order(string type);
    Order(const Order &order);
    ~Order();
    Order &operator=(const Order &order);
    string getName();        // For friends methods
    string getDescription(); // For friends methods
    string getEffect();      // For friends methods
    Player *getPlayer();     // For friends methods
    virtual bool validate(); // For suborders
    virtual bool execute();  // For suborders
protected:
    Player *player;
    string name;
    string effect;
    string description;
    friend ostream &operator<<(ostream &out, const Order &);
};

class OrderList
{
public:
    // Empty Constructor
    OrderList();
    ~OrderList();
    // Copy contructor
    OrderList(const OrderList &copyOL);
    //Assignment operator
    OrderList &operator=(const OrderList &assignOL);
    // Inserts an order at the end (as they supposed to)
    vector<Order *> getOrders();
    void push(Order *order);
    // comparing pointers of order
    int remove(Order *order);
    // So if True it will move up if false it will move down
    bool move(Order *order, bool moveUp);
    // This is a more use friendly methods for move which will call move
    bool moveUp(Order *order);
    bool moveDown(Order *order);

    // Streamline Operator
    friend std::ostream &operator<<(ostream &out, const OrderList &ol);
    // friend std::istream& operator >> (istream& in, OrderList& ol);
private:
    vector<Order *> orderList;
};

class Card
{
public:
    Card(string type);                                       // parameter constructor
    Card(const Card &card);                                  //copy constructor
    ~Card();                                                 // deconstructor
    Card &operator=(const Card &card);                       //assignment operator
    void play(Deck *deck);                                   //executes the current card
    void setPlayer(Player *player);                          //sets the player that owns the card
    string getType();                                        //returns the type of card
    string getPlayerName();                                  //returns the name of the owner
    friend ostream &operator<<(ostream &out, const Order &); //prints out the type and owner of the card
private:
    string type;    //identifier for the Card
    Player *player; //Owner of the card
};

class Hand
{
public:
    Hand();                                                       //empty constructor
    Hand(const Hand &hand);                                       // copy constructor
    ~Hand();                                                      // deconstructor
    void push(Card *card);                                        //add card to the hand
    void remove(Card *card);                                      //remove card from the hand
    void fill(Deck *deck);                                        //populate the hand with 5 cards
    vector<Card *> getHand();                                     //return the hand in the form of a vector of cards
    void chooseCard(string orderType, Deck *deck);                //choose a card to play by the type
    friend std::ostream &operator<<(ostream &out, const Hand &h); //print out each card in the hand
private:
    vector<Card *> hand; //the actual hand of cards
};

class Player
{
public:
    string name;
    Player();
    Player(string name);
    ~Player();
    void setPlayerName(string s);
    Hand *hand;
    OrderList *orders;
    void setHand(Hand *newHand);
    void addCard(Card *newCard);
};

class Deck
{
public:
    Deck();                                                        //empty constructor
    Deck(const Deck &deck);                                        //copy constructor
    ~Deck();                                                       //deconstructor
    void initalizeDeck();                                          //populate the entire deck with cards
    Deck &operator=(const Deck &deckO);                            //assignment operator
    vector<Card *> getDeck();                                      //returns entire deck as vector of cards
    void push(Card *card);                                         //add card to deck
    void draw(Player *player);                                     //draw random card from deck
    void remove(Card *card);                                       //remove specific card from deck
    friend std::ostream &operator<<(ostream &out, const Deck &ol); //print out each card in the deck
private:
    vector<Card *> deck; //vector representing deck of cards
};