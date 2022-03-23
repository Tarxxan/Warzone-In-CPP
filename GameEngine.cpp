#include <iostream>
#include <vector>
#include <string>

#include "GameEngine.h"
#include "CommandProcessor.h"
#include "Player.h"


using namespace std;



GameEngine::GameEngine() :GameState(""),players(0) {
    LogObserver* observer = new LogObserver(this);
}//default constructor


// copy constructor
GameEngine::GameEngine(const GameEngine& GameEng) {
    this->GameState = GameEng.GameState;
    //this->transition = GameEng.transition;
}

//assignment operator
GameEngine& GameEngine::operator = (const GameEngine& GameEng) {
    this->GameState = GameEng.GameState;
    //this->transition = GameEng.transition;
    return *this;

}

//insertion operator
ostream& operator<<(ostream& output, const GameEngine& GameEng) {
    //output << "We are in the " << GameEng.transition << " phase." << endl;
    output << "We are in the " << GameEng.GameState << " state." << endl;
    return output;
}

//
//// called at the beginning of game 
//void GameEngine::start() {
//    this->setTrans("startup");
//    this->setState("start");
//}
//void GameEngine::loadmap() {} //loads the map
//void GameEngine::validatemap() {}
//void GameEngine::addPlayers() {} //adds players to game
//void GameEngine::assignCountries() {} //assigns players to a country
//void GameEngine::assignReinforcement() {} //reinforces the players territories with troops
//void GameEngine::issueOrders() {}//issues the players orders
//void GameEngine::endIssueOrders() {}
//void GameEngine::executeOrders() {} //executes the players orders
//

//getters and setters
void GameEngine::setState(string s) {
    this->GameState = s;
}
string GameEngine::getState() {
    return this->GameState;
}
//int GameEngine::getPlayers() {
//    return players;
//}
//void GameEngine::setPlayers(int p) {
//    this->players = p;
//}
//void GameEngine::setTrans(string s) {
//    this->transition = s;
//}
//string GameEngine::getTrans() {
//    return this->transition;
//}



// new state string
string GameEngine::stringToLog()
{
    return  "The game has transitioned to a new game state: " + this->getState();
}


void GameEngine::startupPhase()
{

    // with polymorphism, we can use child class function even when child class is casted with parent class type.  
    CommandProcessor* cp;
    //FileCommandProcessorAdapter* fcpa;
    //Command* cmdObj;


    string mapName;

    


    cout << "Welcome to Warzone!" << endl;


    this->setState("start");

    //Check if command is from file or console
    string conOrFile = "";
    cout << "Please enter one of the following:" << endl
        << " -console to enter commands from console" << endl
        << " -file <filename> to read commands from a file" << endl;
    getline(cin, conOrFile);
    if (conOrFile == "-console")
    {
        cp = new CommandProcessor();

    }


    // --------------------------need to verify for'-file <??>'
    else if (conOrFile.find("-file") != string::npos)
    {
        //string path;
        //// --------------how do I pass the file path..? 
        //cin >> path;


        cp = new FileCommandProcessorAdapter(conOrFile.substr(6));

    }


    // loop untill you load a Good map
    while (this->getState() == "start") {
        //loadmap

        cout << "\nUse loadmap <filename> command to load a map" << endl;

        //command object returned
        // at this point, all the validation is done internally from commandProcessor.. 
        Command* cmdObj = cp->getCommand(this->GameState);


        if (cmdObj->isValid) {
            mapName = cmdObj->command.substr(8);// TODO: how to extrac map file name form cmdObjString?
            //load the map and is validated.. 
            mapL = new  MapLoader(mapName);



            if (!mapL->isbadFile) {
                //if it's a good file

                this->transition("maploaded");
            }

        }
        // TODO: if commandfile is bad. 
    }

    
    //check if map is valid

    Command* cmdObj = cp->getCommand(this->GameState);

    if (cmdObj->isValid) {
        if (this->mapL->map->validate()) {
            // map is valid

            this->transition("mapvalidated");

        }
        else {
            // map is invalid.
            cout << "Map is invalid, exiting game." << endl;
            exit(0);
        }
        
    }
    
    




    




    //------ 
    // cout<<"enter your command:";

    //cmdObj = cp->getCommand();

    //cmdObjString = cmdObj->command; // better with getter and setter?



}

void GameEngine::transition(string nextState)
{
    this->setState(nextState);
    Notify(this);

}
