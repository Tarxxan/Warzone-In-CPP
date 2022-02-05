// The OrdersList class contains a list of Order objects (it will reside in here as well)
// The OrdersList class implements a remove() method that deletes an order from the list.
// The OrdersList class implements a move() method to move an order in the list of orders. 

#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Order{
    public:
        Order();
        Order(string name);
        Order(const Order& order); //copy contstructor
        ~Order();
        Order& operator=(const Order& order);  //Assignment operator // It can be used to create an object just like the copy constructor
        string getName();
        string getEffect();
        bool setDescription(string desc);
        bool setEffect(string effect); // once order is executed we will have to change the effect (so basically what happened)
        virtual bool validate();
        virtual bool execute();
    protected:
        string name;
        string effect;
        string description;
        friend ostream& operator << (ostream &out, const Order& );
        // do we need this?
        // friend istream& operator >> (istream &in, Order &o);
};

// Every order subclass must implement the validate() method that is used to validate if the
// order is valid.
// Every order subclass must implement the execute() method that first validates the order,
// and executes its action if it is valid, according to the order’s meaning and the player’s state.

class DeployOrder : public Order{

    public:
        DeployOrder(int numOfArmies); // also take in territory/player info??
        DeployOrder(const DeployOrder& deployOrder);
        ~DeployOrder();
        int armies;
        bool validate();
        bool execute();

};
class AdvanceOrder : public Order{

    public:
        AdvanceOrder();
        ~AdvanceOrder();
        bool validate();
        bool execute();


};
class BombOrder : public Order{
    public:
        BombOrder();
        ~BombOrder();
        bool validate();
        bool execute();
       

};
class BlockadeOrder : public Order{

    public:
        BlockadeOrder();
        ~BlockadeOrder();
        bool validate();
        bool execute();
        

};
class AirliftOrder : public Order{
    
    public:
        AirliftOrder();
        ~AirliftOrder();
        bool validate();
        bool execute();
      
};
class NegotiateOrder : public Order{

    public:
        NegotiateOrder();
        ~NegotiateOrder();
        bool validate();
        bool execute();
       
};

class OrderList{
    public:
        // Empty Constructor
        OrderList();
        // Copy contructor
        OrderList(const OrderList &copyOL);
        //Assignment operator 
        OrderList &operator=(const OrderList &assignOL);
        
        
        // comparing pointers of order
        bool remove(Order *order);
        // So if True it will move up if false it will move down
        bool move(Order *order, bool moveUp);
        void getHead();
        // This is a more use friendly methods for move which will call move
        bool moveUp(Order *order);
        bool moveDown(Order *order);
        // Inserts an order at the end (as they supposed to)
        void push(Order *order);
        // Streamline Operator
        friend std::ostream& operator << (ostream& out,const OrderList& ol);
        friend std::istream& operator >> (istream& in, OrderList& ol);
        vector <Order*> orderList;
};




