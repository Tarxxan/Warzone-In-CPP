#include "Orders.h"
using namespace std;

// OrderList::OrderList(){
//     cout << "In the empty constructor";
// };
Order::Order(string name){
    this->name = name;
};

OrderList::OrderList(){};
std::ostream& operator<<(std::ostream &strm, const OrderList &ol) {
    // for (int i = 0; i < ol.orderList->size(); i++){
	//        cout << "The values of the vector are: " << ol.orderList[i] << endl;
	// }
    return strm << "A(";
};
std::ostream& operator<<(std::ostream &strm, const Order &o) {
    return strm << "Order: " << o.name;
};

// class OrderList{
//     OrderList(){
//         cout << "empty constructor";
//     }
//     void push(Order* order){
//         cout << "push";
//     }
// };
