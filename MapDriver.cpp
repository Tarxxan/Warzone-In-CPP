// Driver that reads many different map files, creates a Map object for valid files and rejects the
// invalid ones.
#include "Map.h"
#include <iostream>
using namespace std;

int main()
{

    // MapLoader ml("bigeurope.map");

    // cout <<*ml.map->getAllContinents().at(1)->getTerritories().at(1);
    // cout<< ml.map->oneContinent();
    // cout<< ml.map->connectedSubgraphs();
    // ml.map->connectedGraph();
    // ml.map->validate();

    //-----------------------------------added--------------------------------------------------------------
    bool playAgain = true;
    while (playAgain)
    {
        // Bigeurope.map Valid
        // sudamerica.map Valid
        // artic.map Invalid Territory are not connected last line of code
        // Bigeurope2Continents.map 1 country 2 continents line 32
        // bigeuropebadborders.map Same as artic
        // bigeuropebadcontinents.map Continents arent connected. Continent 1 is disconnected

        cout << "Type the Name of a map. We will attempt to validate it." << endl;
        string s = {};
        cin >> s;

        MapLoader ml2(s);

        // Checks whether the map is valid, throught the 3 helper functions
        ml2.map->validate();

        // Prints Territory before Change of player and army test
        cout << *ml2.map->getAllContinents().at(0)->getTerritories().at(0) << endl;
        Player *k = new Player("Kim");
        ml2.map->getAllContinents().at(0)->getTerritories().at(0)->setNumberOfArmies(345);
        ml2.map->getAllContinents().at(0)->getTerritories().at(0)->setOwnerOfTerritory(k);

        cout << "Assigning a territory a player \" Kim \" and Setting its army to 345" << endl
             << endl;
        cout << *ml2.map->getAllContinents().at(0)->getTerritories().at(0) << endl;

        //
        cout << "\nWould you like to check another Map (Y/N)" << endl;
        string retry = {};
        cin >> retry;
        if (retry.compare("N") == 0)
        {
            playAgain = false;
        }
    }

    cout << "\n\n The following operations are done on the Big Europe Map(valid)" << endl;

    MapLoader ml("bigeurope.map");
    // testing territory insertion operator.
    cout << endl

         << "\n\n[Testing Territory insertion operator]" << endl;
    vector<Territory *> myTerrs = (ml.map->getAllContinents().front())->getTerritories();

    for (Territory *t : myTerrs)
    {
        cout << *t;
    }

    // testing continent insertion operator.
    cout << endl
         << "\n\n[Testing continent insertion operator]" << endl;
    vector<Continent *> myConts = ml.map->getAllContinents();
    for (Continent *c : myConts)
    {
        cout << *c;
    }

    // testing Map insertion operator
    cout << endl
         << "\n\n[Testing Map insertion operator]" << endl;
    cout << *ml.map;
    //-------------------------------------------------------------------------------------------------

    system("pause");

    return 0;
}