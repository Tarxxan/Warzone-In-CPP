#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <chrono>
#include <random>

#include "GameEngine.h"



using namespace std;


//default constructor
GameEngine::GameEngine(){
    LogObserver* observer = new LogObserver(this);
    GameState = "";
    numPlayers = 0;
}


// copy constructor
GameEngine::GameEngine(const GameEngine& GameEng) {
    this->GameState = GameEng.GameState;
    
}

GameEngine::~GameEngine()
{
    // player calls territory destructor 
    for (Player *p : allPlayers ) {

      
        delete p;
        p = nullptr;
    }

    delete mapL;
    mapL = nullptr;


}

//assignment operator
GameEngine& GameEngine::operator = (const GameEngine& GameEng) {
    this->GameState = GameEng.GameState;
    return *this;

}

//insertion operator
ostream& operator<<(ostream& output, const GameEngine& GameEng) {
    output << "We are in the " << GameEng.GameState << " state." << endl;
    return output;
}


//getters and setters
void GameEngine::setState(string s) {
    this->GameState = s;
}
string GameEngine::getState() {
    return this->GameState;
}


// new state string that will be written in log file.
string GameEngine::stringToLog()
{
    return  "The game has transitioned to a new game state: " + this->getState();
}


//start up phase 
void GameEngine::startupPhase()
{
    CommandProcessor* cp=NULL;
    string mapName;
   
    cout << "Welcome to Warzone!" << endl;

    
    // boolean if user decided console or file. 
    bool isSet = false;

    //Check if command is from file or console
    while (!isSet) {

        
        // set state 
        this->setState("start");

        // regex to find command format
        std::regex e ("-file[ ]+[^]+.txt");
        std::smatch cm;

        // ask user to choose between console or file
        string conOrFile = "";
        cout << "Please enter one of the following:" << endl
            << " -console to enter commands from console" << endl
            << " -file <filename> to read commands from a file" << endl;
        getline(cin, conOrFile);
        if (conOrFile == "-console")
        {
            cp = new CommandProcessor();
            isSet = true;

        }
        else if (regex_match(conOrFile, cm, e))
        {
            //check command file 
            ifstream f(conOrFile.substr(6).c_str());

            //if command file is in the path is good 
            if (f.good()) {
                cp = new FileCommandProcessorAdapter(conOrFile.substr(6));
                isSet = true;
            }

        }
        else {
        
            cout << "Invalid command" << endl;
        }
    
    }

    
    //-------------turnament mode-----------------------
    
    Command* cmdObj = cp->getCommand(this);

    
    if (cp->isTournament) {

        

        tournamentMode(cp);

        system("pause");
        system("exit");

    }
    



    //-----------load map-------------- 
    // loop untill you load a Good map
    while (this->getState() == "start") {
        
        cout << "\nUse loadmap <filename> command to load a map" << endl;

        // command object returned
        // At this point, all the command and state validation is done internally from commandProcessor.. 
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
        
        cin >> this->numPlayers; 

        // if non-integer input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            numPlayers = 0;
        }
        

        if (numPlayers >= 2 && numPlayers <= 6)
        {
            cout << "\n>>You entered " << numPlayers << " if this is correct, type \"yes\". If not type anything." << endl;

            cin.clear();
            cin.ignore(10000, '\n');
            string temp;
            
            cin >> temp;
            if (temp.compare("yes") == 0)
            {
                cout << "\nUse addplayer <playername> command to enter players in the game" << endl;
                cin.clear();
                cin.ignore(10000, '\n');


                for (int i = 0; i < numPlayers;) {

                    Command* cmdObj = cp->getCommand(this);

                    //if command is valid
                    if (cmdObj->isValid && cmdObj->command.substr(0, 9) == "addplayer") {
                   
                        
                        bool isDup = false;
                        
                        //check if player name is not a duplicate
                        
                        for (int k = 0; k < allPlayers.size(); k++) {

                            

                            if (cmdObj->command.substr(10) == allPlayers[k]->getName()) {

                                cout << "It is a duplicate name. " << endl;
                                isDup = true;
                            }
                            
                            
                        }
                           
                        if (!isDup) {
                            //create player object
                            Player* p = new Player(cmdObj->command.substr(10));

                            allPlayers.push_back(p);
                            cout << "\tPlayer " << p->getName() << " added..." << endl;
                            if (i == 0) {
                                this->transition("playersadded");
                            }
                            i++;
                        }
                                
                            
                        
                    }
                }

                //all players are added. Moving to gamestart state.
                break;

            }

            
        }
        else
            cout << ">>You must have 2-6 players" << endl;
    }
    
    // Setting all the player's opponents to be used in Negotiate Card
    for (int i = 0; i < allPlayers.size(); i++) {
        for (int j = 0; j < allPlayers.size(); j++) {
            if (i == j) {
                continue;
            }
            else {
                allPlayers[i]->setOpponents(allPlayers[j]);
            }
        }
    }
    //------gamestart--------------------


    while (this->getState().compare("playersadded") == 0 ) {

        cout << "\n\nUse gamestart command to enter the main game." << endl;
  

        //catches gamestart command
        Command* cmdObj = cp->getCommand(this);


        if (cmdObj->isValid && cmdObj->command == "gamestart") {
            

            

            //--------------------------------------------------------------------
            // a) fairly distribute all the territories to the players"
            for (int i = 0; i < this->mapL->combinedTerritories.size();) {
                
                for (int j = 0; j < allPlayers.size();j++) {
                    
                    allPlayers[j]->addTerritory(mapL->combinedTerritories[i]);
                    i++;
                }
            }
            
            // Testing win condition
            /*
            for (int i = 0; i < this->mapL->combinedTerritories.size()-1;) {
                allPlayers[0]->addTerritory(mapL->combinedTerritories[i]);
                i++;
            }
            allPlayers[1]->addTerritory(mapL->combinedTerritories[mapL->combinedTerritories.size()-1]);
            
            cout << "\nDistributing all the territories to the players.." << endl;

            //testing for demo , print out one players details
            cout << "\t" << * allPlayers[0] << endl;
            */

            //--------------------------------------------------------------------
            //b) determine randomly the order of play of the players in the game"
            //randomly changes the order of players
            unsigned seed = chrono::system_clock::now()
                .time_since_epoch()
                .count();
            shuffle(allPlayers.begin(), allPlayers.end(),default_random_engine(seed));


            cout << "\nDetermine randomly the order of play of the players in the game" << endl;

            //printing random orders of players for demo
            for (Player* p : allPlayers) {
                cout << "\t"<< p->getName() << endl;
            }


            //--------------------------------------------------------------------
            //c) give 50 initial armies to the players, which are placed in their respective

            for (int i = 0; i < allPlayers.size(); i++) {
                allPlayers[i]->setAvailableArmies(50);
            }
            cout <<"\nAssigning 50 initial armies to the players..." << endl;

            // show one of the player has initial army value 50 - for demo
            cout << "\t"<<allPlayers[0]->getName() << ": " << allPlayers[0]->getAvailableArmies() << endl;



            //--------------------------------------------------------------------
            //d) let each player draw 2 initial cards from the deck using the decks draw() method"
            
            Deck* deck = new Deck; 
            deck->initalizeDeck();

            //each player draw 2 cards
            for (int i = 0; i < allPlayers.size(); i++) {
                deck->draw(allPlayers[i]);
                deck->draw(allPlayers[i]);

            }

            cout << "\neach player draw 2 initial cards from the deck..." << endl;
            
            // print draw result for demo
            for (Player* p : allPlayers) {
                cout << * p->getPlayerHand() << endl;
            }
            

            //--------------------------------------------------------------------
            //e) switch the game to the play phase

            cout << "Entering the play phase!" << endl;

            //set state to assignreinforcement
            this->transition("assignreinforcement");

            // enter main game loop
            if (this->getState() == "assignreinforcement") {

                

                // enter main game loop
                mainGameLoop();


                //avoid memory leak
                delete cp;
                cp = nullptr;

                delete deck;
                deck = nullptr;



            }
        }
    }
}

void GameEngine::transition(string nextState)
{
    this->setState(nextState);
    Notify(this);

}

void GameEngine::computeContinentControlValue(Player *p) {
    int continentControlValue = 0;
    
    for (auto c : mapL->map->getAllContinents()) {
        bool ownsContinent = true;
        vector<Territory*> allTerritories = c->getTerritories();
        for (auto t : allTerritories) {
            if (p != t->getOwnerOfTerritory()) {
                ownsContinent = false;
                break;
            }
        }
        if (ownsContinent == true) {
            cout << "\n" << p->getName() << " has all the continent of " << c->getContinentName() << endl;
            cout << p->getName() << " receives extra " << c->getContinentControlValue() << " armies\n" << endl;
            continentControlValue += c->getContinentControlValue();
        }
    }
    if (continentControlValue > 0) {
        p->addAvailableArmies(continentControlValue);
        cout << "\n"  << p->getName() << "\'s total additional armies : " << continentControlValue << "\n" << endl;
    }
    
}


// TODO :comment
void GameEngine::tournamentMode(CommandProcessor* cp)
{

    int gRound = cp->gameRounds;
    vector<string> mapList = cp->mapFilesList;
    vector<string> playerList = cp->playersStrat;
    int turns = cp->turnsPerGame;


    for (  auto i : mapList) {

        MapLoader* ml = new MapLoader(i);

        this->mapL = ml;
        if (!mapL->isbadFile) {

            // state changed 
            this->transition("maploaded");
        }


        

        if (!this->mapL->map->validate()) {

            cout << "Game ends." << endl;
            system("pause");
            system("exit");

        }


        this->transition("mapvalidated");

        int count = 0;

        for (auto playerName : playerList) {

            count++;

            playerName += count;

            //create player object
            Player* pl = new Player(playerName);

            //PlayerStrategy* ps = new PlayerStrategy();

            if (playerName == "Benevolent") {
                BenevolentPlayerStrategy* bps = new BenevolentPlayerStrategy(pl);

                //PlayerStrategy* bps = new BenevolentPlayerStrategy(pl);
                pl->setStrategy(bps);
            
            }
            else if (playerName == "Aggressive") {
                AgressivePlayerStrategy* aps = new AgressivePlayerStrategy(pl);
                pl->setStrategy(aps);
            
            }
            else if (playerName == "Neutral") {
                NeutralPlayerStrategy* nps = new NeutralPlayerStrategy(pl);
                pl->setStrategy(nps);
            }
            else {
                CheaterPlayerStrategy* cps = new CheaterPlayerStrategy(pl);
                pl->setStrategy(cps);
            }
            



            allPlayers.push_back(pl);
            this->transition("playersadded");
            
        
        }

        

        while (gRound>0) {

            gameSetup(cp);

            for (auto i : allPlayers) {

                i->getPlayerHand()->getHand().clear();
                //TODO : memory leaks??

                i->getOrders()->getOrders().clear();

                i->getTerritories().clear();

                i->setAvailableArmies(0);

                

            }
            gRound--;

            
        
        }

        // TODO: check if we are deleting player pointer after each game
            //allPlayers.clear();


        
    }









}

void GameEngine::gameSetup(CommandProcessor* cp)
{

    // Setting all the player's opponents to be used in Negotiate Card
    for (int i = 0; i < allPlayers.size(); i++) {
        for (int j = 0; j < allPlayers.size(); j++) {
            if (i == j) {
                continue;
            }
            else {
                allPlayers[i]->setOpponents(allPlayers[j]);
            }
        }
    }
    //------gamestart--------------------


       
            // a) fairly distribute all the territories to the players"
        for (int i = 0; i < this->mapL->combinedTerritories.size();) {

            for (int j = 0; j < allPlayers.size(); j++) {

                allPlayers[j]->addTerritory(mapL->combinedTerritories[i]);
                i++;
            }
        }

      

            
        //b) determine randomly the order of play of the players in the game"
        //randomly changes the order of players
        unsigned seed = chrono::system_clock::now()
            .time_since_epoch()
            .count();
        shuffle(allPlayers.begin(), allPlayers.end(), default_random_engine(seed));

          
        //c) give 50 initial armies to the players, which are placed in their respective

        for (int i = 0; i < allPlayers.size(); i++) {
            allPlayers[i]->setAvailableArmies(50);
        }
        
          
         
        //d) let each player draw 2 initial cards from the deck using the decks draw() method"

        Deck* deck = new Deck;
        deck->initalizeDeck();

        //each player draw 2 cards
        for (int i = 0; i < allPlayers.size(); i++) {
            deck->draw(allPlayers[i]);
            deck->draw(allPlayers[i]);

        }


        //e) switch the game to the play phase

        
        //set state to assignreinforcement
        this->transition("assignreinforcement");

        // enter main game loop
        if (this->getState() == "assignreinforcement") {



            // enter main game loop
            tournamentMainGameLoop(cp->turnsPerGame);


            ////avoid memory leak
            //delete cp;
            //cp = nullptr;

            //delete deck;
            //deck = nullptr;



        }
       
    


}

void GameEngine::tournamentMainGameLoop(int turns)
{
    

    while (turns > 0 && allPlayers.size() != 1) {
        /*reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();*/
        
        turns--;

    }
 
    cout << "anything" << endl;
    //TODO : determine winner / draw output.......
  
    

}













void GameEngine::reinforcementPhase() {
    cout << "\nEntering Reinforcement Phase" << endl;
    for (int i = 0; i < allPlayers.size(); i++) {
        computeContinentControlValue(allPlayers[i]);    // compute the continent control values to add if player possesses
                                                        // all territories of a continent
        allPlayers[i]->computeReinforcementPool();          // compute the reinforcementPool based on number of territories player possesses 
    }
    cout << "\nExiting Reinforcement Phase\n" << endl;
}
void GameEngine::issueOrdersPhase() {
    cout << "\nEntering Issue Orders Phase" << endl;
    for (auto p : allPlayers) {
        p->issueOrder();
    }
    cout << "\nExiting Issue Orders Phase\n" << endl;
}
void GameEngine::executeOrdersPhase() {
    cout << "\nEntering Execute Orders Phase" << endl;
    for (auto p : allPlayers) {
        
       while(p->getOrders()->getOrders().size() > 0)  {
            cout << "\n-----------------------\nExecuting order: \n" << *p->getOrders()->getOrders()[0] << endl;
            p->getOrders()->getOrders()[0]->execute();
        }
    }

    for (int i = 0; i < allPlayers.size(); i++) {
        if (allPlayers[i]->getTerritories().size() == 0) {
            cout << "\nPlayer : " << allPlayers[i]->getName() << " occupies 0 territory " << endl;
            cout << "Player : " << allPlayers[i]->getName() << " is now eliminated from the game " << endl;
            allPlayers.erase(allPlayers.begin()+i);       // eliminate player if they do not possess any territory
        }
    }
    cout << "Exiting Execute Orders Phase\n" << endl;
}


//part 3 assigment 2
void GameEngine::mainGameLoop()
{
    cout << "in maingame loop" << endl;
    cout << "..........playing........" << endl;
    while (allPlayers.size() != 1) {
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();
    }
    cout << allPlayers[0]->getName() << " has won" << endl;
    cout << "End of game! BYE!" << endl;
    exit(1);

}
