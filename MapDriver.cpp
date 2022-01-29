// Driver that reads many different map files, creates a Map object for valid files and rejects the
// invalid ones.
#include "Map.h"
#include <iostream>
using namespace std;

int main() {
    string CurrentMap="";
    cout << "Which Map would you like to play"<<endl;
    cin >> CurrentMap;

    MapLoader ML(CurrentMap);
    cout << ML;
    system("pause");
}