#pragma once
using namespace std;
#include <vector>
#include "Map.h"
#include "Player.h"

class Player;
class Territory;
//////////////////////////////////////////////// PlayerStrategy //////////////////////////////////////////////
class PlayerStrategy {
public:
    PlayerStrategy(); 
    PlayerStrategy(Player* player);
    ~PlayerStrategy();
    PlayerStrategy(const PlayerStrategy& ps);
    PlayerStrategy& operator=(const PlayerStrategy& playerStrategy);
    friend ostream& operator<<(ostream& out, const PlayerStrategy& playerStrategy);

    //getters
    Player* getPlayer();

    virtual vector <Territory*> toDefend() = 0; // return an arbitrary list of territories to be defended
    virtual vector <Territory*> toAttack() = 0; // returns arbitrary list of territories that are to be attacked.
    virtual void issueOrder() = 0;  // creates an Order object and puts it in the player's list of orders.

protected:
    Player* player;
    string strategyName;
};
///////////////////////////////////////////// HumanPlayerStrategy //////////////////////////////////////////////
class HumanPlayerStrategy: public PlayerStrategy{
    // Guys I didnt put here copy/assignment/print/constructors as they are avaibale in base class
    // let me know if you think I should include it 
    HumanPlayerStrategy(Player* player);
    vector <Territory*> toDefend();
    vector <Territory*> toAttack();
    void issueOrder();
};
///////////////////////////////////////////// AgressivePlayerStrategy //////////////////////////////////////////////
class AgressivePlayerStrategy: public PlayerStrategy{
    AgressivePlayerStrategy(Player* player);
    vector <Territory*> toDefend();
    vector <Territory*> toAttack();
    void issueOrder();
};
///////////////////////////////////////////// BenevolentPlayerStrategy //////////////////////////////////////////////
class BenevolentPlayerStrategy: public PlayerStrategy{
    BenevolentPlayerStrategy(Player* player);
    vector <Territory*> toDefend();
    vector <Territory*> toAttack();
    void issueOrder();
};
///////////////////////////////////////////// NeutralPlayerStrategy //////////////////////////////////////////////
class NeutralPlayerStrategy: public PlayerStrategy{
    NeutralPlayerStrategy(Player* player);
    vector <Territory*> toDefend();
    vector <Territory*> toAttack();
    void issueOrder();
};
///////////////////////////////////////////// CheaterPlayerStrategy //////////////////////////////////////////////
class CheaterPlayerStrategy: public PlayerStrategy{
    CheaterPlayerStrategy(Player* player);
    vector <Territory*> toDefend();
    vector <Territory*> toAttack();
    void issueOrder();
};