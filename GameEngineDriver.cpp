

#include "GameEngine.h"
#include <ctime>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{

	GameEngine* GE = new GameEngine;

	//start of the game
	GE->startupPhase();


	//end of the game, avoid memotry leak 
	delete GE;
	GE = nullptr;


	system("pause");
	return 0;
}