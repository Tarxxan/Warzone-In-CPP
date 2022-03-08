#include <string>
using namespace std;
#include <fstream>
#include <list>
//#include "LoggingObserver.h"

#pragma once

// Should inherit iloggable and subject
class Command
{
public:
    string command;
    string effect;

    Command();

    Command(string command);

    Command(const Command &command);

    ~Command();

    Command &operator=(const Command &command);

    void saveEffect(string effect);

    friend ostream &operator<<(ostream &out, const Command &command);

    virtual string stringToLog(); // From Iloggable class
};

// Should inherit iloggable and subject
class CommandProcessor
{
public:
    // list of commands IDK if we can use vectors so im just following picture format in A2 doc
    list<Command *> CommandList;

    CommandProcessor();

    CommandProcessor(CommandProcessor &commandProcessor);

    // Need to make it virtual since its base class
    virtual ~CommandProcessor();

    // Assignment operator
    const CommandProcessor &operator=(const CommandProcessor &commandProcessor);

    // Method to validate commands
    bool validate(string coammdn, string gameState);

    friend ostream &operator<<(ostream &out, const CommandProcessor &commandProcessor);

    virtual string stringToLog();

    void getCommand(string gameState);

    // Method that reads commmand for the console, can be overriden to read commands from a file
    virtual string readCommand();

    bool validate(string coammdn, string gameState);

    // Method that saves command into a list of commands
    void saveCommand(Command *c);
};

class FileLineReader
{
public:
    ifstream file;
    int currentLine;

    FileLineReader();

    FileLineReader(FileLineReader &file);

    ~FileLineReader();

    const FileLineReader &operator=(const FileLineReader &file);

    string ReadLine(string fileName);

    friend ostream &operator<<(ostream &out, const FileLineReader &file);
};

class FileCommandProcessorAdapter : public CommandProcessor
{
public:
    FileLineReader *fileLineReader;
    string fileName;

    FileCommandProcessorAdapter(string fileName);

    FileCommandProcessorAdapter(FileCommandProcessorAdapter &fileCommandAdapter);

    ~FileCommandProcessorAdapter();

    const FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &fileCommandAdapter);

    friend ostream &operator<<(ostream &out, const FileCommandProcessorAdapter &fileCommandAdapter);

    string readCommand();
};