#pragma once
#include "Map.h"
#include "Player.h"
#include "Map.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;
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
    protected:
        Player* player;
        string name;
        string effect;
        string description;
        friend ostream& operator << (ostream &out, const Order& );
};

class DeployOrder : public Order{
    public:
        DeployOrder(Player* player, int numOfArmies, Territory* destination);
        DeployOrder(const DeployOrder& deployOrder);
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
        bool validate();
        bool execute();
    private:
        Player* second;  
};

class OrderList{
    public:
        // Empty Constructor
        OrderList();
        // Copy contructor
        OrderList(const OrderList &copyOL);
        //Assignment operator 
        OrderList &operator=(const OrderList &assignOL);
        // Inserts an order at the end (as they supposed to)
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




