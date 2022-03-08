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

ostream &operator<<(ostream &out, const Command &command)
{
    out << "COMMAND: " << command.command << endl;
    out << "EFFECT: " << command.effect << endl;
    return out;
}

void Command::saveCommand(string command)
{

    // Used to notify the observer
    // Notify(this)
}

string Command::stringToLog()
{

    // Overwrites Iloggable String to log function
}