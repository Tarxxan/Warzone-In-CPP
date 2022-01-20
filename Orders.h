// The OrdersList class contains a list of Order objects (it will reside in here as well)
// The OrdersList class implements a remove() method that deletes an order from the list.
// The OrdersList class implements a move() method to move an order in the list of orders. 

// Each kind of order is implemented as a subclass of the Order class. 
// The Order class implements a stream insertion operator that outputs a string describing the
// order. If the order has been executed, it should also output the effect of the order, stored as a
// string. 
// Every order subclass must implement the validate() method that is used to validate if the
// order is valid.
// Every order subclass must implement the execute() method that first validates the order,
// and executes its action if it is valid, according to the order’s meaning and the player’s state.
