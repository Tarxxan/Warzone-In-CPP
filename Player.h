#ifndef PLAYER_H
#define PLAYER_H
using namespace std;
#include <string>
#include "Orders.h"
#include "Cards.h"
#include <vector>
class Player {
    public:
        Player(); //Default Constructor
        Player(int id, string player_name);
        Player(int id, string name, OrderList* orders, vector <Card*> hand, vector <Territory*> territories);
        ~Player();
        
        Player& operator=(const Player& order);
       
        //getters
        vector <Card*> getHand();
        OrderList* getOrders();
        vector <Territory*> getTerritories();
        string getName();
        int getId();
 
 
        friend ostream& operator<<(ostream& output, const Player& Player);
        void addCard(Card* card);
        void addTerritory(Territory* territory);
        void addOrder(Order* order);
        // //member functions
        vector <Territory*> toDefend(); // return a list of territories that are to be defended
        vector <Territory*> toAttack(); //  returns a list of territories that are to be attacked
        //                             // establish an arbitrary list of territories to be defended, and an
        //                             // arbitrary list of territories that are to be attacked.
        void issueOrder(Order* order);   //creates an Order object and puts it in the player�s list of orders.
        // bool addTerritory(Territory t);  // return true if territory is successfully added
       
 
    private:
        OrderList* orders;
        vector <Territory*> territories;
        vector <Card*> hand;
        int id;
        string name;
};
 
 
#endif;