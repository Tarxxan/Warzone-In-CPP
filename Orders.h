#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Dummy Player (to link after demo properly)
class Player
{
    public:
        string name;
        Player();
        Player(string name);
        Player& operator=(const Player& player);
        friend ostream& operator << (ostream &out, const Player &p );
};
// Dummy territory
class Territory
{
    public:
        string name;
        Territory();
        Territory(string name);
        Territory& operator=(const Territory& territory);
        friend ostream& operator << (ostream &out, const Territory &p );
};
class Order{
    public:
        Order();
        Order(const Order& order);
        ~Order();
        Order& operator=(const Order& order);
        string getName();           // For friends methods
        string getDescription();    // For friends methods
        string getEffect();         // For friends methods
        Player* getPlayer();         // For friends methods
        virtual bool validate(); // For suborders
        virtual bool execute(); // For suborders
        friend ostream& operator << (ostream &out, const Order &o);
    protected:
        Player* player;
        string name;
        string effect;
        string description;
};

class DeployOrder : public Order{
    public:
        DeployOrder(Player* player, int numOfArmies, Territory* destination);
        DeployOrder(const DeployOrder& deployOrder);
        DeployOrder& operator=(const DeployOrder& dOrder);
        ~DeployOrder();
        bool validate();
        bool execute(); // execute will call validate method before executing
    private:
        int armies;
        Territory* destination;
};
class AdvanceOrder : public Order{
    public:
        AdvanceOrder(Player* player, int armies, Territory* source, Territory* destination);
        ~AdvanceOrder();
        AdvanceOrder(const AdvanceOrder& advanceOrder);
        AdvanceOrder& operator=(const AdvanceOrder& aOrder);
        bool validate();
        bool execute();
    private:
        int armies;
        Territory* source;
        Territory* destination;
};
class BombOrder : public Order{
    public:
        BombOrder(Player* player, Territory* destination);
        BombOrder(const BombOrder& bombOrder);
        BombOrder& operator=(const BombOrder& bOrder);
        ~BombOrder();
        bool validate();
        bool execute();
    private:
        Territory * destination;
};
class BlockadeOrder : public Order{
    public:
        BlockadeOrder(Player* player, Territory* destination);
        BlockadeOrder(const BlockadeOrder& blockadeOrder);
        ~BlockadeOrder();
        BlockadeOrder& operator=(const BlockadeOrder& blOrder);
        bool validate();
        bool execute();
    private:
        Territory* destination;
};
class AirliftOrder : public Order{
    public:
        AirliftOrder(Player* player, int army, Territory* source, Territory* destination); 
        AirliftOrder(const AirliftOrder& AirliftOrder);
        ~AirliftOrder();
        AirliftOrder& operator=(const AirliftOrder& aiOrder);
        bool validate();
        bool execute();
    private:
        int armies;
        Territory* source;
        Territory* destination;
};
class NegotiateOrder : public Order{

    public:
        NegotiateOrder(Player* player, Player* player2);
        NegotiateOrder(const NegotiateOrder& NegotiateOrder);
        ~NegotiateOrder();
        NegotiateOrder& operator=(const NegotiateOrder& nOrder);
        bool validate();
        bool execute();
    private:
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




