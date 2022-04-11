#include "CommandProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
class ILoggable;
class Subject;

// Contains isValid to be used by GameEngine to determine if they should bother executing a command
Command::Command()
{
    command = "";
    effect = "";
    isValid = true;
    
}

Command::Command(string command)
{
    LogObserver *observer = new LogObserver(this);
    this->command = command;
    isValid = true;
}

Command::~Command()
{
}

Command::Command(const Command &command)
{
    this->command = command.command;
    this->effect = command.effect;
    this->isValid = command.isValid;
}

Command &Command::operator=(const Command &command)
{
    this->command = command.command;
    this->effect = command.effect;
    this->isValid = command.isValid;
    return *this;
}

ostream &operator<<(ostream &output, const Command &command)
{
    output << "COMMAND: " << command.command << endl;
    output << "EFFECT: " << command.effect << endl;
    return output;
}

string Command::checkCommand(string command, bool isValid)
{
    string effect = "";
    if (!isValid)
        return effect = "invalid Command, no effect will occur.";
    if (command.find("tournament") != string::npos && command.length() > 8)
        return "The tournament will now begin";
    else if (command.compare("quit") == 0)
        return effect = "The game has ended, No new games will be played";
    else if (command.compare("replay") == 0)
        return effect = " A new game of Warzone will follow.";
    else if (command.compare("gamestart") == 0)
        return effect = "Game has been initializaed. It will now begin";
    else if (command.find("loadmap") != string::npos && command.length() > 8)
        return effect = command.substr(8) + " has been loaded";
    else if (command.find("validatemap") != string::npos)
        return effect = "The map has been validated";
    else if (command.find("addplayer") != string::npos && command.length() > 10)
        return effect = command.substr(10) + " has been added to the game";
    else if (command.compare("gamestart") == 0)
        return effect = "Players have been added and the game will now begin";
    else
        return effect = "invalid Command, no effect will occur.";
}

void Command::saveEffect(string effect)
{
    this->effect = effect;
    Notify(this);
}

string Command::stringToLog()
{
    return "Effect: " + this->effect;
}

CommandProcessor::CommandProcessor()
{
    gameRounds = 0;
    turnsPerGame = 0;
    LogObserver *observer = new LogObserver(this);
    isTournament = false;
}

CommandProcessor::~CommandProcessor()
{
    for (Command *c : CommandList)
    {
        delete c;
        c = NULL;
    }
}

CommandProcessor::CommandProcessor(CommandProcessor &commandProcessor)
{

    this->CommandList = commandProcessor.CommandList;
}

CommandProcessor &CommandProcessor::operator=(const CommandProcessor &commandProcessor)
{

    this->CommandList = commandProcessor.CommandList;
    return *this;
}
ostream &operator<<(ostream &output, const CommandProcessor &commandProcessor)
{
    output << "Commands in the List" << endl;
    for (Command *c : commandProcessor.CommandList)
    {
        output << *c << endl;
    }
    return output;
}

string CommandProcessor::stringToLog()
{
    string commandstr = "Command: " + CommandList.back()->command;
    return commandstr;
}

// With help from readCommand() creates a command which will be passed to the validate to ensure its validity given the gamestate.
// This can be used by GameEngine.
Command *CommandProcessor::getCommand(string gameState)
{
    Command *c = readCommand();
    if (validate(c, gameState))
    {
        c->saveEffect(c->checkCommand(c->command, c->isValid));
        return c;
    }

    else
    {
        c->isValid = false;
        c->saveEffect(c->checkCommand(c->command, c->isValid));
        cerr << "An invalid command has been given for current state." << endl;
        return c;
    }
}

Command *CommandProcessor::getCommand(GameEngine *G)
{
    Command *c = readCommand();
    if (validate(c, G->getState()))
    {
        c->saveEffect(c->checkCommand(c->command, c->isValid));
        return c;
    }

    else
    {
        c->isValid = false;
        c->saveEffect(c->checkCommand(c->command, c->isValid));
        cerr << "An invalid command has been given for current state." << endl;
        return c;
    }
}

// Method that reads commmand for the console, can be overriden to read commands from a file in FileCommandProcessorAdapter
Command *CommandProcessor::readCommand()
{
    string command;
    cout << "Enter a command" << endl;
    getline(cin, command);
    cout << endl;
    Command *c = new Command(command);
    saveCommand(c);
    return c;
}

// Validates the Command given the current Gamestate
bool CommandProcessor::validate(Command *c, string gameState)
{

    if (c->command.find("loadmap") != string::npos && (gameState == "start" || gameState == "maploaded") && c->command.length() > 8)
    {
        return true;
    }
    else if (c->command.find("tournament") != string::npos && (gameState == "start"))
    {
        return validateTournament(c);
    }

    else if (c->command == "validatemap" && gameState == "maploaded")
        return true;

    else if (c->command.find("addplayer") != string::npos && (gameState == "mapvalidated" || gameState == "playersadded") && c->command.length() > 10)
        return true;

    else if (c->command == "gamestart" && gameState == "playersadded")
        return true;

    else if ((c->command == "replay" || c->command == "quit") && gameState == "win")
        return true;

    return false;
}

bool CommandProcessor::validateTournament(Command *c)
{
    int mapStart = c->command.find("-M ") + 3;
    int mapEnd = c->command.substr(mapStart).find(" ");
    string mapFiles = c->command.substr(mapStart, mapEnd);

    while (mapFiles.find(",") != string::npos)
    {
        int delim = mapFiles.find(",");
        string mapName = mapFiles.substr(0, delim);
        mapFilesList.push_back(mapName);
        mapFiles = mapFiles.substr(delim + 1);
    }
    mapFilesList.push_back(mapFiles);

    int playerStart = c->command.find("-P ") + 3;
    int playerEnd = c->command.substr(playerStart).find(" ");
    string playerTypes = c->command.substr(playerStart, playerEnd);
    while (playerTypes.find(",") != string::npos)
    {
        int delim = playerTypes.find(",");
        string playerTypeName = playerTypes.substr(0, delim);
        playersStrat.push_back(playerTypeName);
        playerTypes = playerTypes.substr(delim + 1);
    }
    playersStrat.push_back(playerTypes);
    cout << endl;

    // Validate whether the commands are good in here in terms of number and type
    for (auto i : playersStrat)
    {
        if (!validatePlayerStrat(i))
        {
            return false;
        }
    }

    int gameStart = c->command.find("-G ") + 3;
    int gameEnd = c->command.substr(gameStart).find(" ");
    this->gameRounds = stoi(c->command.substr(gameStart, gameEnd));

    if (gameRounds < 1 || gameRounds > 5)
    {
        cout << "Invalid amount of gameRounds" << endl;
        cout << "Invalid tournament command. Exits the program. Bye!" << endl;
        system("pause");
        exit(0);
        return false;
    }

    int turnsStart = c->command.find("-D ") + 3;
    int turnsEnd = c->command.substr(turnsStart).find(" ");

    this->turnsPerGame = stoi(c->command.substr(turnsStart, turnsEnd));
    if (turnsPerGame < 10 || turnsPerGame > 50)
    {
        cout << "Invalid amount of Turns" << endl;
        cout << "Invalid tournament command. Exits the program. Bye!" << endl;
        system("pause");
        exit(0);
        return false;
    }


    this->isTournament = true;


    return true;
}

bool CommandProcessor::validatePlayerStrat(string strategy)
{
    return (strategy == "Neutral" || strategy == "Benevolent" || strategy == "Aggressive" || strategy == "Human" || strategy == "Cheater");
}
// Saves Command and then notifies Observers
void CommandProcessor::saveCommand(Command *c)
{

    this->CommandList.push_back(c);
    Notify(this);
}
/*
  ///////////////////////////////////////////////////////
 //                 FILE LINE READER                  //
///////////////////////////////////////////////////////
*/
FileLineReader::FileLineReader()
{
    currentLine = 0;
}

FileLineReader::~FileLineReader() {}

FileLineReader::FileLineReader(FileLineReader &file)
{
    this->currentLine = file.currentLine;
}

const FileLineReader &FileLineReader::operator=(const FileLineReader &file)
{
    this->currentLine = file.currentLine;
    return *this;
}

string FileLineReader::ReadLine(string fileName)
{
    string command;
    file.open(fileName);
    for (int count = 0; count <= currentLine;)
    {
        if (count != currentLine)
        {
            getline(file, command);
            count++;
        }
        else
        {
            getline(file, command);
            currentLine++;
            break;
        }
    }
    file.close();
    return command;
}

ostream &operator<<(ostream &output, const FileLineReader &file)
{
    output << "Reading with linereader" << endl;
    return output;
}

/*
  ///////////////////////////////////////////////////////
 //       FILE COMMMAND PROCESSOR ADAPTER             //
///////////////////////////////////////////////////////
*/

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string fileName) : CommandProcessor()
{
    this->fileName = fileName;
    fileLineReader = new FileLineReader;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete fileLineReader;
    fileLineReader = NULL;
}

const FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &FileCommandProcessorAdapter)
{
    this->fileName = FileCommandProcessorAdapter.fileName;
    this->fileLineReader = new FileLineReader;
    return *this;
}

ostream &operator<<(ostream &output, const FileCommandProcessorAdapter &FileCommandProcessorAdapter)
{
    output << "Reading from File:" << endl;
    return output;
}

Command *FileCommandProcessorAdapter::readCommand()
{
    string command = fileLineReader->ReadLine(fileName);
    Command *c = new Command(command);
    saveCommand(c);
    return c;
}
