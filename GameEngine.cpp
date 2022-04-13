#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <chrono>
#include <random>
#include <typeinfo>
#include "GameEngine.h"

using namespace std;

// default constructor
GameEngine::GameEngine()
{
    LogObserver *observer = new LogObserver(this);
    GameState = "";
    numPlayers = 0;
}

// copy constructor
GameEngine::GameEngine(const GameEngine &GameEng)
{
    this->GameState = GameEng.GameState;
}

// GameEngine destructor calls player and maploader destructor
GameEngine::~GameEngine()
{

    for (Player *p : allPlayers)
    {

        delete p;
        p = nullptr;
    }

    delete mapL;
    mapL = nullptr;
}

// assignment operator
GameEngine &GameEngine::operator=(const GameEngine &GameEng)
{
    this->GameState = GameEng.GameState;
    return *this;
}

// insertion operator
ostream &operator<<(ostream &output, const GameEngine &GameEng)
{
    output << "We are in the " << GameEng.GameState << " state." << endl;
    return output;
}

// getters and setters
void GameEngine::setState(string s)
{
    this->GameState = s;
}
string GameEngine::getState()
{
    return this->GameState;
}

// new state string that will be written in log file.
string GameEngine::stringToLog()
{
    return "The game has transitioned to a new game state: " + this->getState();
}

// start up phase, game initialization before players begin to play
void GameEngine::startupPhase()
{
    CommandProcessor *cp = NULL;
    string mapName;

    std::cout << "Welcome to Warzone!" << endl;

    // boolean if user decided console or file.
    bool isSet = false;

    // Check if command is from file or console
    while (!isSet)
    {

        // set state
        this->setState("start");

        // regex to find command format
        std::regex e("-file[ ]+[^]+.txt");
        std::smatch cm;

        // ask user to choose between console or file
        string conOrFile = "";
        std::cout << "Please enter one of the following:" << endl
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
            // check command file
            ifstream f(conOrFile.substr(6).c_str());

            // if command file is in the path is good
            if (f.good())
            {
                cp = new FileCommandProcessorAdapter(conOrFile.substr(6));
                isSet = true;
            }
        }
        else
        {

            std::cout << "Invalid command" << endl;
        }
    }

    //-------------turnament mode-----------------------

    Command *cmdObj = cp->getCommand(this);

    // this is responsible for our tournament logic
    if (cp->isTournament)
    {
        tournamentMode(cp);

        system("pause");
        exit(0);
    }

    if (cmdObj->command.find("tournament") != string::npos)
    {
        std::cout << "Invalid Tournament Command, program will now exit" << endl;
        exit(0);
    }

    //-----------load map--------------
    // loop untill you load a Good map
    while (this->getState() == "start")
    {

        std::cout << "\nUse loadmap <filename> command to load a map" << endl;

        // command object returned
        // At this point, all the command and state validation is done internally from commandProcessor..
        Command *cmdObj = cp->getCommand(this);

        // if command and state validation is good
        if (cmdObj->isValid)
        {
            mapName = cmdObj->command.substr(8); // extrac map file name

            // load the map
            mapL = new MapLoader(mapName);

            // if it's a good .map file, change state.
            if (!mapL->isbadFile)
            {

                // state changed
                this->transition("maploaded");
            }
        }
    }

    //-----------validate map---------------
    // check if map is valid
    while (GameState == "maploaded")
    {
        std::cout << "\nUse validatemap command to validate the map" << endl;

        Command *cmdObj = cp->getCommand(this);

        if (cmdObj->isValid)
        {
            if (this->mapL->map->validate())
            {
                // map is valid
                this->transition("mapvalidated");
            }
            else
            {
                // map is invalid.
                std::cout << "Map is invalid, exiting the game." << endl;
                exit(0);
            }
        }
    }

    //-----------addplayer <playername>---------

    while (this->getState() == "mapvalidated" || this->getState() == "playersadded")
    {
        std::cout << ">>How many players will be playing Warzone?(2-6 players) :" << endl;

        cin >> this->numPlayers;

        // if non-integer input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            numPlayers = 0;
        }

        if (numPlayers >= 2 && numPlayers <= 6)
        {
            std::cout << "\n>>You entered " << numPlayers << " if this is correct, type \"yes\". If not type anything." << endl;

            cin.clear();
            cin.ignore(10000, '\n');
            string temp;

            cin >> temp;
            if (temp.compare("yes") == 0)
            {
                std::cout << "\nUse addplayer <playername> command to enter players in the game" << endl;
                cin.clear();
                cin.ignore(10000, '\n');

                for (int i = 0; i < numPlayers;)
                {

                    Command *cmdObj = cp->getCommand(this);

                    // if command is valid
                    if (cmdObj->isValid && cmdObj->command.substr(0, 9) == "addplayer")
                    {

                        bool isDup = false;

                        // check if player name is not a duplicate

                        for (int k = 0; k < allPlayers.size(); k++)
                        {

                            if (cmdObj->command.substr(10) == allPlayers[k]->getName())
                            {

                                std::cout << "It is a duplicate name. " << endl;
                                isDup = true;
                            }
                        }

                        if (!isDup)
                        {
                            // create player object
                            Player *p = new Player(cmdObj->command.substr(10));

                            allPlayers.push_back(p);
                            std::cout << "\tPlayer " << p->getName() << " added..." << endl;
                            if (i == 0)
                            {
                                this->transition("playersadded");
                            }
                            i++;
                        }
                    }
                }

                // all players are added. Moving to gamestart state.
                break;
            }
        }
        else
            std::cout << ">>You must have 2-6 players" << endl;
    }

    // Setting all the player's opponents to be used in Negotiate Card
    for (int i = 0; i < allPlayers.size(); i++)
    {
        for (int j = 0; j < allPlayers.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                allPlayers[i]->setOpponents(allPlayers[j]);
            }
        }
    }
    //------gamestart--------------------

    while (this->getState().compare("playersadded") == 0)
    {

        std::cout << "\n\nUse gamestart command to enter the main game." << endl;

        // catches gamestart command
        Command *cmdObj = cp->getCommand(this);

        if (cmdObj->isValid && cmdObj->command == "gamestart")
        {

            //--------------------------------------------------------------------
            // a) fairly distribute all the territories to the players"
            for (int i = 0; i < this->mapL->combinedTerritories.size();)
            {

                for (int j = 0; j < allPlayers.size(); j++)
                {

                    int check = i;
                    if (check < this->mapL->combinedTerritories.size())
                    {
                        allPlayers[j]->addTerritory(mapL->combinedTerritories[i]);
                    }
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

            std::cout << "\nDistributing all the territories to the players.." << endl;

            //testing for demo , print out one players details
            std::cout << "\t" << * allPlayers[0] << endl;
            */

            //--------------------------------------------------------------------
            // b) determine randomly the order of play of the players in the game"
            // randomly changes the order of players
            unsigned seed = chrono::system_clock::now()
                                .time_since_epoch()
                                .count();
            std::shuffle(allPlayers.begin(), allPlayers.end(), default_random_engine(seed));

            std::cout << "\nDetermine randomly the order of play of the players in the game" << endl;

            // printing random orders of players for demo
            for (Player *p : allPlayers)
            {
                std::cout << "\t" << p->getName() << endl;
            }

            //--------------------------------------------------------------------
            // c) give 50 initial armies to the players, which are placed in their respective

            for (int i = 0; i < allPlayers.size(); i++)
            {
                allPlayers[i]->setAvailableArmies(50);
            }
            std::cout << "\nAssigning 50 initial armies to the players..." << endl;

            // show one of the player has initial army value 50 - for demo
            std::cout << "\t" << allPlayers[0]->getName() << ": " << allPlayers[0]->getAvailableArmies() << endl;

            //--------------------------------------------------------------------
            // d) let each player draw 2 initial cards from the deck using the decks draw() method"

            Deck *deck = new Deck;
            deck->initalizeDeck();

            // set deck for each player
            for (int i = 0; i < allPlayers.size(); i++)
            {
                allPlayers[i]->setGameDeck(deck);
            }

            // each player draw 2 cards
            for (int i = 0; i < allPlayers.size(); i++)
            {
                deck->draw(allPlayers[i]);
                deck->draw(allPlayers[i]);
            }

            std::cout << "\neach player draw 2 initial cards from the deck..." << endl;

            // print draw result for demo
            for (Player *p : allPlayers)
            {
                std::cout << *p->getPlayerHand() << endl;
            }

            //--------------------------------------------------------------------
            // e) switch the game to the play phase

            std::cout << "Entering the play phase!" << endl;

            // set state to assignreinforcement
            this->transition("assignreinforcement");

            // enter main game loop
            if (this->getState() == "assignreinforcement")
            {

                // enter main game loop
                mainGameLoop();

                // avoid memory leak
                delete cp;
                cp = nullptr;

                delete deck;
                deck = nullptr;
            }
        }
    }
}

// transition states, calls notify
void GameEngine::transition(string nextState)
{
    this->setState(nextState);
    Notify(this);
}

// computes the amount of armies given to players after each turn
void GameEngine::computeContinentControlValue(Player *p)
{
    int continentControlValue = 0;

    for (auto c : mapL->map->getAllContinents())
    {
        bool ownsContinent = true;
        vector<Territory *> allTerritories = c->getTerritories();
        for (auto t : allTerritories)
        {
            if (p != t->getOwnerOfTerritory())
            {
                ownsContinent = false;
                break;
            }
        }
        if (ownsContinent == true)
        {
            std::cout << "\n"
                      << p->getName() << " has all the continent of " << c->getContinentName() << endl;
            std::cout << p->getName() << " receives extra " << c->getContinentControlValue() << " armies\n"
                      << endl;
            continentControlValue += c->getContinentControlValue();
        }
    }
    if (continentControlValue > 0)
    {
        p->addAvailableArmies(continentControlValue);
        std::cout << "\n"
                  << p->getName() << "\'s total additional armies : " << continentControlValue << "\n"
                  << endl;
    }
}

// used in startup phase, pass in command processor which stores tournament command rules
void GameEngine::tournamentMode(CommandProcessor *cp)
{

    int gRound = cp->gameRounds;
    vector<string> mapList = cp->mapFilesList;
    vector<string> playerList = cp->playersStrat;
    int turns = cp->turnsPerGame;

    // plays every maps in the list for the specified amount of rounds
    for (auto i : mapList)
    {
        while (gRound > 0)
        {
            MapLoader *ml = new MapLoader(i);
            this->mapL = ml;

            // if map is valid, transition state
            if (!mapL->isbadFile)
            {
                this->transition("maploaded");
                std::cout << ">>MapName:" << ml->map->getMapName() << endl;
            }

            // if map is not valid, system exits
            if (!this->mapL->map->validate())
            {

                std::cout << "Game ends." << endl;
                system("pause");
                exit(0);
            }

            this->transition("mapvalidated");
            int count = 0;

            // create player with proper player strategy
            for (auto playerName : playerList)
            {
                count++;

                string dupName = playerName + to_string(count);
                Player *pl = new Player(dupName, playerName);

                allPlayers.push_back(pl);
                this->transition("playersadded");
            }

            gameSetup(cp);
            // end of each round

            // calls destructors to reset between rounds
            for (auto i : allPlayers)
            {

                delete i->getStrategy();
                i = nullptr;
            }
            gRound--;
            allPlayers.clear();

            // delete maploader to reset between rounds, avoid memeory leak.
            delete this->mapL;
            ml = nullptr;
            this->mapL = nullptr;
        }
        gRound = cp->gameRounds;
    }

    // print final result to log file
    finalResult(cp);
}

// game setup for tournament mode., distribute troops territories and randomize play order
void GameEngine::gameSetup(CommandProcessor *cp)
{
    // Setting all the player's opponents to be used in Negotiate Card
    for (int i = 0; i < allPlayers.size(); i++)
    {
        for (int j = 0; j < allPlayers.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                allPlayers[i]->setOpponents(allPlayers[j]);
            }
        }
    }

    //------gamestart--------------------
    // a) fairly distribute all the territories to the players
    for (int i = 0; i < this->mapL->combinedTerritories.size();)
    {

        for (int j = 0; j < allPlayers.size(); j++)
        {

            int check = i;
            if (check < this->mapL->combinedTerritories.size())
            {
                allPlayers[j]->addTerritory(mapL->combinedTerritories[i]);
            }
            i++;
        }
    }

    // b) determine randomly the order of play of the players in the game
    // randomly changes the order of players
    unsigned seed = chrono::system_clock::now()
                        .time_since_epoch()
                        .count();
    std::shuffle(allPlayers.begin(), allPlayers.end(), default_random_engine(seed));

    // c) give 50 initial armies to the players, which are placed in their respective
    for (int i = 0; i < allPlayers.size(); i++)
    {
        allPlayers[i]->setAvailableArmies(50);
    }

    // d) let each player draw 2 initial cards from the deck using the decks draw() method
    Deck *deck = new Deck;
    deck->initalizeDeck();

    // each player draw 2 cards
    for (int i = 0; i < allPlayers.size(); i++)
    {
        deck->draw(allPlayers[i]);
        deck->draw(allPlayers[i]);
    }

    // e) switch the game to the play phase
    // set state to assignreinforcement
    this->transition("assignreinforcement");

    // enter main game loop
    if (this->getState() == "assignreinforcement")
    {
        // enter main game loop
        tournamentMainGameLoop(cp->turnsPerGame);
    }
}

// repeats the three game phases for given amount of turns, contains winner logic
void GameEngine::tournamentMainGameLoop(int turns)
{
    while (turns > 0 && allPlayers.size() != 1)
    {

        std::cout << "Number of turns left: " << turns << endl;

        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();

        turns--;
    }

    // winner logic, win or draw
    if (allPlayers.size() == 1)
    {
        winners.push_back(allPlayers.at(0)->getName());
        std::cout << ">>Congratulations! Winner is " << allPlayers.at(0)->getName() << endl;
    }
    else if (allPlayers.size() > 1)
    {
        std::cout << "Draw" << endl;
        winners.push_back("Draw");
    }
}

// print final result to log file , pass in command processor
void GameEngine::finalResult(CommandProcessor *cp)
{
    string finalOutput = "";

    finalOutput += "\nTounament Mode:\n"
                   "M: ";

    for (auto i : cp->mapFilesList)
    {
        finalOutput += i + ", ";
    }

    finalOutput += "\n";

    finalOutput += "P: ";

    for (auto i : cp->playersStrat)
    {
        finalOutput += i + ", ";
    }

    finalOutput += "\n";

    finalOutput += "G: ";
    finalOutput += std::to_string(cp->gameRounds);
    finalOutput += "\n";
    finalOutput += "D: ";
    finalOutput += std::to_string(cp->turnsPerGame);
    finalOutput += "\n";

    finalOutput += "\nResults:\n";
    //--
    finalOutput += "-----------------";
    for (int i = 0; i < cp->gameRounds; i++)
    {
        finalOutput += "------------------";
    }
    finalOutput += "\n";
    //---

    finalOutput += "| \t\t\t|";

    for (int i = 1; i <= cp->gameRounds; i++)
    {
        finalOutput += "Game ";
        finalOutput += std::to_string(i);

        finalOutput += "\t\t|";
    }
    finalOutput += "\n";

    //--
    finalOutput += "-----------------";
    for (int i = 0; i < cp->gameRounds; i++)
    {
        finalOutput += "------------------";
    }
    finalOutput += "\n";
    //---

    int counter = 0;

    for (auto i : cp->mapFilesList)
    {
        finalOutput += "| " + i;
        finalOutput += "\t|";
        for (int j = 0; j < cp->gameRounds; j++)
        {

            finalOutput += winners.at(j + counter);
            finalOutput += "\t\t|";
        }
        finalOutput += "\n";
        //--
        finalOutput += "-----------------";
        for (int i = 0; i < cp->gameRounds; i++)
        {
            finalOutput += "------------------";
        }
        finalOutput += "\n";
        //---
        counter += cp->gameRounds - 1;
    }

    cp->CommandList.front()->saveEffect(finalOutput);
}

// uses functions to provide reinforcement troops to play
void GameEngine::reinforcementPhase()
{
    std::cout << "\n>>Entering Reinforcement Phase" << endl;
    for (int i = 0; i < allPlayers.size(); i++)
    {
        computeContinentControlValue(allPlayers[i]); // compute the continent control values to add if player possesses
                                                     // all territories of a continent
        allPlayers[i]->computeReinforcementPool();   // compute the reinforcementPool based on number of territories player possesses
    }
    std::cout << ">>Exiting Reinforcement Phase\n"
              << endl;
}

// calls issue order for each player in the game (endup calling player strategy)
void GameEngine::issueOrdersPhase()
{
    std::cout << "\n>>Entering Issue Orders Phase" << endl;
    for (auto p : allPlayers)
    {
        p->issueOrder();
    }
    std::cout << ">>Exiting Issue Orders Phase\n"
              << endl;
}

// execute orders and elimnates any players with zero territories
void GameEngine::executeOrdersPhase()
{
    std::cout << "\n>>Entering Execute Orders Phase" << endl;
    for (auto p : allPlayers)
    {

        while (p->getOrders()->getOrders().size() > 0)
        {
            std::cout << "\n-----------------------\nExecuting order: \n"
                      << *p->getOrders()->getOrders()[0] << endl;
            p->getOrders()->getOrders()[0]->execute();
        }
    }

    for (int i = 0; i < allPlayers.size(); i++)
    {
        if (allPlayers[i]->getTerritories().size() == 0)
        {
            std::cout << "\nPlayer : " << allPlayers[i]->getName() << " occupies 0 territory " << endl;
            std::cout << "Player : " << allPlayers[i]->getName() << " is now eliminated from the game " << endl;
            allPlayers.erase(allPlayers.begin() + i); // eliminate player if they do not possess any territory
        }
    }
    std::cout << ">>Exiting Execute Orders Phase\n"
              << endl;
}

// part 3 assigment 2
void GameEngine::mainGameLoop()
{

    std::cout << "..........playing........" << endl;
    while (allPlayers.size() != 1)
    {
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();
    }
    std::cout << allPlayers[0]->getName() << " has won" << endl;
    std::cout << "End of game! BYE!" << endl;
    exit(1);
}
