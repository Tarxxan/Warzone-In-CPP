
// You must deliver a file named GameEngineDriver.cpp file that allows the user
// to type commands on the console, whose result is to trigger some state transitions
// Refer to graph is its complicated to explain

#include "GameEngine.h"
#include <ctime>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    GameEngine GM;

    GM.start();
    string command;
    while (true)
    {
        while (GM.getTrans().compare("startup") == 0)
        {

            string mapName;

            cout << "Welcome to Warzone! What what you like to do.( Ex. loadmap )" << endl;
            cin >> command;

            if (command.compare("loadmap") == 0)
            {
                GM.setState("maploaded");
            }
            else
                cout << "You must start by loading the map" << endl;

            while (GM.getState().compare("maploaded") == 0)
            {
                cout << " Whats the name of the map you want to load? :(Ex. bigeurope.map)" << endl;
                cin >> mapName;
                cout << "You have selected " << mapName << " would you like to validate the map or load another one? : (Ex. loadmap, validatemap )" << endl;
                cin >> command;
                if (command.compare("validatemap") == 0)
                {
                    GM.validatemap();
                    // Call explicitly to not forget to change state in real implementation
                    GM.setState("mapvalidated");
                }
                else
                    cout << "Returning to load another map" << endl;
            }
            if(GM.getState().compare("mapvalidated")==0){
                cout << "Validated map... " << endl;
            }
            

            while (GM.getState().compare("mapvalidated") == 0)
            {
                int playersPlaying;
                cout << "How many players will be playing Warzone? :" << endl;
                cin >> playersPlaying;
                if (playersPlaying > 1)
                {
                    cout << "You entered " << playersPlaying << " if this is correct, type \"addplayer\". If not type anything." << endl;
                    cin >> command;
                    if (command.compare("addplayer") == 0)
                    {

                        GM.addPlayers();
                        GM.setState("players added");
                        GM.setPlayers(playersPlaying);
                    }
                }
                else
                    cout << "You must have atleast two players to play" << endl;
            }

            while (GM.getState().compare("players added") == 0)
            {
                cout << "Are you sure " << GM.getPlayers() << " is the correct amount of players?" << endl;
                cout << "Type \"assigncountries\" to proceed or \"addplayer\" to change the players." << endl;
                cin >> command;
                if (command.compare("assigncountries") == 0)
                {
                    GM.assignCountries();
                    GM.setState("assign reinforcement");
                    GM.setTrans("play");
                }
                else if (command.compare("addplayer") == 0)
                {

                    int playersPlaying;
                    cout << "How many players will be playing Warzone? :" << endl;
                    cin >> playersPlaying;
                    if (playersPlaying > 1)
                    {
                        GM.addPlayers();
                        GM.setPlayers(playersPlaying);
                    }
                    else
                        cout << "You must have atleast two players to play" << endl;
                }
                else
                    cout << "Invalid input. Asking for player count again" << endl;
            }
        }
         if(GM.getState().compare("play")==0){
                cout << "Validated map... " << endl;
            }
        
        while (GM.getTrans().compare("play") == 0)
        {   

            while (GM.getState().compare("assign reinforcement") == 0)
            {
                cout << "Type \"issueorder\" to start playing" << endl;
                cin >> command;

                if (command.compare("issueorder") == 0)
                {
                    GM.setState("issue orders");
                }
                else
                    cout << "Invalid input. lets try this again." << endl;
            }

            while (GM.getState().compare("issue orders") == 0)
            {
                cout << "Each player will now get a turn to issue orders" << endl;
                for (int i = 0; i < GM.getPlayers(); i++)
                {
                    GM.issueOrders();
                }
                cout << "Type \"endissueorders\" to proceed or \"issueorder\" to restart" << endl;
                cin >> command;
                if (command.compare("endissueorders") == 0)
                {
                    GM.setState("execute orders");
                }
                else
                    cout << "Going back to re-issue orders." << endl;
            }

            while (GM.getState().compare("execute orders") == 0)
            {
                cout << "Each player will now get a turn to execute orders" << endl;
                for (int i = 0; i < GM.getPlayers(); i++)
                {
                    GM.executeOrders();
                }
                cout << "Type \"endexecorders\" to proceed \"win\" to check win or \"execorder\" to restart" << endl;
                cin >> command;
                if (command.compare("endexecorders") == 0)
                {
                    GM.setState("assign reinforcement");
                }

                else if (command.compare("win")== 0)
                {

                    if (GM.getPlayers() == 1)
                    {
                        GM.setState("win");
                    }
                    else
                        cout << "You didnt win yet. Keep playing" << endl;
                        GM.setPlayers(1);
                }
                else
                    cout << "Going back to re-execute orders." << endl;
            }

            while (GM.getState().compare("win") == 0)
            {   cout << "CONGRATS" << endl;
                cout << " Would you like to play again?Type \"play\" for yes and \"end\" to exit" << endl;
                cin >> command;
                if (command.compare("play") == 0)
                {
                    GM.setTrans("startup");
                    GM.setState("start");
                }
                else if(command.compare("end") == 0)
                {
                    cout << "Thank you for playing warzone." << endl;
                    system("pause");
                    return 0;
                }
                else 
                    cout <<"Invalid response... JUST CHOOSE ONE"<< endl;
            }
        }
    
    }
    return 0;
}