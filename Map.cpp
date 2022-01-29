#include "Map.h";
using namespace std;


    Territory::Territory(int TerritoryID, string Name, int Territorysoldiers)
    {
       this-> TerritoryID=TerritoryID;
       this->Name=Name;
       this->TerritorySoldiers=Territorysoldiers;
    };



class MapLoader{
// Map loader can read any Domination map file.
// http://domination.sourceforge.net/getmaps.shtml
// Map loader creates a map object as a graph data structure.
// Map loader should be able to read any text file (even invalid ones)


//default constructor 

//Copy constructor



};