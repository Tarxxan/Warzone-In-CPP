#include "GameEngine.h"
#include "CommandProcessor.h"
//#include "LoggingObserver.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Command::Command()
{
    command = "";
    effect = "";
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

void Command::saveEffect(string command)
{

    // Based on the command name have to do a series of checks in order to issue a proper effect

    // Used to notify the observer
    Notify(this);
}

string Command::stringToLog()
{
    ofstream gameLog;
    gameLog.open("gamelog.txt", "a");
    gameLog << "Effect of Command:" << this->effect << "\n"
            << endl;
    gameLog.close();
    return this->effect;
}

CommandProcessor::CommandProcessor() : this->CommandList = {};

CommandProcessor::CommandProcessor(CommandProcessor &commandProcessor)
{
    this->CommandList = commandProcessor.CommandList;
}

CommandProcessor::~CommandProcessor()
{

    for (Command c : CommandList)
    {
        delete c;
        c = NULL;
    }
}

ostream &operator<<(ostream &output, const CommandProcessor &commandProcessor)
{
    output << "Commands in the List" << endl;
    for (Command c : commandProcessor.CommandList)
    {
        output << *c << endl;
    }
    return output;
}

string CommandProcessor::stringToLog()
{
    ofstream gameLog;
    gameLog.open("gamelog.txt", "a");
    gameLog << "Commands: " << endl;
    string commandContents;
    for (Command c : CommandList)
    {
        commandContents += *c + "\t";
    }
    gameLog << commandContents;
    gameLog << endl;
    gameLog.close();
    return commandContents;
}
//Uses validate method to get commands and ensure they are correct given the gamestate
void CommandProcessor::getCommand(string gameState)
{
}

// Method that reads commmand for the console, can be overriden to read commands from a file
virtual string CommandProcessor::readCommand()
{
    string command;
    cout << "Enter a command" << endl;
    getline(cin, command);
    return command;
}

// Not Finished ----------------------------------
bool CommandProcessor::validate(string command, string gameState)
{
    return true;
}

// Method that saves command into a list of commands
void CommandProcessor::saveCommand(Command *c)
{
    this->CommandList.push_back(c);
    notify(this);
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

const FileLineReader &operator=(const FileLineReader &file)
{
    this->currentLine = file.currentLine;
    return *this;
}

// Want to check if theres a way to put a bit somewhere where we can just start from there instead of iterating over it a bunch of times 
string FileLineReader::ReadLine(string fileName)
{
    string command;
    int count=0;

    while(!file.eof()){
        if(count!=currentLine){
            getline(file,command);
            count++;
        } 
        getline(file,command);
        break;
    }
    currentLine++;
    file.close();
    return command;
}

friend ostream &operator<<(ostream &output, const FileLineReader &file)
{
    output << "Reading with linereader" << endl;
    return output;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string fileName) : CommandProcessor(), FileLineReader()
{
    this->fileName = fileName;
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
    string command = FileLineReader->readLineFromFile(fileName);
    return command;
}
