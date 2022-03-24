//#include "GameEngine.h"
#include "CommandProcessor.h"
#include <iostream>
#include <fstream>
#include <string>

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

void Command::saveEffect(string effect)
{
    this->effect = effect;
    Notify(this);
}

string Command::stringToLog()
{
    return "Effect: " + this->effect + "\n";
}

CommandProcessor::CommandProcessor()
{
    LogObserver *observer = new LogObserver(this);
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

// Method that reads commmand for the console, can be overriden to read commands from a file in FileCommandProcessorAdapter
Command *CommandProcessor::readCommand()
{
    cin.clear();
    cin.ignore(10000, '\n');
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
    if (c->command.find("loadmap") != string::npos && (gameState == "start" || gameState == "maploaded"))
    {
        return true;
    }

    else if (c->command == "validatemap" && gameState == "maploaded")
        return true;

    else if (c->command.find("addplayer") != string::npos && (gameState == "mapvalidated" || gameState == "playersadded"))
        return true;

    else if (c->command == "gamestart" && gameState == "playersadded")
        return true;

    else if ((c->command == "replay" || c->command == "quit") && gameState == "win")
        return true;

    return false;
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
