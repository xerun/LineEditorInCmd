#include "Command.h"
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

/**
* Command constructor
* @param command_line A variable of type String.
*/
Command::Command(const std::string& command_line)
{
	status = false; // set the status as faluse by default
	parse(command_line); // call the parse method with command_line parameter
}

/**
* Parse and validate the command given and set the values of
* symbol, address1, address2 and status
* @param command_line A variable of type String.
*/
void Command::parse(const std::string& command_line)
{
	string cmd = command_line;
	status = true;
	bool validCmd = false;
	char cmdarr[] = { 'p', 'i', 'a' , 'c' , 'g' , 'x' , 'v' , 'u' , 'n' , 'd' , 'j' , 'w' , 'q' ,'\0' };
	// create a character array with set valid inputs and give \0 at the end of the character to define the end

	for (unsigned int i = 0; i < strlen(cmdarr); ++i)
	{// loop through the character array
		if (cmd.front() == cmdarr[i])
		{// if the first letter of the command matches any of the character from cmdarr
			// then make the validCmd true
			validCmd = true;
		}
	}
	if (cmd.find(',') != std::string::npos && !validCmd) // checks if the sting contains comma
	{
		string begin = cmd.substr(0, cmd.find(',')); // get values before space
		string end = cmd.substr(cmd.find(',') + 1); // get values after space
		
		if (!validCmd && (isalpha(cmd.front())))
		{// if the command is not valid and first letter character is alphabet
			// show error message to user and set start variable to false
			cout << "Bad command: " << cmd.front() << endl;
			status = false;
		}
		else if (begin.length() >= 1 && (begin.find_first_not_of("0123456789") != string::npos) && begin.front() != '$')
		{// if length of begin variable is greater than or equal to 1 and it is not a number and not starting with $
			// show error message to user and set start variable to false
			if ((begin.front()!='-' && !isdigit(begin.at(1))))
			{
				cout << "Bad address 1: " << begin << endl;
				status = false;
			}			
		}
		else if ((begin.find_first_not_of("0123456789") != string::npos) && begin.front() != '$' && begin.length() == 1)
		{// if begin variable is not number and not starting with $ and lenght 1
			// show error message to user and set start variable to false
			if (begin.front() != '.')
			{
				cout << "Bad address 1: " << begin.front() << endl;
				status = false;
			}
		}
		else if ((end.find_first_not_of("0123456789") != string::npos) && end.back() != '$')
		{// if end variable is not number and not ending with $
			// show error message to user and set start variable to false
			if ((end.front() != '-' && !isdigit(end.at(1))))
			{
				cout << "Bad address 2: " << end << endl;
				status = false;
			}			
		}
	}
	else
	{
		if (!validCmd && (isalpha(cmd.front())))
		{// if the command is not valid and first letter is alphabet
			// show error message to user and set start variable to false
			cout << "Bad command: " << cmd.front() << endl;
			status = false;
		}
		else if ((cmd.find_first_not_of("0123456789") != string::npos) && (cmd.front() != '.' && cmd.front() != '$') && !validCmd)
		{// if the command is not a number and starting with . or $ and not a valid command
			// show error message to user and set start variable to false
			cout << "Bad address 1: " << cmd << endl;
			status = false;
		}
	}

	if (status) 
	{
		status = false;
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower); // convert the input to lower case
		replace(cmd.begin(), cmd.end(), ',', ' '); // replace the comma with space
		
		if (cmd.find(' ') != std::string::npos) // checks if the sting contains comma
		{
			string first = cmd.substr(0, cmd.find(' ')); // get values before space
			string last = cmd.substr(cmd.find(' ') + 1); // get values after space
			if (first.find('$') != std::string::npos)
			{
				replace(first.begin(), first.end(), '$', '1'); // replace $ symbol with 1 to flip the command
				if (last != "")
				{
					last = "$";
				}
				cmd = first + " " + last;
			}
			if ((first.front() == '-' && isdigit(first.at(1))))
			{
				cmd = "p1 $";
			}
			if ((last.front() == '-' && isdigit(last.at(1))))
			{
				cmd = "p1 $";
			}
		}

		std::string temp;

		for (unsigned int i = 0; i < cmd.size(); i++)
		{
			//iterate the string to find the first "number" character
			//if found create another loop to extract it
			//and then break the current one
			//thus extracting the FIRST encountered numeric block
			if (isdigit(cmd[i]))
			{
				for (unsigned int a = i; a < cmd.size(); a++)
				{
					temp += cmd[a];
				}
				//the first numeric block is extracted
				break;
			}
		}
		string num1;
		string num2;
		std::istringstream stream(temp);
		stream >> num1; // get the first int value before space
		stream >> num2; // get the second int value after space

		if (cmd.empty())
		{// if the command is empty then set command as print by default
			status = true;
			symbol = "p";
			address1 = ".";
			address2 = address1;
		}
		else
		{
			if (cmd.front() == 'p' && cmd.length() == 1)
			{// if only p value is passed then set the value as print
				status = true;
				symbol = "p";
				address1 = ".";
				address2 = address1;
			}
			else if (isalpha(cmd.front()) && cmd.back() != '$')
			{// check if the command is an alphabet and the last character is $ symbol
				status = true;
				symbol = cmd.front();	// set symbol as the first letter of command		
				if (num1.empty()) // if num1 is empty them make address1 and address2 as 1 by default
				{
					address1 = "1";
					address2 = address1;
				}
				else if (num2.empty()) // if num1 is not empty and num2 is empty then make address2 same as address1
				{
					address1 = num1;
					address2 = num1;
				}
			}
			else if (isdigit(cmd.front()) && cmd.back() != '$')
			{// if the fist letter of command is a number and last letter is not $ then make command as print
				status = true;
				symbol = "p";
				address1 = num1;
				if (!num2.empty()) // if the num2 is not empty then assign num2 to address2
					address2 = num2;
				else // otherwise make address2 same as address1
					address2 = address1;
			}
			else if ((cmd.front() == '.' || cmd.front() == '$') && cmd.length() == 1)
			{// if the first letter is . or $ and length of command is 1 then make default command as print
				status = true;
				symbol = "p";
				address1 = ".";
				address2 = address1;
			}
			else if ((cmd.front() == '$' || cmd.back() == '$') && cmd.length() >= 3)
			{ // if the command start or end with letter $ and the start or end letter is a digit and command is length of minimum 3
				status = true;
				symbol = "p";
				if (cmd.back() == '$' && isalpha(cmd.front()))
				{// if the last letter is $ and first letter is alphabet then set command
					symbol = cmd.front();
				}
				address1 = "1";
				address2 = "999"; // the value 999 in address2 is implies goes to the last line of the buffer
			}
			else if (cmd.front() == ' ')
			{// if the command has , at first then it is replaced as space
				//if the first letter is space then set status true
				status = true;
			}

			if (status)
			{
				if (cmd.find(' ') != std::string::npos)
				{// checks if the sting contains comma
					if (cmd.front() == ' ')
					{// checks if string contains comma at the beginning
						symbol = "p";
						address1 = "1";
						if (cmd.length() >= 2 && isdigit(cmd.at(1)))
						{// checks the 2nd character after comma
							address2 = num1;
						}
						else
						{
							address2 = address1;
						}
					}
					else if (cmd.length() >= 2 && cmd.at(1) == ' ')
					{// check if 2nd charter is comma
						if (num2.empty()) {
							address1 = "1";
							address2 = num1;
						}
					}
					else if (cmd.length() >= 2 && !num1.empty())
					{// if 2nd character is a digit
						address1 = num1;
						if (num2.empty())
						{// if the num2 value is empty then address2 is set same as address1
							address2 = address1;
						}
						else if (address2.empty())
						{// if address2 is empty then set address2 as num2
							address2 = num2;
						}
					}
					else if (cmd.back() == ' ')
					{// if the last value is , is replaced by space at the beginning
						// the command implies no address2 is defined so address2 will be same as address1
						address2 = num1;
					}
				}
			}
		}
	}
}

/**
* Return the symbol
* @param 
*/
std::string Command::getSymbol()
{
	return symbol;
}

/**
* Return the address1
* @param
*/
std::string Command::getAddress1()
{
	return address1;
}

/**
* Return the address2
* @param
*/
std::string Command::getAddress2()
{
	return address2;
}

/**
* Return the status
* @param
*/
bool Command::getStatus()
{
	return status;
}

/**
* Set the status
* @param status A variable of type Boolean.
*/
void Command::setStatus(bool status)
{
	this->status = status;
}