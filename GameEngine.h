#pragma once
#include <string>
#include <iostream>
#include "LoggingObserver.h"
#include "Map.h"
#include "Player.h"
#include "CommandProcessor.h"
using namespace std;

class GameEngine : public ILoggable, public Subject
{

private:
     string GameState;
     //string transition;
     int numPlayers;
     MapLoader* mapL;
     vector<Player*> allPlayers;
     


public:
    GameEngine(); //default constructor
    GameEngine(const GameEngine& GameEng); //copy constructor
    ~GameEngine();
    GameEngine& operator = (const GameEngine& GameEng); //assignment operator
    friend ostream& operator<<(ostream& os, const GameEngine& GameEng); //stream insertion operator


     void setState(string s); //sets the state of the game
     string getState(); //gets the state of the game

     // Added for project 2. 
     virtual string stringToLog(); // From Iloggable class
     void startupPhase(); // start of the game
     void transition(string nextState); //set states and notify objserber 
     void mainGameLoop(); 
};