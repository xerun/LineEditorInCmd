#ifndef COMMAND_H
#define COMMAND_H
#include <string>
class Command
{
private:
	std::string command_line; //stores supplied	command line	
	bool status; // stores validity of this command
	std::string symbol; // store the command symbol
	std::string address1; // stores address1
	std::string address2; // stores address2
public:
	Command(const std::string& command_line); // ctor, sets and parses command line
	void parse(const std::string& command_line); // resets and parse command line
	std::string getSymbol(); // retuns the command symbol
	std::string getAddress1(); // returns the address1
	std::string getAddress2(); // returns the address2
	bool getStatus(); // returns whether command line syntax is valid
	void setStatus(bool status); // sets status of this command
};
#endif