#include "Map.h"
#include <iostream>
#include <vector>
#include <fstream> // file stream
#include <string> // Needed for Getline method
using namespace std;

//----------------------------------------------------------------------------------------------------
//-----------------------------Territory Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------

    Territory::Territory()
    {
        //do we need to define default constructor?
    }

    Territory::Territory(int territoryId, string territoryName, string continentName, vector<Territory*> adjacentTerritories)
    {
        this->territoryId = territoryId;
        this->territoryName = territoryName;
        this->continentName = continentName;
        this->adjacentTerritories = adjacentTerritories;
    }

    Territory::Territory(const Territory& territory)
    {
        this->territoryId = territory.territoryId;
        this->territoryName = territory.territoryName;
        this->continentName = territory.continentName;
        this->numberOfArmies = territory.numberOfArmies;
        this->adjacentTerritories = territory.adjacentTerritories;
    }

    Territory& Territory::operator=(const Territory& territory)
    {
        this->territoryId = territory.territoryId;
        this->territoryName = territory.territoryName;
        this->continentName = territory.continentName;
        this->numberOfArmies = territory.numberOfArmies;
        this->adjacentTerritories = territory.adjacentTerritories;
    }

    ostream& operator<<(ostream& output, const Territory& territory)
    {
        output << "--Territory ID: " << territory.territoryId << endl;
        output << "--Territory Name: " << territory.territoryName << endl;
        output << "--Continent Name: " << territory.continentName << endl;
        output << "--Number of armies: " << territory.numberOfArmies << endl;
        output << "--adjacent territories: " << endls;
        //I want to iterate through the vector adjacentTerritories and print out naems. //----------------------------TODO

    }


    int Territory::getTerritoryId()
    {
        return territoryId;
    }

    string Territory::getTerritoryName()
    {
        return territoryName;
    }

    string Territory::getContientName()
    {
        return continentName;
    }

    vector<Territory*> Territory::getAdjacentTerritories()
    {
        return adjacentTerritories; //this returns the vector
    }
    void Territory::setNumberOfArmies(int num)
    {
        numberOfArmies = num;
    }
    Player* Territory::getOwnerOfTerritory()
    {
        return ownerOfTerritory; // return the pointer to player object
    }




//----------------------------------------------------------------------------------------------------
//-----------------------------Continent Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------

class Continent{
public:
    Continent(); //default constructor
    Continent(int continentId, string continentName, int continentArmyValue, vector<Territory*> territories); //param constructor
    Continent(Const Continent& continent); //copy constructor
    ~Continent();
    


    //member functions
    void addTerritory(Territory* territory); //store a pointer to territoriy that belongs to this continent
    string getContientName();
    int getContinentId();
    vector<Territory*> getTerritories(); // get all the territories belong to this continent
    int getContinentControlValue(); // get control value
 

private:
    int continentId;
    string continentName; 
    int continentControlValue; // control value
    vector<Territory*> territories; // Territories that belong to this continent

};



Continent::Continent()
{
    //default constructor
}

//param constructor
Continent::Continent(int continentId, string continentName, int continentArmyValue, vector<Territory*> territories)
{
    this->continentId = continentId;
    this->continentName = continentName;
    this->continentControlValue = continentControlValue;
    this->territories = territories;
}

//copy constructor
Continent::Continent(Const Continent& continent)
{
    this->continentId = Continent.continentId;
    this->continentName = Continent.continentName;
    this->continentControlValue = continent.continentArmyValue;
    this->territories = continent.territories;
}

//destructor
Continent::~Continent()
{
    //cout<< "-Continent destructor is called" <<endl;
}


//assignment operator
Continent& Continent::operator=(const Continent& continent)
{
    this->continentId = Continent.continentId;
    this->continentName = Continent.continentName;
    this->continentControlValue = continent.continentArmyValue;
    this->territories = continent.territories;
}


 //stream insertion operator 
ostream& operator<<(ostream& output, const Continent& continent)
{
    output << "--Continet ID: " << continent.continentId << endl;
    output << "--Continent Name: " << continent.continentName << endl;
    output << "--Continent control value: " << continent.continentControlValue << endl;
    output << "--Territories: " << endl;
    // -------------------------------------------NOTE : want to print out all the territories belong to this continent
}



//----------------------------------------------------------------------------------------------------
//-----------------------------MapLoader Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------



// Map loader creates a map object as a graph data structure.
// Map loader should be able to read any text file (even invalid ones)
// Give values to an object that is uninitialized
MapLoader::MapLoader(){};

 MapLoader::MapLoader(const MapLoader &copyML){
    FileContents=copyML.FileContents;
    FileName=copyML.FileName;
    // not sure if this should be different because its a pointer but ill look into it
    map = copyML.map;
 }

//Used to change values of an already initialized object
MapLoader& MapLoader::operator=(const MapLoader &AssignML){
    FileContents=AssignML.FileContents;
    FileName=AssignML.FileName;
    map = AssignML.map;
    return *this;

    }

//  MapLoader will actually be reading the file

MapLoader::MapLoader(string FileName){

ifstream in(FileName); 
string TempText="";

if(in.fail())
{
   cout <<" An Error has occured when reading from the file. Unexpected value or file error." << endl;
   // delete pointer to map maybe inside of here 

return;
}  

while(getline(in,TempText)){

FileContents+=TempText +"\n";

}

in.close();
// Testing that we can display the file contents
this->FileContents=FileContents;
}

// IO Stream Operators for MapLoader
//Figured out what they do just unsure what we will put in them.

istream &operator >> (istream &in,  MapLoader &ML)
{
    cout << "Enter Map File";
    in >> ML.FileName;
    return in;
    }

ostream &operator << (ostream &out, const MapLoader &ML)
{
    out << ML.FileContents << endl;
    return out;
}


//----------------------------------------------------------------------------------------------------
//-----------------------------Map Class--------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

