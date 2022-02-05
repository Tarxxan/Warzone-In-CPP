// Driver that creates orders of every kind, places them in an OrdersList object, and
// demonstrates that the above features are available. 

#include <iostream>
#include "Orders.h"
#include <memory>
using namespace std;

int main() {
    
    AdvanceOrder* temp = new AdvanceOrder();
    DeployOrder* dep = new DeployOrder(50);
    // cout << newOrder << endl;
    // newOrder.validate();
    // newOrder.setDescription("Armies were deployed");
    // cout << newOrder << endl;
    // advance.validate();
    OrderList newList;
    newList.push(temp);
    newList.push(dep);
    newList.getHead();
    delete temp,dep,newList;
    system("pause");
    
}

// g++ "OrdersDriver.cpp" "Orders.cpp" -o "orders.exe"

