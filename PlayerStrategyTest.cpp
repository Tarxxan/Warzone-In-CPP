#include <iostream>
#include "Player.h"
#include <memory>
using namespace std;


int main() {
    Player* p1 = new Player("Tom", "cheater");
    Player* p2 = new Player("John");
    
    vector<Territory*> list1;
    vector<Territory*> list2;
    vector<Territory*> list3;
    vector<Territory*> list4;

    Territory* t1 = new Territory(1, "Australia", "Oceanie", 5, list1);
    Territory* t2 = new Territory(2, "Canada", "America", 3, list2);
    Territory* t3 = new Territory(3, "United States", "America", 6, list3);
    Territory* t4 = new Territory(4, "China", "Asia", 2, list4);
        // Link A & B
    t1->addAdjacentTerritory(t2);
    t2->addAdjacentTerritory(t1);
    // A & C
    t1->addAdjacentTerritory(t3);
    t3->addAdjacentTerritory(t1);
    // A & D belong to Tom
    p1->addTerritory(t1);
    p1->addTerritory(t4);
    // B & C belong to John
    p2->addTerritory(t2);
    p2->addTerritory(t3);
    // Add players army
    p1->computeReinforcementPool();
    p2->computeReinforcementPool();

    cout << "#############################################################" << endl;
    p2->setStrategy(new BenevolentPlayerStrategy(p2));
    vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    // players.at(0)->issueOrder();
    players.at(1)->issueOrder();
    

    // p1->issueOrder();

    system("pause");
}

// g++ "PlayerStrategyTest.cpp" "Orders.cpp" "Player.cpp" "Map.cpp" "Cards.cpp" "LoggingObserver.cpp" "PlayerStrategies.cpp" -o "strategies.exe"
