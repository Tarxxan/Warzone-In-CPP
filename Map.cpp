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

Territory::Territory(const Territory& t)
{
    this->territoryId = t.territoryId;
    this->territoryName = t.territoryName;
    this->continentName = t.continentName;
    this->numberOfArmies = t.numberOfArmies;
    this->adjacentTerritories = t.adjacentTerritories;
}

Territory::~Territory()
{
    cout<< "~Territory destructor is called" <<endl;

}

Territory& Territory::operator=(const Territory& t)
{
    this->territoryId = t.territoryId;
    this->territoryName = t.territoryName;
    this->continentName = t.continentName;
    this->numberOfArmies = t.numberOfArmies;
    this->adjacentTerritories = t.adjacentTerritories;

    return *this;
}

ostream& operator<<(ostream& output, const Territory& t)
{
    output << "--Territory ID: " << t.territoryId << endl;
    output << "--Territory Name: " << t.territoryName << endl;
    output << "--Continent Name: " << t.continentName << endl;
    output << "--Number of armies: " << t.numberOfArmies << endl;
    output << "--adjacent territories: " << endl;
    //I want to iterate through the vector adjacentTerritories and print out naems. //----------------------------TODO

    return output;

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

int Territory::getNumberOfArmies()
{
    return numberOfArmies;
}

vector<Territory*> Territory::getAdjacentTerritories()
{
    return adjacentTerritories; //this returns the vector
}

void Territory::addAdjacentTerritories(Territory* t)

{
     this->adjacentTerritories.push_back(t);
}

void Territory::setNumberOfArmies(int num)
{
    numberOfArmies = num;
}


//-------------------------------------------------------------------NOTE: no idea why this doesnt work?
//Player* Territory::getOwnerOfTerritory()
//{
//    return ownerOfTerritory; // return the pointer to player object
//}




//----------------------------------------------------------------------------------------------------
//-----------------------------Continent Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------

Continent::Continent()
{
    //default constructor
}

//param constructor
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
    cout<< "~Continent destructor is called" <<endl;
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

void Continent::addTerritory(Territory* t)
{
    this->territories.push_back(t);
}

string Continent::getContientName()
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


//stream insertion operator 
ostream& operator<<(ostream& output, const Continent& c)
{
    output << "--Continet ID: " << c.continentId << endl;
    output << "--Continent Name: " << c.continentName << endl;
    output << "--Continent control value: " << c.continentControlValue << endl;
    output << "--Territories: " << endl;
    // -------------------------------------------NOTE : want to print out all the territories belong to this continent

    return output;
}






//----------------------------------------------------------------------------------------------------
//-----------------------------Map Class--------------------------------------------------------------
//----------------------------------------------------------------------------------------------------


//default constructor
Map::Map()
{}

Map::Map(string mapName, vector<Territory*> territories, vector<Continent*> continents)
{
    this->mapName = mapName;
  //  this->territories = territories;
    this->continents = continents;
}

//copy constructor
Map::Map(const Map& map)
{
    this->mapName = mapName;
    //this->territories = territories;
    this->continents = continents;
}

//destructor
Map::~Map()
{
    cout<< "~Map destructor is called" <<endl;

}

Map& Map::operator=(const Map& m)
{
    // TODO: insert return statement here
    this->mapName = m.mapName;
    this->continents = m.continents;
   // this->territories = m.territories;

    return *this;
}

ostream& operator<<(ostream& output, const Map& m)
{
    output << "--Map Name: " << m.mapName << endl;
    output << "--Territories: " << endl;
    //TODO 
    return output;
}

string Map::getMapName()
{
    return mapName;
}


vector<Continent*> Map::getAllContinents(){
       return continents;
    }




//----------------------------------------------------------------------------------------------------
//-----------------------------MapLoader Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------



// Map loader creates a map object as a graph data structure.
// Map loader should be able to read any text file (even invalid ones)
// Give values to an object that is uninitialized
MapLoader::MapLoader() {};

MapLoader::MapLoader(const MapLoader& copyML) {
    FileContents = copyML.FileContents;
    FileName = copyML.FileName;
    // not sure if this should be different because its a pointer but ill look into it
    map = copyML.map;
}

//Used to change values of an already initialized object
MapLoader& MapLoader::operator=(const MapLoader& AssignML) {
    FileContents = AssignML.FileContents;
    FileName = AssignML.FileName;
    map = AssignML.map;
    return *this;

}
void MapLoader::SplitString(string s, vector<string> &v){
	
	string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==' '){
			v.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
		
	}
	v.push_back(temp);
	
}
	

//  MapLoader will actually be reading the file
MapLoader::MapLoader(string FileName) {

    ifstream in(FileName);
    string TempText = "";
    vector <string> continentTokens;
    vector <string> territoryTokens;
    vector <string> adjacentTokens;

    int tokenLimiter{0};
    int continentCount{ 0 };
    if (in.fail())
    {
        cerr << " An Error has occured when reading from the file. Unexpected value or file error." << endl;
        delete map;
        return;
    }

    int i{0};
    while (getline(in, TempText)) {
    
        if(TempText.compare("[continents]")==0){
            while (getline(in, TempText) && TempText.compare("")!=0){
                continentTokens.push_back(TempText);
            }
       }
        if(TempText.compare("[countries]")==0){
            while (getline(in, TempText) && TempText.compare("")!=0){
                territoryTokens.push_back(TempText);
            } 
        }
        if(TempText.compare("[borders]")==0){
            while (getline(in, TempText) && TempText.compare("")!=0){
                adjacentTokens.push_back(TempText);
            }
       }
    }

    vector<Territory*> Territories;
    vector<Continent*> continents;
    vector<string> results;
    for( int i=0;i<continentTokens.size();i++){
            SplitString(continentTokens[i],results);
            vector<Territory*> territories;
            // vector<Territory*> adjacentTerritories;
            // Territory* t= new Territory(0,"TEST","TEST", adjacentTerritories);
            // territories.push_back(t);
            Continent* c = new Continent(++continentCount,results[0],stoi(results[1]),territories);
            continents.push_back(c);
            // Test print of Continents
            // cout << *c <<endl;
            results.clear();
        }

    for( int i=0;i<territoryTokens.size();i++){
            SplitString(territoryTokens[i],results);
            vector<Territory*> adjacentTerritories;
            Territory* t= new Territory(stoi(results[0]),results[1],continents.at(stoi(results[2])-1)->getContientName(), adjacentTerritories);
            continents.at(stoi(results[2])-1)->addTerritory(t);
            // Test Print that we can access territories within continents
            // cout << *continents.at(stoi(results[2])-1)->getTerritories().at(0);
            results.clear();
        }

        for(int i=0;i<adjacentTokens.size();i++){
            SplitString(adjacentTokens[i],results);
                for( int j=0;j<continents.size();j++){
                    cout << "in continent" <<endl;
                    for( int k=0; k< continents.at(j)->getTerritories().size(); k++)
                        cout << "in countries" <<endl;
                            if(continents.at(j)->getTerritories().at(k)->getTerritoryId()==results[1]){
                                cout << "in Adjacent" <<endl;
                                for(l=1;l<results.size();l++){
                                    continents.at(j)->getTerritories().at(k)->addAdjacentTerritories()
                                }
                            }

                   
        }
    in.close();  

}
   this->map= new Map(FileName,Territories,continents);}
// IO Stream Operators for MapLoader
//Figured out what they do just unsure what we will put in them.

istream& operator >> (istream& in, MapLoader& ML)
{
    cout << "Enter Map File";
    in >> ML.FileName;
    return in;
}

//temporary
int main()
{
    MapLoader ml("bigeurope.map");
    //cout <<ml.map->getAllContinents.at(stoi(results[2]))->getTerritories().at(0);
   // cout <<ml.map->getAllContinents().at(0);
    // cout << ml.map->getAllContinents().at(1);
    return 0;
}





