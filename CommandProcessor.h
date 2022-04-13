#pragma once
#include <string>
#include <fstream>
#include <list>
#include "LoggingObserver.h"
#include "GameEngine.h"

using namespace std;

class ILoggable;
class Subject;
class GameEngine;

class Command : public ILoggable, public Subject
{
public:
    string command;
    string effect;
    bool isValid;

    // Default Construcot
    Command();
    // Param Constructor
    Command(string command);
    // Destrucot
    ~Command();
    // Copy Constructor
    Command(const Command &command);
    // Assignment Operator
    Command &operator=(const Command &command);
    // Saves effect into command
    void saveEffect(string effect);
    // Checks whether command is valid and then returns approrpiate message
    string checkCommand(string command, bool isValid);
    // stream operator
    friend ostream &operator<<(ostream &output, const Command &command);
    // String to log override
    virtual string stringToLog(); // From Iloggable class
};

// Should inherit iloggable and subject
class CommandProcessor : public ILoggable, public Subject
{
public:
    // list of commands IDK if we can use vectors so im just following picture format in A2 doc
    list<Command *> CommandList;
    vector<string> mapFilesList;
    vector<string> playersStrat;
    int gameRounds;
    int turnsPerGame;
    bool isTournament;

    CommandProcessor();
    // Need to make it virtual since its base class
    // Delete all pointers in the list
    virtual ~CommandProcessor();

    // Copy constructor
    CommandProcessor(CommandProcessor &commandProcessor);

    // Assignment Operator
    CommandProcessor &operator=(const CommandProcessor &commandProcessor);
    // Stream Insertion Operator
    friend ostream &operator<<(ostream &output, const CommandProcessor &commandProcessor);
    // StringToLog Override
    virtual string stringToLog();
    // gets command from game engine
    Command *getCommand(GameEngine *G);
    // command used for testing get command uses string
    Command *getCommand(string gameState);

    // Validates whether the command is valid given the game state
    bool validate(Command *c, string gameState);
    // Method that saves command into a list of commands
    // wheter the tournament mode paramaters given are valid
    bool validateTournament(Command *c);
    // Strategy validate for tornament Helper
    bool validatePlayerStrat(string strat);

protected:
    // Saves command in command list
    void saveCommand(Command *c);
    // Reads command from console
    virtual Command *readCommand();
};

class FileLineReader
{
public:
    ifstream file;
    int currentLine;
    // Constructor
    FileLineReader();
    // Destructor
    ~FileLineReader();
    // Copy Constructor
    FileLineReader(FileLineReader &file);
    // Assignment Operator
    const FileLineReader &operator=(const FileLineReader &file);
    // Reads line from file for commands( Helper function)
    string ReadLine(string fileName);
    // Output stream
    friend ostream &operator<<(ostream &output, const FileLineReader &file);
};

class FileCommandProcessorAdapter : public CommandProcessor
{
public:
    FileLineReader *fileLineReader;
    string fileName;
    // Derived class of Command Processor Constructor
    FileCommandProcessorAdapter(string fileName);
    // Copy Constructor
    FileCommandProcessorAdapter(FileCommandProcessorAdapter &fileCommandAdapter);
    // Destructor
    ~FileCommandProcessorAdapter();
    // Assignment Operator
    const FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &fileCommandAdapter);
    // Output Stream opeator
    friend ostream &operator<<(ostream &output, const FileCommandProcessorAdapter &fileCommandAdapter);
    // Read command but from a file instead of console
    Command *readCommand();
};