// Driver that creates orders of every kind, places them in an OrdersList object, and
// demonstrates that the above features are available. 

#include <iostream>
#include "Orders.h"
using namespace std;

int main() {
    std::cout << "Hello World! \n" ;
    DeployOrder newOrder = DeployOrder(5);
    AdvanceOrder advance = AdvanceOrder();
    cout << newOrder << endl;
    newOrder.validate();
    newOrder.setDescription("Armies were deployed");
    cout << newOrder << endl;
    advance.validate();
    // OrderList newList;
    // cout << newList;
    system("pause");
}

// g++ "OrdersDriver.cpp" "Orders.cpp" -o "orders.exe"

