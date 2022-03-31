#include "CommandProcessor.h"
//#include "GameEngine.h"
#include <iostream>
using namespace std;

// Waiting for gameEngine to be finished so i can try tetsing with the game Engine object
int main()
{

    string conOrFile = "";
    cout << "Please enter one of the following:" << endl
         << " -console to enter commands from console" << endl
         << " -file <file name> to read commands from a file" << endl;
    getline(cin, conOrFile);
    if (conOrFile == "-console")
    {
        CommandProcessor *commandProc = new CommandProcessor();
        commandProc->getCommand("start");

        cout << " it is getting here" << endl;
        cout << commandProc->gameRounds + "\t" + commandProc->turnsPerGame << endl;

        delete commandProc;
        commandProc = NULL;
    }

    else if (conOrFile.find("-file") != string::npos)
    {
        cout << endl;
        CommandProcessor *FCommandProc = new FileCommandProcessorAdapter(conOrFile.substr(6));
        FCommandProc->getCommand("start");
        cout << FCommandProc->gameRounds << endl;
        cout << FCommandProc->turnsPerGame << endl;
        delete FCommandProc;
        FCommandProc = NULL;
    }

    return 0;
}