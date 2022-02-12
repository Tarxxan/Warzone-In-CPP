// Engine that controls the flow of the game by using the notion of state, transition, and command. 
// The state represents a certain phase of the game and dictates what are the valid actions or user commands that take place in this phase. 
// Some actions or commands may eventually trigger a transition to another state, which is what controls the flow of the game. 
#pragma once
#include <iostream>
#include "GameEngine.h"
#include "Player.h"
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

using namespace std;
using std::list;