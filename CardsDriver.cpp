// Driver that creates a deck of cards of all different kinds, then creates a hand object that is
// filled by drawing cards from the deck, then calls the play method of all cards in the hand.
#include <iostream>
#include "Cards.h"
#include "Player.h"
/*
int main() {
    
    Player* player1 = new Player("Mark");
    Deck* deck = new Deck();
    Hand* newHand = new Hand();
    string cardInput;
    deck->initalizeDeck();
    cout << "INITIAL DECK SIZE: " << deck->getDeck().size() << endl;
    player1->setHand(newHand);
    player1->fillHand(deck);
    cout << "Filling " << player1->name<< "'s Hand with Cards\nCARDS IN HAND: \n";
    cout << *player1->hand;
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "CHOOSE CARD: ";
    cin >> cardInput;
    player1->chooseCard(cardInput, deck);
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "CHOOSE CARD: ";
    cin >> cardInput;
    player1->chooseCard(cardInput, deck);
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "CHOOSE CARD: ";
    cin >> cardInput;
    player1->chooseCard(cardInput, deck);
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "CHOOSE CARD: ";
    cin >> cardInput;
    player1->chooseCard(cardInput, deck);
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "CHOOSE CARD: ";
    cin >> cardInput;
    player1->chooseCard(cardInput, deck);
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "------------------------\n";
    cout << player1->name << "'s OrderList: \n" << *player1->orders;

}*/