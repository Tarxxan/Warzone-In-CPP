// The OrdersList class contains a list of Order objects (it will reside in here as well)
// The OrdersList class implements a remove() method that deletes an order from the list.
// The OrdersList class implements a move() method to move an order in the list of orders. 

#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Order{
    public:
        Order(string name);
        Order(const Order& order); //copy contstructor
        ~Order();
        Order& operator=(const Order& order);  //Assignment operator // It can be used to create an object just like the copy constructor
        string getName();
        string getEffect();
        bool setDescription(string desc);
        bool setEffect(string effect); // once order is executed we will have to change the effect (so basically what happened)
    private:
        string name;
        string effect;
        string description;
        friend ostream& operator << (ostream &out, const Order&);
        // do we need this?
        // friend istream& operator >> (istream &in, Order &o);
};

// Every order subclass must implement the validate() method that is used to validate if the
// order is valid.
// Every order subclass must implement the execute() method that first validates the order,
// and executes its action if it is valid, according to the order’s meaning and the player’s state.

// class DeployOrder : Order{};
// class AdvanceOrder : Order{};
// class BombOrder : Order{};
// class BlockadeOrder : Order{};
// class AirliftOrder : Order{};
// class NegotiateOrder : Order{};

// class OrderList{
//     public:
//         // Empty Constructor
//         OrderList();
// //         // Copy contructor
// //         OrderList(const OrderList &copyOL);
// //         //Assignment operator 
// //         OrderList &operator=(const OrderList &assignOL);
        
        
// //         // comparing pointers of order
// //         bool remove(Order *order);
// //         // So if True it will move up if false it will move down
// //         bool move(Order *order, bool moveUp);

// //         // This is a more use friendly methods for move which will call move
// //         bool moveUp(Order *order);
// //         bool moveDown(Order *order);
// //         // Inserts an order at the end (as they supposed to)
//         // void push(Order *order);



//     private:
//         // Streamline Operator
//         friend ostream& operator << (ostream &out, const OrderList&);
//         friend istream& operator >> (istream &in, OrderList &ol);
//         vector <Order>* orderList;
// };




