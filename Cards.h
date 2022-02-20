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
#include "Player.h"
#include "Orders.h"

using namespace std;

class Player;
class Order;
class OrderList;
class Deck;

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