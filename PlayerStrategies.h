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
    string getName();

    virtual vector <Territory*> toDefend() = 0; // return an arbitrary list of territories to be defended
    virtual vector <Territory*> toAttack() = 0; // returns arbitrary list of territories that are to be attacked.
    virtual void issueOrder() = 0;  // creates an Order object and puts it in the player's list of orders.

protected:
    Player* player;
    string strategyName;
};
///////////////////////////////////////////// HumanPlayerStrategy //////////////////////////////////////////////

//Human strategy that extends PlayerStrategy but implements its own toDefend,toAttack and issueOrder methods
class HumanPlayerStrategy: public PlayerStrategy{
    public:
        HumanPlayerStrategy(Player* player);
        vector <Territory*> toDefend();
        vector <Territory*> toAttack();
        void issueOrder();
};
///////////////////////////////////////////// AggressivePlayerStrategy //////////////////////////////////////////////

//Aggressive strategy that extends PlayerStrategy but implements its own toDefend,toAttack and issueOrder methods
class AggressivePlayerStrategy: public PlayerStrategy{
    public:
        AggressivePlayerStrategy(Player* player);
        vector <Territory*> toDefend();
        vector <Territory*> toAttack();
        void issueOrder();
};
///////////////////////////////////////////// BenevolentPlayerStrategy //////////////////////////////////////////////

//Benevolent Strategy that extends PlayerStrategy but implements its own toDefend,toAttack and issueOrder methods
class BenevolentPlayerStrategy: public PlayerStrategy{
    public:
        BenevolentPlayerStrategy(Player* player);
        vector <Territory*> toDefend();
        vector <Territory*> toAttack();
        void issueOrder();
};
///////////////////////////////////////////// NeutralPlayerStrategy //////////////////////////////////////////////

//Neutral Strategy that extends PlayerStrategy but implements its own toDefend,toAttack and issueOrder methods
class NeutralPlayerStrategy: public PlayerStrategy{
    public:
        NeutralPlayerStrategy(Player* player);
        vector <Territory*> toDefend();
        vector <Territory*> toAttack();
        void issueOrder();
};
///////////////////////////////////////////// CheaterPlayerStrategy //////////////////////////////////////////////

//Cheater Strategy that extends PlayerStrategy but implements its own toDefend,toAttack and issueOrder methods
class CheaterPlayerStrategy: public PlayerStrategy{
    public:
        CheaterPlayerStrategy(Player* player);
        vector <Territory*> toDefend();
        vector <Territory*> toAttack();
        void issueOrder();
};