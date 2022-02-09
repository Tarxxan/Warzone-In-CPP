// Driver that reads many different map files, creates a Map object for valid files and rejects the
// invalid ones.
#include "Map.h"
#include <iostream>
using namespace std;

int main() {


    
    //MapLoader ml("bigeurope.map");

    // cout <<*ml.map->getAllContinents().at(1)->getTerritories().at(1);
    //cout<< ml.map->oneContinent();
    //cout<< ml.map->connectedSubgraphs();
    // ml.map->connectedGraph();
    //ml.map->validate();




    //-----------------------------------added--------------------------------------------------------------
    MapLoader ml("bigeurope.map");

    //testing territory insertion operator. 
    cout << endl<< "[Testing Territory insertion operator]" << endl;
    vector<Territory*> myTerrs = (ml.map->getAllContinents().front())->getTerritories();

    for (Territory* t : myTerrs) 
    { cout << *t; }


    //testing continent insertion operator.
    cout <<endl<< "[Testing continent insertion operator]" << endl;
    vector<Continent*> myConts = ml.map->getAllContinents();
    for (Continent* c : myConts)
    { cout << *c; }
     

    //testing Map insertion operator
    cout << endl << "[Testing Map insertion operator]" << endl;
    cout << *ml.map;    
    //-------------------------------------------------------------------------------------------------


    //string CurrentMap="";
    //cout << "Which Map would you like to play"<<endl;
    //cin >> CurrentMap;

    //MapLoader ML(CurrentMap);
    //cout << ML;
    //system("pause");
    
    return 0;
}