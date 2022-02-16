#pragma once
#include <string>
#include <iostream>
using namespace std;

class GameEngine
{

private:
     string GameState;
     string transition;
     int players;

public:
    GameEngine(); //default constructor
    GameEngine(const GameEngine& GameEng); //copy constructor
    GameEngine& operator = (const GameEngine& GameEng); //assignment operator
    friend ostream& operator<<(ostream& os, const GameEngine& GameEng); //stream insertion operator

     void start();
     void loadmap(); //loads the map
     void validatemap();
     void addPlayers(); //adds players to game
     void assignCountries(); //assigns players to a country
     void assignReinforcement(); //reinforces the players territories with troops
     void issueOrders(); //issues the players orders
     void endIssueOrders();
     void executeOrders(); //executes the players orders
     void setState(string s); //sets the state of the game
     string getState(); //gets the state of the game
     int getPlayers();
     void setPlayers(int p);
     void setTrans(string s);
     string getTrans();
};