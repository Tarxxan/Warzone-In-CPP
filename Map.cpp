#include "Map.h"
#include <fstream> // IOStream
#include <string> // Needed for Getline method
using namespace std;

//----------------------------------------------------------------------------------------------------
//-----------------------------Territory Class--------------------------------------------------------
//----------------------------------------------------------------------------------------------------
    Territory::Territory(int TerritoryID, std::string Name, int Territorysoldiers)
    {
       this-> TerritoryID=TerritoryID;
       this->Name=Name;
       this->TerritorySoldiers=Territorysoldiers;
       // Do we need to init a player in here
    };

    Territory::Territory(const Territory &CopyT){
        TerritoryID=CopyT.TerritoryID;
        Name=CopyT.Name;
        TerritorySoldiers=CopyT.TerritorySoldiers;
        // Same issue with pointer idk if i even need this
        //Player= CopyT.Player;
    }

    Territory& Territory::operator=(const Territory &AssignT){
    TerritoryID=AssignT.TerritoryID;
    Name=AssignT.Name;
    TerritorySoldiers = AssignT.TerritorySoldiers;
    return *this;
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

