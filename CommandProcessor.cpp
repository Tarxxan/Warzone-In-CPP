#include "CommandProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
class ILoggable;
class Subject;

// Contains isValid to be used by GameEngine to determine if they should bother executing a command

/**
 * Command::Command
 * Default Constructor
 */
Command::Command()
{
    command = "";
    effect = "";
    isValid = true;
}
/**
 * Command::Command
 *
 * @param  {string} command : Command passed as string for tetsing
 */
Command::Command(string command)
{
    LogObserver *observer = new LogObserver(this);
    this->command = command;
    isValid = true;
}
/**
 * Command::~Command
 * Command Destructor
 */
Command::~Command()
{
}
/**
 * Command::Command
 * Copy Constructor
 * @param  {Command} command :
 */
Command::Command(const Command &command)
{
    this->command = command.command;
    this->effect = command.effect;
    this->isValid = command.isValid;
}
/**
 * Command
 * Assignment Operator assigns one copy to another
 * @param  {Command} command :
 * @return {Command}         :
 */
Command &Command::operator=(const Command &command)
{
    this->command = command.command;
    this->effect = command.effect;
    this->isValid = command.isValid;
    return *this;
}
/**
 *  Output Stream Operator
 * @param  {ostream} output  :
 * @param  {Command} command :
 * @return {ostream}         :
 */
ostream &operator<<(ostream &output, const Command &command)
{
    output << "COMMAND: " << command.command << endl;
    output << "EFFECT: " << command.effect << endl;
    return output;
}
/**
 * Command
 * Checks command aswell as whether it is a valid command and will return the appropriate string to be saved as an effect
 * @param  {string} command :
 * @param  {bool} isValid   :
 * @return {string}         :
 */
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

/**
 * Command
 * Saves the effect in the command as well as calling notify
 * @param  {string} effect :
 */
void Command::saveEffect(string effect)
{
    this->effect = effect;
    Notify(this);
}
/**
 * Command
 * StringToLog override
 * @return {string}  :
 */
string Command::stringToLog()
{
    return "Effect: " + this->effect;
}

/**
 * CommandProcessor::CommandProcessor
 * Default constructor for command processor
 */
CommandProcessor::CommandProcessor()
{
    gameRounds = 0;
    turnsPerGame = 0;
    LogObserver *observer = new LogObserver(this);
    isTournament = false;
}
/**
 * CommandProcessor::~CommandProcessor
 * CommandProcessor destrucotr calls destructors of all commands in its command list
 */
CommandProcessor::~CommandProcessor()
{
    for (Command *c : CommandList)
    {
        delete c;
        c = NULL;
    }
}
/**
 * CommandProcessor::CommandProcessor
 * Copy constructor
 * @param  {CommandProcessor} commandProcessor :
 */
CommandProcessor::CommandProcessor(CommandProcessor &commandProcessor)
{

    this->CommandList = commandProcessor.CommandList;
}

/**
 * CommandProcessor
 * Assignment Operator
 * @param  {CommandProcessor} commandProcessor :
 * @return {CommandProcessor}                  :
 */
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &commandProcessor)
{

    this->CommandList = commandProcessor.CommandList;
    return *this;
}
/**
 * Ouput Stream for Command Processor
 * @param  {ostream} output                    :
 * @param  {CommandProcessor} commandProcessor :
 * @return {ostream}                           :
 */
ostream &operator<<(ostream &output, const CommandProcessor &commandProcessor)
{
    output << "Commands in the List" << endl;
    for (Command *c : commandProcessor.CommandList)
    {
        output << *c << endl;
    }
    return output;
}
/**
 * CommandProcessor
 * String to log override
 * @return {string}  :
 */
string CommandProcessor::stringToLog()
{
    string commandstr = "Command: " + CommandList.back()->command;
    return commandstr;
}

/**
 * Command*CommandProcessor::getCommand
 *  calls read command and proceeds to validate it before returning said command
 * @param  {string} gameState :
 * @return {Command*}
 */
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
/**
 * Command*CommandProcessor::getCommand
 *  Using the gameengine objects returns a command after it is read and validated
 * @param  {GameEngine*} G :
 * @return {Command*}
 */
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
/**
 * Command*CommandProcessor::readCommand
 * Reads the command from the keyboard
 */
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
/**
 * CommandProcessor
 * Validates the command given the current gamestate
 * @param  {Command*} c       :
 * @param  {string} gameState :
 * @return {bool}             :
 */
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
/**
 * CommandProcessor ValidateTournament
 * Validates whether the command given as a tournament is a valid tournament command and parses
 * the data into the correct vectors
 * @param  {Command*} c :
 * @return {bool}       :
 */
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
    if (c->command.find("-P") != string::npos)
    {

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
    }
    else
    {
        return false;
    }
    cout << endl;

    // Validate whether the commands are good in here in terms of number and type
    for (auto i : playersStrat)
    {
        if (!validatePlayerStrat(i)|| playersStrat.size() >6 || playersStrat.size()==1)
        {
            return false;
        }
    }

    if (c->command.find("-G") != string::npos)
    {
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
    }
    else
    {
        return false;
    }

    if (c->command.find("-D") != string::npos)
    {
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
    }
    else
        return false;

    this->isTournament = true;

    return true;
}
/**
 * CommandProcessor validatePlayerStrat
 * Checks whether the given strategy is valid in the tournament(Human is valid but should not be used)
 * @param  {string} strategy :
 * @return {bool}            :
 */
bool CommandProcessor::validatePlayerStrat(string strategy)
{
    return (strategy == "Neutral" || strategy == "Benevolent" || strategy == "Aggressive" || strategy == "Human" || strategy == "Cheater");
}
/**
 * CommandProcessor  S
 * Saves Command into the command list and then notifies Observers
 * @param  {Command*} c :
 */
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
/**
 * FileLineReader::FileLineReader
 *  Default constructor
 */
FileLineReader::FileLineReader()
{
    currentLine = 0;
}
/**
 * FileLineReader::~FileLineReader
 * Destructor for FileLineReader
 */
FileLineReader::~FileLineReader() {}

/**
 * FileLineReader::FileLineReader
 *  Copy Constructor
 * @param  {FileLineReader} file :
 */
FileLineReader::FileLineReader(FileLineReader &file)
{
    this->currentLine = file.currentLine;
}
/**
 * FileLineReader Assignment Operator
 *  Assigns the value of one object to another
 * @param  {FileLineReader} file :
 * @return {FileLineReader}      :
 */
const FileLineReader &FileLineReader::operator=(const FileLineReader &file)
{
    this->currentLine = file.currentLine;
    return *this;
}
/**
 * FileLineReader ReadLine
 * Responsible for reading the lines of a file and parsing them as commands
 * @param  {string} fileName :
 * @return {string}          :
 */
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
/**
 *  Output Stream Operator
 * @param  {ostream} output      :
 * @param  {FileLineReader} file :
 * @return {ostream}             :
 */
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

/**
 * Derived class of CommandProcessor, Default constructor
 * @return {FileCommandProcessorAdapter::FileCommandProcessorAdapter(string}  :
 */
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string fileName) : CommandProcessor()
{
    this->fileName = fileName;
    fileLineReader = new FileLineReader;
}
/**
 * FileCommandProcessorAdapter::~FileCommandProcessorAdapter
 * Destructor for FileCommandProcesssor
 */
FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete fileLineReader;
    fileLineReader = NULL;
}
/**
 * FileCommandProcessorAdapter Assignment Operator
 * Assigns the value of one object to another
 * @param  {FileCommandProcessorAdapter} FileCommandProcessorAdapter :
 * @return {FileCommandProcessorAdapter}                             :
 */
const FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &FileCommandProcessorAdapter)
{
    this->fileName = FileCommandProcessorAdapter.fileName;
    this->fileLineReader = new FileLineReader;
    return *this;
}
/**
 * Output Stream Operator
 * @param  {ostream} output                                          :
 * @param  {FileCommandProcessorAdapter} FileCommandProcessorAdapter :
 * @return {ostream}                                                 :
 */
ostream &operator<<(ostream &output, const FileCommandProcessorAdapter &FileCommandProcessorAdapter)
{
    output << "Reading from File:" << endl;
    return output;
}
/**
 * Command*FileCommandProcessorAdapter::readCommand
 * Reads a command using the file reader and then saves the command
 */
Command *FileCommandProcessorAdapter::readCommand()
{
    string command = fileLineReader->ReadLine(fileName);
    Command *c = new Command(command);
    saveCommand(c);
    return c;
}
