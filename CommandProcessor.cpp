//#include "GameEngine.h"
#include "CommandProcessor.h"
#include "LoggingObserver.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class ILoggable;
class Subject;

Command::Command()
{
    command = "";
    effect = "";
}

Command::~Command()
{
}
Command::Command(string command)
{
    this->command = command;
}

Command::Command(const Command &command)
{
    this->command = command.command;
    this->effect = command.effect;
}

Command &Command::operator=(const Command &command)
{
    this->command = command.command;
    this->effect = command.effect;
    return *this;
}

ostream &operator<<(ostream &output, const Command &command)
{
    output << "COMMAND: " << command.command << endl;
    output << "EFFECT: " << command.effect << endl;
    return output;
}

string Command::checkCommand(string command)
{
    string effect = "";
    if (command.compare("quit") == 0)
        return effect = "The game has ended, No new games will be played";
    else if (command.compare("replay") == 0)
        return effect = " A new game of Warzone will follow.";
    else if (command.compare("gamestart") == 0)
        return effect = "Game has been initializaed. It will now begin";
    else if (command.find("loadmap") != string::npos)
        return effect = command.substr(8) + " has been loaded";
    else if (command.find("validatemap") != string::npos)
        return effect = "The map has been validated";
    else if (command.find("addplayer") != string::npos)
        return effect = command.substr(10) + " has been added to the game";
    else if (command.compare("gamestart") == 0)
        return effect = "Players have been added and the game will now begin";
    else
        return effect = "invalid Command, no effect will occur.";
}

void Command::saveEffect(string command)
{
    effect = checkCommand(command);
    Notify(this);
}
// call detatch in destructors in observer to ensure you arent notifying a deleted object
string Command::stringToLog()
{
    ofstream gameLog;
    gameLog.open("gamelog.txt", ios_base::app);
    gameLog << "Effect of Command:" << this->effect << "\n"<< endl;
    gameLog.close();
    return this->effect;
}

CommandProcessor::CommandProcessor() {}

CommandProcessor::CommandProcessor(CommandProcessor &commandProcessor)
{
    this->CommandList = commandProcessor.CommandList;
}

CommandProcessor::~CommandProcessor()
{

    for (Command *c : CommandList)
    {
        delete c;
        c = NULL;
    }
}

ostream &operator<<(ostream &output, const CommandProcessor &commandProcessor)
{
    output << "Commands in the List"<< endl;
    for (Command *c : commandProcessor.CommandList)
    {
        output << *c << endl;
    }
    return output;
}

string CommandProcessor::stringToLog()
{
    ofstream gameLog;
    gameLog.open("gamelog.txt", ios_base::app);
    gameLog << "Commands: " << endl;
    string commandContents;
    for (Command *c : this->CommandList)
    {

        commandContents += c->command + "\t";
    }
    cout << commandContents;
    gameLog << commandContents;
    gameLog << endl;
    gameLog.close();
    return commandContents;
}
// Uses validate method to get commands and ensure they are correct given the gamestate
void CommandProcessor::getCommand(string gameState)
{
    string currCommand = readCommand();
    if (validate(currCommand, gameState))
    {
        Command *c = new Command(currCommand);
        LogObserver *observer = new LogObserver(c);
        c->saveEffect(currCommand);
        saveCommand(c);
       
    }

    else
    {
        Command *c = new Command(currCommand);
        LogObserver *observer = new LogObserver(c);
        c->saveEffect(currCommand);
        saveCommand(c);
        cerr << "An invalid command has been given for current state." << endl;
    }
}

// Method that reads commmand for the console, can be overriden to read commands from a file

string CommandProcessor::readCommand()
{
    string command;
    cout << "Enter a command" << endl;
    getline(cin, command);
    return command;
}

bool CommandProcessor::validate(string command, string gameState)
{
    if (command.find("loadmap") != string::npos && (gameState == "start" || gameState == "maploaded"))
    {
        return true;
    }

    else if (command == "validatemap" && gameState == "maploaded")
        return true;

    else if (command.find("addplayer") !=string::npos && (gameState == "mapvalidated" || gameState == "playersadded"))
        return true;

    else if (command == "gamestart" && gameState == "playersadded")
        return true;

    else if ((command == "replay" || command == "quit") && gameState == "win")
        return true;

    return false;
}

// Method that saves command into a list of commands
void CommandProcessor::saveCommand(Command *c)
{
    this->CommandList.push_back(c);
    Notify(this);
}

FileLineReader::FileLineReader()
{
    currentLine = 0;
}

FileLineReader::FileLineReader(FileLineReader &file)
{
    this->currentLine = file.currentLine;
}

FileLineReader::~FileLineReader() {}

const FileLineReader &FileLineReader::operator=(const FileLineReader &file)
{
    this->currentLine = file.currentLine;
    return *this;
}

// Want to check if theres a way to put a bit somewhere where we can just start from there instead of iterating over it a bunch of times
string FileLineReader::ReadLine(string fileName)
{
    string command;
    file.open(fileName);
    for(int count=0;count<=currentLine;){
        if (count != currentLine)
        {
            getline(file, command);
            count++;
        }
        else
        {
            getline(file, command);
            cout << command<<endl;
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

string FileCommandProcessorAdapter::readCommand()
{
    string command = fileLineReader->ReadLine(fileName);
    return command;
}
