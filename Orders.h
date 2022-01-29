// The OrdersList class contains a list of Order objects (it will reside in here as well)
// The OrdersList class implements a remove() method that deletes an order from the list.
// The OrdersList class implements a move() method to move an order in the list of orders. 

// Each kind of order is implemented as a subclass of the Order class. 
//  deploy, advance, bomb, blockade, airlift, and negotiate
// The Order class implements a stream insertion operator that outputs a string describing the
// order. If the order has been executed, it should also output the effect of the order, stored as a
// string. 
// Every order subclass must implement the validate() method that is used to validate if the
// order is valid.
// Every order subclass must implement the execute() method that first validates the order,
// and executes its action if it is valid, according to the order’s meaning and the player’s state.
#pragma once
#include <vector>
#include <iostream>
// #include "Orders.cpp"
using namespace std;

class Order{
    public:
        Order(string name);
    private:
        string name;
        friend ostream& operator << (ostream &out, const Order&);
        friend istream& operator >> (istream &in, Order &o);
};
class DeployOrder : Order{};
class AdvanceOrder : Order{};
class BombOrder : Order{};
class BlockadeOrder : Order{};
class AirliftOrder : Order{};
class NegotiateOrder : Order{};

class OrderList{
    public:
        // Empty Constructor
        OrderList();
//         // Copy contructor
//         OrderList(const OrderList &copyOL);
//         //Assignment operator 
//         OrderList &operator=(const OrderList &assignOL);
        
        
//         // comparing pointers of order
//         bool remove(Order *order);
//         // So if True it will move up if false it will move down
//         bool move(Order *order, bool moveUp);

//         // This is a more use friendly methods for move which will call move
//         bool moveUp(Order *order);
//         bool moveDown(Order *order);
//         // Inserts an order at the end (as they supposed to)
        // void push(Order *order);



    private:
        // Streamline Operator
        friend ostream& operator << (ostream &out, const OrderList&);
        friend istream& operator >> (istream &in, OrderList &ol);
        vector <Order>* orderList;
};




