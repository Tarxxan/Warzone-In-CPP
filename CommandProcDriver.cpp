#include "CommandProcessor.h"
#include <iostream>
using namespace std;

// Waiting for gameEngine to be finished so i can try tetsing with the game Engine object
int main()
{
    while (true)
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
            commandProc->getCommand("maploaded");
            commandProc->getCommand("mapvalidated");
            commandProc->getCommand("playersadded");
            commandProc->getCommand("win");
            commandProc->getCommand("win");
            cout << "-------------------------" << endl;

        
            delete commandProc;
            commandProc = NULL;
        }

        else if (conOrFile.find("-file") != string::npos)
        {
            cout << endl;

            CommandProcessor *FCommandProc = new FileCommandProcessorAdapter(conOrFile.substr(6));
            FCommandProc->getCommand("start");
            FCommandProc->getCommand("maploaded");
            FCommandProc->getCommand("mapvalidated");
            FCommandProc->getCommand("playersadded");
            FCommandProc->getCommand("win");
            FCommandProc->getCommand("win");
            // This will show how we handle Invalid Commands.
            FCommandProc->getCommand("win");
            cout << "-------------------------" << endl;
    
            delete FCommandProc;
            FCommandProc = NULL;
        }

        string answer;
        cout << "Would you like to use a different format to get commands ? Y/N" << endl;
        getline(cin, answer);
        if (answer == "N")
            break;

            
    }

    GameEngine *ge = new GameEngine();
    ge->setState("quit");
    CommandProcessor *cp = new CommandProcessor();
    cp->getCommand(ge);
    delete ge;
    ge=nullptr;
    cout << "This GameEngine Stuff clearly worked since we changed state with the game Engine. More use of the collaboration of both of these classes in GE driver" << endl;
}