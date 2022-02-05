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

vector<Territory*> Territory::addAdjacentTerritories(Territory* t)

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

//  MapLoader will actually be reading the file

MapLoader::MapLoader(string FileName) {
   
    vector<Continent*> Continents;
    ifstream in(FileName);
    string TempText = "";
  

    int continentCount{ 0 };
    if (in.fail())
    {
        cout << " An Error has occured when reading from the file. Unexpected value or file error." << endl;
        // delete pointer to map maybe inside of here 

        return;
    }

    while (getline(in, TempText)) {
        cout << TempText <<endl;
        FileContents += TempText+"\n";}
        cout << FileContents << endl;
        //General idea i dont think this exact thing works because once it finds the line with contients im not 
        //sure if the file can continue getline inside.
        if (FileContents.find("[continents]"))
        {
cout<< "IN conttt" << endl;
            string TempContinents = "";
            // while (getline(, TempContinents, ' ')) {
                vector<Territory*> territories;
                vector <string> tokens;
                tokens.push_back(TempContinents);
                Continent* c2 = new Continent(continentCount += 1, "work", 1, territories);
                Continent* c = new Continent(continentCount += 1, tokens[0], stoi(tokens[1]), territories);
                // Push into continent vector from Map class or MapLoader class
                //Continents.push_back(c);
                cout <<"print c"<< endl;
          //  }
        }

        if (TempText.find("[countries]"))
        {
            cout<< "IN Countries" << endl;
            string tempTerritory = "";
            while (getline(in, tempTerritory, ' ') && tempTerritory.compare("\n") != 0) {
                vector<Territory*> borders;
                vector <string> tokens;
                tokens.push_back(tempTerritory);

                Territory* t = new Territory(stoi(tokens[0]), tokens[1], Continents.at(stoi(tokens.at(2)))->getContientName(), borders);
                // Push into continent vector from Map class or MapLoader class
                // access token[2]-1 vector of the continent class and then push into there  
                //*Continents.at(stoi(tokens.at(2))-1).territories.push_back(t);
               Continents.at(stoi(tokens.at(2))-1)->addTerritory(t);

            }
        }

        if (TempText.find("[borders]"))
        {
            string tempBorders = "";
            while (getline(in, tempBorders, ' ') && tempBorders.compare("\n") == 0) {
                vector <string> tokens;
                tokens.push_back(tempBorders);

      
                for (int i = 0; i < Continents.size(); i++) {
                            cout<< *Continents.at(i) << endl;
                // for (int j=0; j< Continents.at(i).getTerritories().size(); j++){
                //     if(temp.getTerritories().at(j)->getTerritoryId()==tempBorders[0]){
                //         temp.getTerritories().at(j)->getAdjacentTerritories()push_back()
                //     }
                    
                //     }
                    // i dont think its possible to find the correct territory from here we would need multiple loops to iterate over it until we found the proper territory id
                    //we might need to assign these borders into a temp vector and then assign them afterwards when iterating over the territories or something
                    // Continents.at(Territory.at(tokens.at(0)))                     )

                    // }


                }
            }

        }

        in.close();
        // Testing that we can display the file contents
        this->FileContents = FileContents;
    }


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
    vector<Continent*> Continents;
    vector<Territory*> territories;
    vector<Territory*> borders;
    Continent* c2 = new Continent(1, "work", 1, territories);
    Continents.push_back(c2);
    Territory* t2= new Territory(1,"canada", c2->getContientName(), borders);
    Territory* t3= new Territory(2,"USA", c2->getContientName(), borders);
    Continents.at(0)->addTerritory(t2);
    
    // Works to print Continents
    cout <<* Continents.at(0)->getTerritories().at(0)<< endl;
    Continents.at(0)->getTerritories().at(0)->addAdjacentTerritories(t3);    
    cout <<* Continents.at(0)->getTerritories().at(0)->getAdjacentTerritories().at(0)<< endl;
   // cout << *Continents.at(0)<< endl;
    
 //   cout <<*c2->getTerritories().at(0)<< endl;

    //MapLoader ml("bigeurope.map");
    return 0;
}





