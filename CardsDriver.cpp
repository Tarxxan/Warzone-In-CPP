// Driver that creates a deck of cards of all different kinds, then creates a hand object that is
// filled by drawing cards from the deck, then calls the play method of all cards in the hand.
#include <iostream>
#include "Cards.h"
int main()
{

    Player *player1 = new Player("Mark");
    Deck *deck = new Deck();
    Hand *newHand = new Hand();

    deck->initalizeDeck();
    cout << "INITIAL DECK SIZE: " << deck->getDeck().size() << endl;
    player1->setHand(newHand);
    
    cout << "DRAWING CARDS TO FILL HAND\n";
    deck->draw(player1);
    cout << "DREW 1 CARD\t HAND SIZE: " << player1->hand->getHand().size() << endl;
    deck->draw(player1);
    cout << "DREW 1 CARD\t HAND SIZE: " << player1->hand->getHand().size() << endl;
    deck->draw(player1);
    cout << "DREW 1 CARD\t HAND SIZE: " << player1->hand->getHand().size() << endl;
    deck->draw(player1);
    cout << "DREW 1 CARD\t HAND SIZE: " << player1->hand->getHand().size() << endl;
    deck->draw(player1);
    cout << "DREW 1 CARD\t HAND SIZE: " << player1->hand->getHand().size() << endl;
    cout << "-------------------------------\n";
    cout << "CARDS IN HAND: \n";
    cout << *player1->hand;
    cout << "-------------------------------\n";
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "-------------------------------\n";

    Card *currentCard = player1->hand->getHand().at(0);
    cout << "~~~PLAYING CARD IN HAND~~~\n";
    currentCard->play(deck);
    cout << "-------------------------------\n";
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "-------------------------------\n";

    currentCard = player1->hand->getHand().at(0);
    cout << "~~~PLAYING CARD IN HAND~~~\n";
    currentCard->play(deck);
    cout << "-------------------------------\n";
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "-------------------------------\n";

    currentCard = player1->hand->getHand().at(0);
    cout << "~~~PLAYING CARD IN HAND~~~\n";
    currentCard->play(deck);
    cout << "-------------------------------\n";
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "-------------------------------\n";

    currentCard = player1->hand->getHand().at(0);
    cout << "~~~PLAYING CARD IN HAND~~~\n";
    currentCard->play(deck);
    cout << "-------------------------------\n";
    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "-------------------------------\n";

    currentCard = player1->hand->getHand().at(0);
    cout << "~~~PLAYING CARD IN HAND~~~\n";
    currentCard->play(deck);
    cout << "-------------------------------\n";

    cout << "~~~DECK SIZE~~~: " << deck->getDeck().size() << endl;
    cout << "~~~HAND SIZE~~~: " << player1->hand->getHand().size() << endl;
    cout << "-------------------------------\n";
    delete deck;
    cout << "------------------------\n";
    cout << "DISPLAYING PLAYER ORDERLIST\n";
    cout << player1->name << "'s OrderList: \n"
         << *player1->orders;
    cout << "-------------------------------\n";
    delete player1;
}