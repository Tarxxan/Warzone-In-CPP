#pragma once
#include <vector>
#include <string>
using namespace std;

// Dummy classes for Player and Territory TODO: Linkage after assignment 1
class Player{
    public:
        Player();
        Player(string name);
        ~Player();
        string getName();
    private:
        string name;
};
class Territory{
    public:
        Territory();
        Territory(string name);
        ~Territory();
        string getTerritoryName();
    private:
        string name;
};

// Order base class for all suborders types
// For assignment 2 TODO: Maybe user should not have access to any members of Order base class as its only to be used by subclasses
class Order{
    public:
        Order();                    // Empty Constructor
        Order(const Order& order);  // Copy Constructor 
        ~Order();                   // Destructor
        Order& operator=(const Order& o);   // Assignment operator - can be used instead of copy constructor
        // Getters
        string getName();           // Returns the name of the player whos order it is
        string getDescription();    // Returns the description of the order
        string getEffect();         // Returns the effect of the order
        Player* getPlayer();        // Returns the player whos order it is
        virtual bool validate();    // A promise that subOrders will implement it
        virtual bool execute();     // A promise that subOrders will implement it
        friend ostream& operator << (ostream &out, const Order &o); // Friend function to print the object  
    protected:
        // Data members
        Player* player;
        string name;
        string effect;
        string description;
};

class DeployOrder : public Order{
    public:
        DeployOrder(Player* player, int numOfArmies, Territory* destination); // Parameter Constructor
        DeployOrder(const DeployOrder& deployOrder);                          // Copy Constructor
        DeployOrder& operator=(const DeployOrder& dOrder);                    // Assignment Operator - can be used as the copy constructor
        ~DeployOrder();                                                       // Destructor
        bool validate();                                                      // Will eventually validate the order
        bool execute();                                                       // execute will call validate method before executing
    private:
        // Data members
        int armies;
        Territory* destination;
};
class AdvanceOrder : public Order{
    public:
        AdvanceOrder(Player* player, int armies, Territory* source, Territory* destination); // Parameter cosntructor
        ~AdvanceOrder();    // Destructor
        AdvanceOrder(const AdvanceOrder& advanceOrder); // Copy constructor
        AdvanceOrder& operator=(const AdvanceOrder& aOrder);    // Assignment operator 
        bool validate();    // Will eventually validate orders
        bool execute();     // Triggers   validation and performs action
    private:
        // Data members
        int armies;
        Territory* source;
        Territory* destination;
};
class BombOrder : public Order{
    public:
        BombOrder(Player* player, Territory* destination);  // Parameter constructor
        BombOrder(const BombOrder& bombOrder);              // Copy constructor
        BombOrder& operator=(const BombOrder& bOrder);      // Assignment operator 
        ~BombOrder();       // Destructor
        bool validate();    // Will eventually validate orders
        bool execute();     // Triggers   validation and performs action
    private:
        // Data members
        Territory * destination;
};
class BlockadeOrder : public Order{
    public:
        BlockadeOrder(Player* player, Territory* destination);  // Parameter constructor
        BlockadeOrder(const BlockadeOrder& blockadeOrder);      // Copy constructor
        BlockadeOrder& operator=(const BlockadeOrder& blOrder); // Assignment operator
        ~BlockadeOrder();   // Destructor
        bool validate();    // Will eventually validate orders
        bool execute();     // Triggers   validation and performs action
    private:
        // Data members
        Territory* destination;
};
class AirliftOrder : public Order{
    public:
        AirliftOrder(Player* player, int army, Territory* source, Territory* destination); // Parameter constructor
        AirliftOrder(const AirliftOrder& AirliftOrder); // Copy Constructor
        ~AirliftOrder();    // Destructor
        AirliftOrder& operator=(const AirliftOrder& aiOrder);   // Assignment operator
        bool validate();    // Will eventually validate orders
        bool execute();     // Triggers   validation and performs action
    private:
        // Data members
        int armies;
        Territory* source;
        Territory* destination;
};
class NegotiateOrder : public Order{

    public:
        NegotiateOrder(Player* player, Player* player2);        // Parameter constructor
        NegotiateOrder(const NegotiateOrder& NegotiateOrder);   // Copy constructor
        NegotiateOrder& operator=(const NegotiateOrder& nOrder);    // Assignment operator
        ~NegotiateOrder();  // Destructor
        bool validate();    // Will eventually validate orders
        bool execute();     // Triggers   validation and performs action
    private:
        // Data members
        Player* second;  
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




