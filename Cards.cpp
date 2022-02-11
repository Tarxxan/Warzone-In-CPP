#include "Cards.h"

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
// void Card::setPlayer(Player* player){
//     this->player = player;
// }
void Card::play(){
    
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
// void Deck::draw(Player* player){
//     int index = rand() % this->deck.size();
//     auto posIt = this->deck.begin()+index;

//     Card* temp = this->deck.at(index);
//     this->deck.erase(posIt);
//     player->addCard(temp);
//     // gets a random card, rem  oves it from the list and assigns it to the players hand
// }
Card* Deck::dummyDraw(){
    srand(time(NULL));
    int index = rand() % this->deck.size();
    auto posIt = this->deck.begin()+index;
    cout << index << endl;
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




