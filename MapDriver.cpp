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
        cout << "Type the Name of a map. We will attempt to validate it." << endl;
        string s = {};
        cin >> s;

        MapLoader ml2(s);
        ml2.map->validate();

        cout << "\nWould you like to check another Map (Y/N)" << endl;
        string retry = {};
        cin >> retry;
        if (retry.compare("N") == 0)
        {
            playAgain = false;
        }
    }

    cout << "The following operations are done on the Big Europe Map(valid)" << endl;

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