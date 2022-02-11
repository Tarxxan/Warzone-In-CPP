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

class Card{
    public:
        Card(string type);
        Card(const Card& card);
        ~Card();
        Card& operator=(const Card& card);
        void play(); // once played we should somehow get the reference to deck and add it back (and remove from hand)
        // void setPlayer(Player* player); // sets the flag for certain action of player to true
        string getType();
        string getPlayerName();
        // friend ostream& operator << (ostream &out, const Order& );
    private:
        string type;
        // Player* player;
};

class Deck{
    public:
        Deck();
        Deck(const Deck& deck); 
        void initalizeDeck();
        Deck& operator=(const Deck& deckO);
        vector <Card*> getDeck();
        void push(Card* card);
        // void draw(Player* player);
        Card* dummyDraw();
        void remove(Card* card);
        friend std::ostream& operator << (ostream& out,const Deck& ol);
    private:
        vector <Card*> deck;
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