// Driver that reads many different map files, creates a Map object for valid files and rejects the
// invalid ones.
#include "Map.h"
#include <iostream>
#include <ctime>
using namespace std;

// Bigeurope.map Valid
        // sudamerica.map Valid
        // artic.map Invalid Territory are not connected last line of code
        // Bigeurope2Continents.map 1 country 2 continents line 32
        // bigeuropebadborders.map Same as artic
        // bigeuropebadcontinents.map Continents arent connected. Continent 1 is disconnected

int main()
{   
    bool playAgain = true;
    while (playAgain)
    {
        

        cout << "Type the Name of a map. We will attempt to validate it." << endl;
        string s = {};
        cin >> s;

        MapLoader ml2(s);
        
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
 
        srand(time(0));
        // Testing setting army number and player 
        cout << *ml.map->getAllContinents().at(0)->getTerritories().at(0) << endl;
        // "Assigning a territory a player \" Kim \" and Setting its army to 345"
        Player *k = new Player("Kim");
        ml.map->getAllContinents().at(0)->getTerritories().at(0)->setNumberOfArmies(345);
        ml.map->getAllContinents().at(0)->getTerritories().at(0)->setOwnerOfTerritory(k);

        cout << "Assigning a territory a player \" Kim \" and Setting its army to 345" << endl
             << endl;
        cout << *ml.map->getAllContinents().at(0)->getTerritories().at(0) << endl;
        
        // testing Map insertion operator
        cout << "\n\n[Testing Map insertion operator]" << endl;
        cout << *ml.map;
    
        // testing continents insertion operator.
        cout << "\n\n[Testing continent insertion operator]" << endl;
        vector<Continent *> myConts = ml.map->getAllContinents();
        int randomContinent=rand() % (myConts.size()-1);
        cout << *myConts.at(randomContinent) << endl;
           // testing territory insertion operator.
        cout << "\n[Testing Territory insertion operator]" << endl;
        vector<Territory *> myTerrs = (myConts.at(randomContinent)->getTerritories());
     
        //randomContinent=rand() % myConts.size()-1;
        int randomTerr=rand() % (myTerrs.size()-1);
        cout << *myConts.at(randomContinent)->getTerritories().at(randomTerr) << endl;

   
    // testing continent insertion operator.
    

  

    system("pause");

    return 0;
}