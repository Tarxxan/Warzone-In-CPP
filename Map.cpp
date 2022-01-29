#include "Map.h"
#include <fstream> // IOStream
#include <string> // Needed for Getline method
using namespace std;



    // Territory::Territory(int TerritoryID, string Name, int Territorysoldiers)
    // {
    //    this-> TerritoryID=TerritoryID;
    //    this->Name=Name;
    //    this->TerritorySoldiers=Territorysoldiers;
    // };



    
    // Map loader can read any Domination map file.
// http://domination.sourceforge.net/getmaps.shtml
// Map loader creates a map object as a graph data structure.
// Map loader should be able to read any text file (even invalid ones)






// IO Stream Operators for MapLoader NOT exactly sure what these do tbh.

istream & operator >> (istream &in,  MapLoader &ML)
{
    cout << "Enter Map File";
    in >> ML.FileName;
    return in;
    }

ostream & operator << (ostream &out, const MapLoader &ML)
{
    out << ML.FileContents << endl;
    return out;
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
cout<< FileContents <<endl;
}




//default constructor 

//Copy constructor

// Im writing the driver in here for now because for some reason my linker doesnt wanna link the files.
int main() {
    string CurrentMap="";
    cout << "Which Map would you like to play"<<endl;
    cin >> CurrentMap;

    MapLoader ML(CurrentMap);
    cout << ML <<endl;
    return 0;
}