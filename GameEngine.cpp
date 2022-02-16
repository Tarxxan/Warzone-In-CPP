#include <iostream>
#include <vector>
#include <string>
#include "GameEngine.h"

using namespace std;


GameEngine::GameEngine() {}//default constructor


// copy constructor
GameEngine::GameEngine(const GameEngine& GameEng) {
    this->GameState = GameEng.GameState;
    this->transition = GameEng.transition;
}

//assignment operator
GameEngine& GameEngine::operator = (const GameEngine& GameEng) {
    this->GameState = GameEng.GameState;
    this->transition = GameEng.transition;
    return *this;

}

//insertion operator
ostream& operator<<(ostream& output, const GameEngine& GameEng) {
    output << "We are in the " << GameEng.transition << " phase." << endl;
    output << "We are in the " << GameEng.GameState << " state." << endl;
    return output;
}


// called at the beginning of game 
void GameEngine::start() {
    this->setTrans("startup");
    this->setState("start");
}
void GameEngine::loadmap() {} //loads the map
void GameEngine::validatemap() {}
void GameEngine::addPlayers() {} //adds players to game
void GameEngine::assignCountries() {} //assigns players to a country
void GameEngine::assignReinforcement() {} //reinforces the players territories with troops
void GameEngine::issueOrders() {}//issues the players orders
void GameEngine::endIssueOrders() {}
void GameEngine::executeOrders() {} //executes the players orders


//getters and setters
void GameEngine::setState(string s) {
    this->GameState = s;
}
string GameEngine::getState() {
    return this->GameState;
}
int GameEngine::getPlayers() {
    return players;
}
void GameEngine::setPlayers(int p) {
    this->players = p;
}
void GameEngine::setTrans(string s) {
    this->transition = s;
}
string GameEngine::getTrans() {
    return this->transition;
}



