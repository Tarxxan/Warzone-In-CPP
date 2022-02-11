// Driver that creates a deck of cards of all different kinds, then creates a hand object that is
// filled by drawing cards from the deck, then calls the play method of all cards in the hand.
#include <iostream>
#include "Cards.h"
int main() {
    
    Deck* deck = new Deck();
    deck->initalizeDeck();
    Hand* hand = new Hand();
    hand->fill(deck);
    cout << *hand;
    cout << deck->getDeck().size();


}