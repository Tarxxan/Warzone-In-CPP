// Driver that creates orders of every kind, places them in an OrdersList object, and
// demonstrates that the above features are available. 

#include <iostream>
#include "Orders.h"
#include <memory>
using namespace std;

int main() {
    // TODO: Linkage to actual Player & Territory
    Player* p1 = new Player("Tom");
    Player* p2 = new Player("John");
    Territory* t1 = new Territory("Australia");
    Territory* t2 = new Territory("Canada");

    // Creating objects for each subOrder type
    DeployOrder* deploy = new DeployOrder(p1, 5, t1);
    cout << "Testing Deploy Order: \nAfter creation:\n";
    cout << *deploy << endl;
    cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    deploy->execute();
    cout << "Execute was performed, printing the order: \n";
    cout << *deploy << endl;
    cout << "Desctructing order";
    delete deploy;
    deploy = nullptr;

    AdvanceOrder* advance = new AdvanceOrder(p1, 5, t1, t2);
    cout << "\n\nTesting Advance Order: \nAfter creation:\n";
    cout << *advance << endl;
    cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    advance->execute();
    cout << "Execute was performed, printing the order: \n";
    cout << *advance << endl;
    cout << "Desctructing order\n";
    delete advance;
    advance = nullptr;

    BlockadeOrder* block = new BlockadeOrder(p1, t1);
    cout << "\n\nTesting Blockade Order: \nAfter creation:\n";
    cout << *block << endl;
    cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    block->execute();
    cout << "Execute was performed, printing the order: \n";
    cout << *block << endl;
    cout << "Desctructing order\n";
    delete block;
    block = nullptr;

    BombOrder* bomb = new BombOrder(p1, t1);
    cout << "\n\nTesting Bomb Order: \nAfter creation:\n";
    cout << *bomb << endl;
    cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    bomb->execute();
    cout << "Execute was performed, printing the order: \n";
    cout << *bomb << endl;
    cout << "Desctructing order\n";
    delete bomb;
    bomb = nullptr;


    NegotiateOrder* neg = new NegotiateOrder(p1, p2);
    cout << "\n\nTesting Negotiate Order: \nAfter creation:\n";
    cout << *neg << endl;
    cout << "Will now use execute method which should 1. trigger validate 2. set the effect\n";
    neg->execute();
    cout << "Execute was performed, printing the order: \n";
    cout << *neg << endl;
    cout << "Desctructing order\n";
    delete neg;
    neg = nullptr;


    // Tests for OrderList push , moveUp, moveDown, delete (testing for first, last and in between instances)
    AirliftOrder* dep = new AirliftOrder(p1, 1, t1, t2);
    AirliftOrder* dep1 = new AirliftOrder(p2, 2, t2, t1);
    AirliftOrder* dep2 = new AirliftOrder(p1, 3, t1, t2);
    OrderList newList;
    cout << "\n\nTesting OrderList:\nAdding 3 orders with armies (1,2,3) so it will be easier to follow movements" << endl;
    newList.push(dep);
    newList.push(dep1);
    newList.push(dep2);
    cout << newList << "\nMoving last one up\n";
    newList.moveUp(dep2);
    cout << newList << "\nMoving middle one down\n";
    newList.moveDown(dep2);
    cout << newList << "\nMoving first one down\n";
    newList.moveDown(dep);
    cout << newList << "\nMoving middle one up\n";
    newList.moveUp(dep);
    cout << newList << "\nMoving first one up\n";
    newList.moveUp(dep);
    cout << newList << "\nMoving last one down\n";
    newList.moveDown(dep2);
    cout << newList << "\nDeleting the first one\n";
    newList.remove(dep);
    cout << newList << "\nAdding another element\n";
    newList.push(dep);
    cout << newList << "\nDeleting the middle one\n";
    newList.remove(dep2);
    cout << newList << "\nAdding another element\n";
    newList.push(dep2);
    cout << newList << "\nDeleting the last one\n";
    newList.remove(dep2);
    cout << newList << endl;

    cout << "Desctructing orders\n";
    delete dep;
    dep = nullptr;
    delete dep1;
    dep1 = nullptr;
    delete dep2;
    dep2 = nullptr;

    cout << "Desctructing players and territories\n";
    delete p1;
    p1 = nullptr;
    delete p2;
    p2 = nullptr;
    delete t1;
    t1 = nullptr;
    delete t2;
    t2 = nullptr;

    system("pause");
    
}

// g++ "OrdersDriver.cpp" "Orders.cpp" -o "orders.exe"
