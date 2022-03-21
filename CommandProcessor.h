#pragma once
#include <string>
#include <fstream>
#include <list>
#include "LoggingObserver.h"


using namespace std;

class ILoggable;
class Subject;

class Command : public ILoggable, public Subject
{
public:
    string command;
    string effect;
    bool isValid;

    Command();

    Command(string command);

    Command(const Command &command);

    ~Command();

    Command &operator=(const Command &command);

    void saveEffect(string effect);

    string checkCommand(string command, bool isValid);

    friend ostream &operator<<(ostream &output, const Command &command);

    virtual string stringToLog(); // From Iloggable class
};

// Should inherit iloggable and subject
class CommandProcessor : public ILoggable, public Subject
{
public:
    // list of commands IDK if we can use vectors so im just following picture format in A2 doc
    list<Command *> CommandList;

    CommandProcessor();

    CommandProcessor(CommandProcessor &commandProcessor);

    // Need to make it virtual since its base class
    // Delete all pointers in the list
    virtual ~CommandProcessor();

    // Assignment operator
    const CommandProcessor &operator=(const CommandProcessor &commandProcessor);

    friend ostream &operator<<(ostream &output, const CommandProcessor &commandProcessor);

    virtual string stringToLog();

    Command* getCommand(string gameState);

    // Method that reads commmand for the console, can be overriden to read commands from a file

    bool validate(Command *c, string gameState);
    // Method that saves command into a list of commands
    void saveCommand(Command *c);

private:
    virtual Command* readCommand();
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

    friend ostream &operator<<(ostream &output, const FileLineReader &file);
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

    friend ostream &operator<<(ostream &output, const FileCommandProcessorAdapter &fileCommandAdapter);

    Command* readCommand();
};