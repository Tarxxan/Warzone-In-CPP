#include "Map.h"
#include <iostream>
#include <vector>
#include <fstream> // file stream
#include <string>  // Needed for Getline method
#include <map>

using namespace std;
//class Player;

// Dummy Player class
Player::Player()
{
    name = "";
}

Player::Player(string name)
{
    this->name = name;
}

void Player::setPlayerName(string s)
{
    this->name = s;
}

Player::~Player()
{

    cout << "Player was destroyed" << endl;
}

ostream& operator<<(ostream& output, const Player& p)
{
    output << "--Player Name: " << p.name << endl;
    return output;
}
//----------------------------------------------------------------------------------------------------
//-----------------------------Territory Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//Default constructor
Territory::Territory()
{
}

// param constructor
Territory::Territory(int territoryId, string territoryName, string continentName, int numberOfArmies, vector<Territory*> adjacentTerritories)
{
    this->territoryId = territoryId;
    this->territoryName = territoryName;
    this->continentName = continentName;
    this->numberOfArmies = numberOfArmies;
    this->adjacentTerritories = adjacentTerritories;
    Player* p = new Player("John");
    this->ownerOfTerritory = p;
}

// Copy Construct
Territory::Territory(const Territory& t)
{
    this->territoryId = t.territoryId;
    this->territoryName = t.territoryName;
    this->continentName = t.continentName;
    this->numberOfArmies = t.numberOfArmies;
    this->adjacentTerritories = t.adjacentTerritories;
    this->ownerOfTerritory = t.ownerOfTerritory;
}

// destructor
Territory::~Territory()
{
    delete ownerOfTerritory;
    ownerOfTerritory = nullptr;
    cout << "~Territory destructor is called" << endl;
}

//Assignment Operator
Territory& Territory::operator=(const Territory& t)
{
    this->territoryId = t.territoryId;
    this->territoryName = t.territoryName;
    this->continentName = t.continentName;
    this->numberOfArmies = t.numberOfArmies;
    this->adjacentTerritories = t.adjacentTerritories;
    this->ownerOfTerritory = t.ownerOfTerritory;
    return *this;
}

ostream& operator<<(ostream& output, const Territory& t)
{
    output << "--Territory ID: " << t.territoryId << endl;
    output << "--Territory Name: " << t.territoryName << endl;
    output << "--Continent Name: " << t.continentName << endl;
    output << "--Player Name: " << t.ownerOfTerritory->name << endl;
    output << "--Number of armies: " << t.numberOfArmies << endl;
    output << "--Adjacent territories: ";

    for (Territory* t : t.adjacentTerritories)
    {
        output << t->territoryName << " | ";
    }
    output << endl
        << "------------------------------------------------------" << endl;
    return output;
}

// Getter and setters for our ddata members 
int Territory::getTerritoryId()
{
    return territoryId;
}

string Territory::getTerritoryName()
{
    return territoryName;
}

string Territory::getContinentName()
{
    return continentName;
}

int Territory::getNumberOfArmies()
{
    return numberOfArmies;
}

vector<Territory*> Territory::getAdjacentTerritory()
{
    return adjacentTerritories; // this returns the vector
}

void Territory::addAdjacentTerritory(Territory* t)

{
    this->adjacentTerritories.push_back(t);
}

void Territory::setNumberOfArmies(int num)
{
    numberOfArmies = num;
}

Player* Territory::getOwnerOfTerritory()
{
    return ownerOfTerritory;
}

void Territory::setOwnerOfTerritory(Player* p)
{
    this->ownerOfTerritory = p;
}

//----------------------------------------------------------------------------------------------------
//-----------------------------Continent Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------


//default constructor
Continent::Continent()
{
}


//parameterized constructor
Continent::Continent(int continentId, string continentName, int continentControlValue, vector<Territory*> territories)
{
    this->continentId = continentId;
    this->continentName = continentName;
    this->continentControlValue = continentControlValue;
    this->territories = territories;
}

//copy constructor
Continent::Continent(const Continent& c)
{
    this->continentId = c.continentId;
    this->continentName = c.continentName;
    this->continentControlValue = c.continentControlValue;
    this->territories = c.territories;
}


//destructor
Continent::~Continent()
{
    cout << "~Continent destructor is called" << endl;
}


//assignment operator
Continent& Continent::operator=(const Continent& c)
{
    this->continentId = c.continentId;
    this->continentName = c.continentName;
    this->continentControlValue = c.continentControlValue;
    this->territories = c.territories;

    return *this;
}


//add territory to vector
void Continent::addTerritory(Territory* t)
{
    this->territories.push_back(t);
}

//getters
string Continent::getContinentName()
{
    return continentName;
}

int Continent::getContinentId()
{
    return continentId;
}

vector<Territory*> Continent::getTerritories()
{
    return territories;
}

int Continent::getContinentControlValue()
{
    return continentControlValue;
}

// insertion operator
ostream& operator<<(ostream& output, const Continent& c)
{
    output << "--Continent ID: " << c.continentId << endl;
    output << "--Continent Name: " << c.continentName << endl;
    output << "--Continent control value: " << c.continentControlValue << endl;
    output << "--Territories: ";
    for (Territory* t : c.territories)
    {
        output << t->getTerritoryName() << " | ";
    }
    output << endl
        << "------------------------------------------------------" << endl;

    return output;
}

//----------------------------------------------------------------------------------------------------
//-----------------------------Map Class--------------------------------------------------------------
//----------------------------------------------------------------------------------------------------


//default constructor
Map::Map()
{
}


// parameterized constructor
Map::Map(string mapName, vector<Continent*> continents)
{
    this->mapName = mapName;
    this->continents = continents;
}

//copy constructor
Map::Map(const Map& map)
{
    this->mapName = mapName;
    this->continents = continents;
}

//destructor
Map::~Map()
{
    deletePointers();
    cout << "Map destructor called" << endl;
}

//assignment operator
Map& Map::operator=(const Map& m)
{

    this->mapName = m.mapName;
    this->continents = m.continents;

    return *this;
}


// insertion operator
ostream& operator<<(ostream& output, const Map& m)
{
    int numTerr = 0;
    output << "--Map Name: " << m.mapName << endl;

    output << "--Continents: ";
    for (Continent* c : m.continents)
    {
        numTerr += c->getTerritories().size();
        output << c->getContinentName() << " | ";
    }
    output << endl
        << "--Number of Continents: " << m.continents.size() << endl;
    output << "--Number of Territories: " << numTerr;
    output << endl
        << "------------------------------------------------------" << endl;

    return output;
}


//getters
string Map::getMapName()
{
    return mapName;
}

vector<Continent*> Map::getAllContinents()
{
    return continents;
}

// Helper function to find territory to push pointer into adjacent territory vector
Territory* Map::findTerritory(int id)
{
    for (Continent* c : this->continents)
    {

        for (Territory* t : c->getTerritories())
        {

            if (t->getTerritoryId() == id)
            {
                return t;
            }
        }
    }
    Territory* t = new Territory();
    return t;
}

//Validate method with 3 helper methods checking each of the conditions for a map to be valid 
bool Map::validate()
{
    int value = oneContinent();
    if (value != 1)
    {
        cerr << " This map has a Territory belonging to more than one continent.\n"
            << endl;
        return false;
    }
    value = connectedSubgraphs();
    if (value != 1)
    {
        cerr << " This map has unconnected territories within the continent\n"
            << endl;
        return false;
    }

    value = connectedGraph();
    if (value != 1)
    {
        cerr << " This maps Continents aren't connected\n"
            << endl;
        return false;
    }

    cout << "\nThis is a valid map! Let's get to the game!\n" << endl;
    return true;
}

// According to Warozne game maps should be undirected so this checks reflexivity
bool Map::checkBothWays(Territory* t, int tID)
{
    for (Territory* adj : t->getAdjacentTerritory())
    {
        if (adj->getTerritoryId() == tID)
        {
            return true;
        }
    }
    return false;
}

bool Map::connectedSubgraphs()
{
    //uses map DS to avoid duplicate keys. Will tell us if any territory is disconnected by checking adjacent 
    //and pushes it into map follows for all territory of continent and then comapares sizes of map and vector
    std::map<int, int> continentTerritories;

    for (Continent* c : this->continents)
    {
        int mapsize = c->getTerritories().size();
        for (Territory* t : c->getTerritories())
        {
            for (Territory* adj : t->getAdjacentTerritory())
            {
                if (adj->getContinentName().compare(c->getContinentName()) == 0)
                {
                    if (checkBothWays(adj, t->getTerritoryId()))
                    {
                        continentTerritories.insert({ adj->getTerritoryId(), 1 });
                    }
                    else
                    {
                        cout << "Territory " << t->getTerritoryId() << " is problematic" << endl;
                        return false;
                    }
                }
            }
        }

        if (continentTerritories.size() != mapsize)
        {
            return false;
        }
        continentTerritories.clear();
    }

    return true;
}


//check if it is connected graph 
bool Map::connectedGraph()
{

    std::map<string, int> mapContinents;
    int mapsize = this->continents.size();
    for (Continent* c : this->continents)
    {
        for (Territory* t : c->getTerritories())
        {
            for (Territory* adj : t->getAdjacentTerritory())
            {
                if (adj->getContinentName().compare(c->getContinentName()) != 0)
                {
                    mapContinents.insert({ adj->getContinentName(), 1 });
                }
            }
        }
    }
    if (mapContinents.size() != mapsize)
    {
        return false;
    }
    mapContinents.clear();

    return true;
}


//check if a territory is belong to one and only one continent
bool Map::oneContinent()
{

    std::map<int, vector<int>> oneContinent;
    for (Continent* c : this->continents)
    {
        for (Territory* t : c->getTerritories())
        {
            oneContinent[t->getTerritoryId()].push_back(c->getContinentId());
        }
    }

    for (int i = 0; i < oneContinent.size(); i++)
    {
        for (int j = 0; j < oneContinent[i].size(); j++)
        {
            if (oneContinent[i].size() > 1)
            {

                return false;
            }
        }
    }

    return true;
}


// function to deal with memory leak. called to avoid dangling pointers
void Map::deletePointers()
{
    for (Continent* c : continents)
    {
        for (Territory* t : c->getTerritories())
        {
            for (Territory* adj : t->getAdjacentTerritory())
            {
                adj = nullptr;
            }
            delete t;

            t = nullptr;
        }
        delete c;
        c = nullptr;
    }
    cout << "All pointers of the map are deleted" << endl;
}

//----------------------------------------------------------------------------------------------------
//-----------------------------MapLoader Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------

// Map loader creates a map object as a graph data structure.
// Map loader should be able to read any text file (even invalid ones)
// Give values to an object that is uninitialized
MapLoader::MapLoader() {};

MapLoader::MapLoader(const MapLoader& copyML)
{
    isbadFile = { false };
    FileContents = copyML.FileContents;
    FileName = copyML.FileName;
    map = copyML.map;
}

// Used to change values of an already initialized object
MapLoader& MapLoader::operator=(const MapLoader& AssignML)
{
    FileContents = AssignML.FileContents;
    FileName = AssignML.FileName;
    map = AssignML.map;
    return *this;
}

//Splits strings into tokens to parse map data
void MapLoader::SplitString(string s, vector<string>& v)
{

    string temp = "";
    for (int i = 0; i < s.length(); ++i)
    {

        if (s[i] == ' ')
        {
            v.push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(s[i]);
        }
    }
    v.push_back(temp);
}

//destructor
MapLoader::~MapLoader()
{
    if (!isbadFile) {
        delete map;
        map = nullptr;
    }
    cout << "~MapLoader destructor is called" << endl;
}

//  MapLoader will actually be reading the file
MapLoader::MapLoader(string FileName)
{
    isbadFile = { false };
    ifstream in(FileName);
    string TempText = "";
    vector<string> continentTokens;
    vector<string> territoryTokens;
    vector<string> adjacentTokens;

    int continentCount{ 0 };

    if (in.fail())
    {
        cerr << " An Error has occured when reading from the file. Unexpected file error." << endl;
        isbadFile = true;
        return;
    }

    int i{ 0 };
    while (getline(in, TempText))
    {

        if (TempText.compare("[continents]") == 0)
        {
            while (getline(in, TempText) && TempText.compare("") != 0)
            {
                continentTokens.push_back(TempText);
            }
        }
        if (TempText.compare("[countries]") == 0)
        {
            while (getline(in, TempText) && TempText.compare("") != 0)
            {
                territoryTokens.push_back(TempText);
            }
        }
        if (TempText.compare("[borders]") == 0)
        {
            while (getline(in, TempText) && TempText.compare("") != 0)
            {
                adjacentTokens.push_back(TempText);
            }
        }
    }

    vector<Territory*> Territories;
    vector<Continent*> continents;
    vector<string> results;

    if (continentTokens.size() == 0 || territoryTokens.size() == 0 || adjacentTokens.size() == 0)
    {
        cerr << " An Error has occured when reading from the file. Unexpected value." << endl;
        in.close();
        return;
    }

    try
    {
        for (int i = 0; i < continentTokens.size(); i++)
        {

            SplitString(continentTokens[i], results);
            vector<Territory*> territories;
            Continent* c = new Continent(++continentCount, results[0], stoi(results[1]), territories);
            continents.push_back(c);
            results.clear();
        }

        for (int i = 0; i < territoryTokens.size(); i++)
        {
            SplitString(territoryTokens[i], results);
            vector<Territory*> adjacentTerritories;
            Territory* t = new Territory(stoi(results[0]), results[1], continents.at(stoi(results[2]) - 1)->getContinentName(), 0, adjacentTerritories);
            continents.at(stoi(results[2]) - 1)->addTerritory(t);
            results.clear();
        }

        this->map = new Map(FileName, continents);

        for (int i = 0; i < adjacentTokens.size(); i++)
        {
            SplitString(adjacentTokens[i], results);
            Territory* t = this->map->findTerritory(stoi(results[0]));
            for (int i = 1; i < results.size(); i++)
            {
                t->addAdjacentTerritory(this->map->findTerritory(stoi(results[i])));
            }
            results.clear();
        }
    }
    catch (const exception& e)
    {
        cerr << "The Map file is invalid according to game specificiations" << '\n';
        map->deletePointers();
        delete map;
        map = nullptr;
        return;
    }

    this->map->validate();
    in.close();
}
// IO Stream Operators for MapLoader
// Figured out what they do just unsure what we will put in them.

ostream& operator>>(ostream& output, MapLoader& ML)
{
    output << ML.FileName << endl;
    return output;
}

