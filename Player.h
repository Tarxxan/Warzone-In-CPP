#include "GameEngine.h"
class Player {
    public:
        Player(); //Default Constructor
        ~Player();
        Player(int id, string player_name);
        Player& operator=(const Player& order);
        // Player(std::list<Order> orders, std::list<Territory> territories, std::list<Card> cards); // whats that
        
        //getters
        vector <Card*> getHand();
        OrderList* getOrders();
        vector <Territory*> getTerritories();
        string getName();
        int getId(); 

        // TODO: below
        friend ostream& operator<<(ostream& output, const Player& Player); 
        void addCard(Card* card);
        void addTerritory(Territory* territory);
        void addOrder(Order* order);
        // //member functions
        // list<Territory> toDefend(); // return a list of territories that are to be defended
        // list<Territory> toAttack(); //  returns a list of territories that are to be attacked
        //                             // establish an arbitrary list of territories to be defended, and an
        //                             // arbitrary list of territories that are to be attacked.
        // void issueOrder();   //creates an Order object and puts it in the player�s list of orders.
        // bool addTerritory(Territory t);  // return true if territory is successfully added 
        

    private:
        OrderList*  orders;
        vector <Territory*> territories;
        vector <Card*> hand;
        int id;
        string name;
};
