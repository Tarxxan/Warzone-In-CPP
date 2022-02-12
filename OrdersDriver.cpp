// Driver that creates orders of every kind, places them in an OrdersList object, and
// demonstrates that the above features are available. 

#include <iostream>
#include "Orders.h"
#include <memory>
using namespace std;

int main() {
    // TODO: Add each of the order type and I guess some validations
    Player* p1 = new Player();
    Player* p2 = new Player();
    Territory* t1 = new Territory();
    Territory* t2 = new Territory();


    AirliftOrder* dep = new AirliftOrder(p1, 1, t1, t2);
    AirliftOrder* dep1 = new AirliftOrder(p2, 2, t2, t1);
    AirliftOrder* dep2 = new AirliftOrder(p1, 3, t1, t2);
    OrderList newList;
    cout << "initial list" << endl;
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

    system("pause");
    
}

// g++ "OrdersDriver.cpp" "Orders.cpp" -o "orders.exe"

