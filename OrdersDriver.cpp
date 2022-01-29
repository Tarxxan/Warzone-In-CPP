// Driver that creates orders of every kind, places them in an OrdersList object, and
// demonstrates that the above features are available. 

#include <iostream>
#include "Orders.h"
using namespace std;

int main() {
    std::cout << "Hello World!";
    Order newOrder = Order("Bomb");
    Order* ptOrder = &newOrder;

    OrderList newList;
    cout << newList;
    system("pause");
}

// g++ "OrdersDriver.cpp" "Orders.cpp" -o "orders.exe"

