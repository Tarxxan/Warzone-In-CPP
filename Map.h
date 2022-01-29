// The Map class is implemented as a connected graph. The graph’s nodes represents a
// territory (implemented as a Territory class). Edges between nodes represent adjacency
// between territories
// Continents are connected subgraphs. Each territory belongs to one and only one continent.
// A territory is owned by a player and contain a number of armies.
// The Map class can be used to represent any map graph configuration.
// The Map class includes a validate() method that makes the following checks: 1) the map is
// a connected graph, 2) continents are connected subgraphs and 3) each country belongs to
// one and only one continent. 

// Include Guards to prevent multiple inclusion
#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Territory{

public:
//Default Constructor
    Territory();

//Param constructor
    Territory(int TerritoryID, string Name,const int TerritorySoldiers);

//copy contstructor
    Territory(const Territory &copyT);

 //Assignment operator 
    Territory &operator=(const Territory &AssignT);

// Streamline Operator

    friend ostream& operator << (ostream &out, const Territory&);
    friend istream& operator >> (istream &in, Territory &Territory);

    // int GetTerritoryID();
    // void addTerritory();// Have to have params to push to the vector just dont know which ones yet. ( Add edge)
   

private:
    int TerritoryID;
    string Name; 
    int TerritorySoldiers;
    vector <Territory>* AdjacentTerritories ;
   // Player *Player;
   // const string Continent;

 };

// method adjacency list
// add territory, set player and soldiers 
// countructor with player and number of soldiers 


class Map{
public:
//Default, Param, Copy, Assignment, Stream Insertions
    //Map();
    //Map(string FileName);
    //Map(const Map &copyMap);
   // Map &operator=(const Map &AssignMap);
  //  friend ostream& operator << (ostream &out, const Map&);
    //friend istream& operator >> (istream &in, Map &Map);
// Creates territories from the text file. Passing values line by line
  //  void createTerritory(string TextTerritory);
// Returns all continents on the map
   // void getContinents(); 
// Validate Method does 3 checks.
  //  bool validate();

    //string getTerritoryName();


private:

        //vector <Continent>* Continents ;


};

class MapLoader{
public:
// Default, Param, Copy, Assignment, Stream Insertions
    MapLoader();
    MapLoader(string FileName);
    MapLoader(const MapLoader &copyML);
    MapLoader &operator=(const MapLoader &AssignML);
    friend ostream& operator << (ostream &out, const MapLoader&);
    friend istream& operator >> (istream &in, MapLoader &ML);
    string FileContents;
        // These are suppos3ed to be used in operators but they never get displayed so i dont even know 
    string FileName;
    // Must delete reference to pointer if file is bad to avoid a mem leak
    Map* map;
 

};

class Player{
public:
    Player();
}


// class Continent{
// public:
//     vector<Territory>* Countries;

//  Continent();



// };
;
