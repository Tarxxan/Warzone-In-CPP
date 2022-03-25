#include <iostream>
#include <vector>
#include <string>

#include "GameEngine.h"




using namespace std;



GameEngine::GameEngine() :GameState(""),numPlayers(0) {
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


    //global variable..
    string mapName;

    


    cout << "Welcome to Warzone!" << endl;

    //set state 
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
      /*  cin.clear();
        cin.ignore(10000, '\n');*/
    }


    // --------------------------need to verify for'-file <??>'
    else if (conOrFile.find("-file") != string::npos)
    {
        //string path;
        //// --------------how do I pass the file path..? 
        //cin >> path;


        cp = new FileCommandProcessorAdapter(conOrFile.substr(6));
      /*  cin.clear();
        cin.ignore(10000, '\n');*/
    }
    

    //-----------load map-------------- 

    // loop untill you load a Good map
    while (this->getState() == "start") {
        //loadmap

        cout << "\nUse loadmap <filename> command to load a map" << endl;

        //command object returned
        // at this point, all the command and state validation is done internally from commandProcessor.. 
        Command* cmdObj = cp->getCommand(this);


        // if command and state validation is good
        if (cmdObj->isValid) {
            mapName = cmdObj->command.substr(8);// extrac map file name

            //load the map 
            mapL = new  MapLoader(mapName);


            //if it's a good .map file, change state.
            if (!mapL->isbadFile) {
                
                // state changed 
                this->transition("maploaded");
            }

        }
        
        // TODO: if commandfile is bad. 
    }

    //-----------validate map---------------
    //check if map is valid
    while (GameState == "maploaded") {
        cout << "\nUse validatemap command to validate the map" << endl;

        Command* cmdObj = cp->getCommand(this);

        if (cmdObj->isValid) {
            if (this->mapL->map->validate()) {
                // map is valid
                this->transition("mapvalidated");

            }
            else {
                // map is invalid.
                cout << "Map is invalid, exiting the game." << endl;
                exit(0);
            }

        }
    
    }
    
    
    

    //-----------addplayer <playername>---------

    

    

    while (this->getState() == "mapvalidated" || this->getState() == "playersadded") {
        cout << ">>How many players will be playing Warzone?(2-6 players) :" << endl;
        
        
        cin >> this->numPlayers; //TODO: exception when string is inputed

        if (numPlayers >= 2 && numPlayers <= 6) //&& isdigit(numPlayers)
        {
            cout << "\n>>You entered " << numPlayers << " if this is correct, type \"yes\". If not type anything." << endl;


            string temp;
            //getline(cin, temp);
            cin >> temp;
            if (temp.compare("yes") == 0)
            {
                cout << "\nUse addplayer <playername> command to enter players in the game" << endl;

                for (int i = 0; i < numPlayers;) {


                    
                    Command* cmdObj = cp->getCommand(this);

                    //if command is valid
                    if (cmdObj->isValid && cmdObj->command.substr(0, 9) == "addplayer") {

                        //create player object
                        Player* p = new Player(cmdObj->command.substr(10));
                        
                        allPlayers.push_back(p);
                        cout << "\tPlayer " << p->getName()<<" added..." << endl;
                        if (i == 0) {
                            this->transition("playersadded");
                        }
                        i++;
                    }
                }



                




            }
            break;
        }
        else
            cout << "\n>>You must have 2-6 players" << endl;
    }
    


    //------gamestart--------------------


    while (this->getState().compare("playersadded") == 0 ) {

        cout << "\n\nUse gamestart command to enter the main game." << endl;
   /*         << "\n\ta) fairly distribute all the territories to the players"
            << "\n\tb) determine randomly the order of play of the players in the game"
            << "\n\tc) give 50 initial armies to the players, which are placed in their respective reinforcement pool"
            << "\n\td) let each player draw 2 initial cards from the deck using the decks draw() method"
            << "\n\te) switch the game to the play phase";*/


        //cout << "is it before gmdObj?" << endl;

        Command* cmdObj = cp->getCommand(this);

        //cout << "is it after gmdObj?" << endl;

        if (cmdObj->isValid && cmdObj->command == "gamestart") {
            

            this->transition("assignreinforcement");

            //--------------------------------------------------------------------
            // a) fairly distribute all the territories to the players"
            for (int i = 0; i < this->mapL->combinedTerritories.size();) {
                
                for (int j = 0; j < allPlayers.size();j++) {
                    
                    //cout << mapL->combinedTerritories[i] << endl;
                    allPlayers[j]->addTerritory(mapL->combinedTerritories[i]);
                    i++;

                    
                }
            }


            cout << "Distributing all the territories to the players.." << endl;

            //test
            //cout << *allPlayers[0] << endl;

            //--------------------------------------------------------------------
            //b) determine randomly the order of play of the players in the game"

            //changes the order of players
            random_shuffle(allPlayers.begin(), allPlayers.end());

            //cout << allPlayers[0]->getName() << endl;
            //cout << allPlayers[1]->getName() << endl;

            //--------------------------------------------------------------------
            //c) give 50 initial armies to the players, which are placed in their respective

            for (int i = 0; i < allPlayers.size(); i++) {
                allPlayers[i]->setAvailableArmies(50);
            }
            cout <<"Assigning 50 initial armies to the players..." << endl;

    /*        cout << allPlayers[0]->getAvailableArmies() << endl;
            cout << allPlayers[3]->getAvailableArmies();*/



            //--------------------------------------------------------------------
            //d) let each player draw 2 initial cards from the deck using the decks draw() method"
            
            Deck* deck = new Deck; //DELETE later
            deck->initalizeDeck();

            for (int i = 0; i < allPlayers.size(); i++) {
                deck->draw(allPlayers[i]);
                deck->draw(allPlayers[i]);


            }

            cout << "each player draw 2 initial cards from the deck..." << endl;
            //cout << *allPlayers[0]->getPlayerHand();
            //cout << *allPlayers[3]->getPlayerHand();


            //--------------------------------------------------------------------
            //e) switch the game to the play phase

            cout << "Entering the play phase!" << endl;

            // enter main game loop
            mainGameLoop();
            

        }//end of if


        


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

void GameEngine::mainGameLoop()
{
    cout << "in maingame loop" << endl;
}
