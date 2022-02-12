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
#include "Orders.h"
#include "Player.h"
using namespace std;

class Order;
class Player;
class Deck;
/*
class Order{
    public:
        Order();
        Order(string type);
        Order(const Order& order);
        ~Order();
        Order& operator=(const Order& order);
        string getName();           // For friends methods
        string getDescription();    // For friends methods
        string getEffect();         // For friends methods
        Player* getPlayer();         // For friends methods
        virtual bool validate(); // For suborders
        virtual bool execute(); // For suborders
    protected:
        Player* player;
        string name;
        string effect;
        string description;
        friend ostream& operator << (ostream &out, const Order& );
};


class OrderList{
    public:
        // Empty Constructor
        OrderList();
        ~OrderList();
        // Copy contructor
        OrderList(const OrderList &copyOL);
        //Assignment operator 
        OrderList &operator=(const OrderList &assignOL);
        // Inserts an order at the end (as they supposed to)
        vector <Order*> getOrders();
        void push(Order *order);
        // comparing pointers of order
        int remove(Order *order);
        // So if True it will move up if false it will move down
        bool move(Order *order, bool moveUp);
        // This is a more use friendly methods for move which will call move
        bool moveUp(Order *order);
        bool moveDown(Order *order);
        
        // Streamline Operator
        friend std::ostream& operator << (ostream& out,const OrderList& ol);
        // friend std::istream& operator >> (istream& in, OrderList& ol);
    private:
        vector <Order*> orderList;
};
*/

class Card{
    public:
        Card(string type);
        Card(const Card& card);
        ~Card();
        Card& operator=(const Card& card);
        void play(Deck* deck); // once played we should somehow get the reference to deck and add it back (and remove from hand)
        void setPlayer(Player* player); // sets the flag for certain action of player to true
        string getType();
        string getPlayerName();
        friend ostream& operator << (ostream &out, const Order& );
    private:
        string type;
        Player* player;
};

class Hand{
    public:
        Hand();
        Hand(const Hand& hand);
        vector <Card*> getHand();
        void push(Card* card);
        void remove(Card* card);
        void fill(Deck* deck);
        friend std::ostream& operator << (ostream& out,const Hand& h);
    private:
        vector <Card*> hand;
};

class Deck {
public:
    Deck();
    Deck(const Deck& deck);
    void initalizeDeck();
    Deck& operator=(const Deck& deckO);
    vector <Card*> getDeck();
    void push(Card* card);
    void draw(Player* player);
    Card* dummyDraw();
    void remove(Card* card);
    friend std::ostream& operator << (ostream& out, const Deck& ol);
private:
    vector <Card*> deck;
};



/*
class Player
{
public:
    string name;
    Player();
    Player(string name);
    ~Player();
    void setPlayerName(string s);
    Hand* hand;
    OrderList* orders;
    void setHand(Hand *newHand);
    void addCard(Card *newCard);
    void fillHand(Deck* deck);
    void chooseCard(string orderType,Deck* deck);
};
*/


