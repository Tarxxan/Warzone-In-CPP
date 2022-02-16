// The Map class is implemented as a connected graph. The graph�s nodes represents a
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

class Player
{
public:
    string name;
    Player();
    Player(string name);
    ~Player();
    void setPlayerName(string s);
};

// Territory

class Territory
{

public:
    Territory();                                                                                                                         // Default Constructor
    Territory(int territoryId, string territoryName, string continentName, int numberOfArmies, vector<Territory *> adjacentTerritories); // Param constructor
    Territory(const Territory &territory);                                                                                               // copy contstructor
    ~Territory();
    Territory &operator=(const Territory &territory);                        // Assignment operator // It can be used to create an object just like the copy constructor
    friend ostream &operator<<(ostream &output, const Territory &territory); // Stream insertion operator <<  // This is made friend to access private members of Territory

    // member functions
    int getTerritoryId();
    string getTerritoryName();
    string getContinentName();                  // get name of continent that this territory belong to
    int getNumberOfArmies();                    // total number of arimes currently on that territory
    vector<Territory *> getAdjacentTerritory(); // get adjacent territories
    void addAdjacentTerritory(Territory *t);
    Player *getOwnerOfTerritory();
    void setOwnerOfTerritory(Player *p);
    void setNumberOfArmies(int num);

private:
    int territoryId;
    string territoryName;
    string continentName;
    int numberOfArmies;
    vector<Territory *> adjacentTerritories; // Store adjacent territory pointers in vector.
    Player *ownerOfTerritory;
};

// Continent

class Continent
{
public:
    Continent();                                                                                               // default constructor
    Continent(int continentId, string continentName, int continentArmyValue, vector<Territory *> territories); // param constructor
    Continent(const Continent &continent);                                                                     // copy constructor
    ~Continent();
    Continent &operator=(const Continent &continent);                        // assignment operator
    friend ostream &operator<<(ostream &output, const Continent &continent); // stream insertion operator

    // member functions
    void addTerritory(Territory *territory); // store a pointer to territoriy that belongs to this continent
    string getContinentName();
    int getContinentId();
    vector<Territory *> getTerritories(); // get all the territories belong to this continent
    int getContinentControlValue();       // get control value

private:
    int continentId;
    string continentName;
    int continentControlValue;       // control value // Player that con
    vector<Territory *> territories; // Territories that belong to this continent
};

// Map

class Map
{
public:
    Map();                                                                                // default constructor
    Map(string mapName, vector<Continent *> continents); // param constructor
    Map(const Map &map);                                                                  // copy constructor
    ~Map();
    Map &operator=(const Map &map);                              // assignment operator
    friend ostream &operator<<(ostream &output, const Map &map); // stream insertion operator

    // member functons
    string getMapName();
    vector<Continent *> getAllContinents();
    bool validate(); // check if map is valid
    Territory *findTerritory(int id);
    void deletePointers();
    bool oneContinent();
    bool connectedSubgraphs();
    bool connectedGraph();
    bool checkBothWays(Territory *t, int tID);

private:
    string mapName;
    vector<Continent *> continents; // all continents in this map
};

// Map loader

class MapLoader
{
public:
    // Default, Param, Copy, Assignment, Stream Insertions
    MapLoader();
    MapLoader(string FileName);
    MapLoader(const MapLoader &copyML);
    MapLoader &operator=(const MapLoader &AssignML);
    friend ostream &operator<<(ostream &out, const MapLoader &);
    friend istream &operator>>(istream &in, MapLoader &ML);
    ~MapLoader();
    string FileContents;
    string FileName;
    bool isbadFile;
    Map *map;
    void SplitString(string s, vector<string> &v);
};
