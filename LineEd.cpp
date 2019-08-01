#include "LineEd.h"
#include "Command.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

/**
 * LineEd constructor
 *
 * It opens the file for reading, if the file variable is empty or file not exists
 * then promote user to input a new filename or accept empty filename and continue code
 *
 * @param filename A variable of type String.
 */
LineEd::LineEd(const std::string& filename)
{
	// Open the File
	fstream file(filename, ios::in | ios::app);
	// using ios::trunc will tell the program to overwrite the existing file

	// Check if object is valid
	if (file)
	{
		fileName = filename;
		cout << "" << fileName << endl;
		std::string str;
		// Read the next line from File untill it reaches the end.
		while (getline(file, str))
		{
			// Line contains string of length > 0 then save it in vector
			if (str.size() > 0)
				buffer.push_back(str);
		}
		cout << "\"" << filename << "\" " << buffer.size() << " lines" << endl;
		cout << "Entering command mode..." << endl;
		saved = true;
	}
	else
	{
		file.close(); // close the previous fstream before opening a new file
		cout << "";
		getline(cin, fileName);

		fstream file(fileName, ios::in | ios::app);

		// Check if object is valid
		if (file)
		{
			std::string str;
			// Read the next line from File untill it reaches the end.
			while (getline(file, str))
			{
				// Line contains string of length > 0 then save it in vector
				if (str.size() > 0)
					buffer.push_back(str);
			}
			
			saved = true;
		}

		if (saved == true)
		{
			cout << "\"" << fileName << "\" " << buffer.size() << " lines" << endl;
			cout << "Entering command mode..." << endl;
		}
		else if (saved == false && fileName!="")
		{// if new file and name is given
			cout << "\"" << fileName << "\" [New File]" << endl;
			cout << "Entering command mode..." << endl;
		}
		else 
		{// if new file and no name given
			cout << "\"?\" [New File]" << endl;
			cout << "Entering command mode..." << endl;
		}
	}
	
	//Close The File
	file.close();
	currentLine = buffer.size();
}


/**
 * Run function
 *
 * This is a recursive function which takes the command from the user,
 * create instance of Command class and get the symbol, address1, address2 and status from Command class
 * if the command is valid then call the execute function in it
 *
 */
void LineEd::run()
{	
	string line;	
	cout << "? ";
	cin.clear();
	cin >> skipws; // remove any white space at the beginning of the input
	getline(cin, line); // get the input from user including any space

	Command* cmd = new Command(line); //create instance of command class
	bool validStatus = cmd->getStatus(); // copy status from command class to validStatus variable
	if (validStatus) // check if the command is valid
	{
		string symbol = cmd->getSymbol(); //copy symbol from command class to symbol variable
		string address1 = cmd->getAddress1(); //copy address1 from command class to address1 variable
		string address2 = cmd->getAddress2(); //copy address2 from command class to address2 variable
		long line1;
		long line2;
		if (address1 == ".")
		{// if the address1 is . then it will point to the current pointed line in the buffer
			line1 = currentLine;
			line2 = currentLine;
		}
		else
		{// other wise convert the number in address string to number and store in line1 and line2
			line1 = stol(address1);
			line2 = stol(address2);
		}
		execute(symbol, line1, line2);	// call the execute function
	}
	run(); // recall the function for another input from the user
}

/**
 * RunCommand function
 *
 * This function takes the command from the user as parameter,
 * if the command is valid then 
 * create instance of Command class and get the symbol, address1, address2 and status from Command class
 * then call the execute function in it
 *
 * @param command A variable of type String.
 *
 */
void LineEd::runCommand(const std::string& command)
{
	Command* cmd = new Command(command); //create instance of command class
	bool validStatus = cmd->getStatus(); // copy status from command class to validStatus variable
	if (validStatus) // check if the command is valid
	{
		string symbol = cmd->getSymbol(); //copy symbol from command class to symbol variable
		string address1 = cmd->getAddress1(); //copy address1 from command class to address1 variable
		string address2 = cmd->getAddress2(); //copy address2 from command class to address2 variable
		long line1;
		long line2;
		if (address1 == ".")
		{// if the address1 is . then it will point to the current pointed line in the buffer
			line1 = currentLine;
			line2 = currentLine;
		}
		else
		{// other wise convert the number in address string to number and store in line1 and line2
			line1 = stol(address1);
			line2 = stol(address2);
		}
		execute(symbol, line1, line2);	// call the execute function
	}
}

/**
 * Call function according to the command
 *
 * Check the symbol variable and call the desired function
 *
 * @param symbol A variable of type String, line1 A variable of type Int, line2 A variable of type Int,.
 *
 */
void LineEd::execute(const std::string& symbol, const int& line1, const int& line2)
{
	if (symbol == "p")
	{
		print(line1, line2); // calls the print function
	}
	if (symbol == "i")
	{
		insert(line1); // calls the insert function 
	}
	if (symbol == "a")
	{
		append(); // calls the append function
	}
	if (symbol == "x")
	{
		cut(line1, line2); // calls the cut function
	}
	if (symbol == "v")
	{
		paste(line1); // calls the paste function
	}
	if (symbol == "j")
	{
		join(line1, line2); // calls the join function
	}
	if (symbol == "c")
	{
		replaceLine(line1, line2); // calls the replace function
	}
	if (symbol == "d")
	{
		deletes(line1, line2); // calls the delete function
	}
	if (symbol == "u")
	{
		moveUp(); // calls moveup function
	}
	if (symbol == "n")
	{
		moveDown(); // calls the movedown function
	}
	if (symbol == "g")
	{
		goTo(line1); // calls the goto function
		print(line1, line1); // then print the line
	}
	if (symbol == "w")
	{
		write(); // calls the write function
	}
	if (symbol == "q")
	{
		quit(); // calls the quit function
	}
}

/**
 * Append lines in buffer
 *
 * Ignores line range, if any. Enables the LineEd input mode. 
 * Appends text into the buffer after the last line. The current 
 * line is set to the last line entered.
 *
 */
void LineEd::append()
{
	saved = false;
	cout << "Entering input mode." << endl;
	while (!cin.eof())
	{
		string text;
		getline(cin, text);
		if (text == ".")
		{
			cout << "Entering command mode..." << endl;
			break;
		}
		buffer.push_back(text);
		currentLine = buffer.size();
	}
}

/**
 * Insert lines in buffer
 *
 * Ignores line address 2, if any. Enables the LineEd input mode. 
 * Inserts text into the buffer at line x. The current address 
 * is set to the last line entered.
 *
 * @param line1 A variable of type unsigned long
 *
 */
void LineEd::insert(unsigned long line1)
{
	saved = false;
	unsigned long tempLine = currentLine;
	currentLine = (line1-1); // make the current line, the line before the input line
	int lineNo{ 0 };
	list<string>::iterator it{ buffer.begin() };
	advance(it, line1 - 1);
	cout << "Entering input mode." << endl;
	while (!cin.eof()) // loop until the end of file
	{
		string text;
		getline(cin, text);
		if (text==".") // if the user input point then break from the loop
		{
			cout << "Entering command mode..." << endl;
			break;
		}
		buffer.insert(it, text); // insert the line at the end of buffer
		++lineNo; // increment lineno
	}
	currentLine = (lineNo > 0) ? currentLine + lineNo : tempLine;
	// make the currentLine the last inputed line or roll back to its previous value
}

/**
 * Delete lines from buffer
 *
 * Deletes the line range x through y from the buffer. If there 
 * is a line after the deleted line range, then the current 
 * address is set to that line; otherwise, if there is a line 
 * before the deleted line range, then the current address is 
 * set to that line; otherwise, the buffer must be empty and 
 * the current line undefined.
 *
 * @param line1 A variable of type unsigned long, line2 A variable of type unsigned long
 *
 */
void LineEd::deletes(unsigned long line1, unsigned long line2)
{
	if (buffer.size() > 0)
	{// check if buffer size is not empty
		if (line2 == 999) line2 = buffer.size(); // if line is 999 then take buffer size and line 2
		saved = false;
		if (line2 == buffer.size()) // if line line same as buffer then make current line pointing to the previous line
		{
			currentLine = line1 - 1;
		}
		else if (line1 == 1) // if line1 first line then set currentline as fist line
		{
			currentLine = line1;
		}
		else // set current line to the last line in the buffer
		{
			currentLine = line2 - 1;
		}
		if (line2 == 1) // if line1 is line 1 then pop the fist line in buffer
		{
			buffer.pop_front();
		}
		else
		{
			list<string>::iterator it1{ buffer.begin() }; // set iterator1 to beginning of buffer
			list<string>::iterator it2{ buffer.begin() }; // set iterator2 to beginning of buffer
			advance(it1, line1 - 1); // move iterator1 to line1
			advance(it2, line2); // move iterator2 to line2
			buffer.erase(it1, it2); //delete lines from buffer
		}
		
		if (buffer.size() < 1) // if buffer size is empty then set current line to 0
			currentLine = 0;
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Cut lines from buffer
 *
 * Cuts the line range x through y from the buffer into the clipboard. 
 * If there is a line after the cut line range, then the current 
 * address is set to that line; otherwise, if there is a line before 
 * the cut line range, then the current address is set to that line; 
 * otherwise, the buffer must be empty and the current line undefined.
 *
 * @param line1 A variable of type unsigned long, line2 A variable of type unsigned long
 *
 */
void LineEd::cut(unsigned long line1, unsigned long line2)
{
	if (buffer.size() > 0) 
	{// check if buffer size is not empty
		if (line2 == 999) line2 = buffer.size();// if line is 999 then take buffer size and line 2
		saved = false; // set saved to false
		clipboard.clear(); // clears any previous contents from clipboard
		list<string>::iterator it1{ buffer.begin() }; // set iterator1 to beginning of buffer
		list<string>::iterator it2{ buffer.begin() }; // set iterator2 to beginning of buffer
		advance(it1, line1 - 1); // move iterator1 to line1
		advance(it2, line1 - 1); // move iterator2 to line1

		for (unsigned long k = line1; k <= line2; ++k)
		{// loop from line1 till line 2
			clipboard.push_back(*it2); // push the line values in clipboard
			++it2; // increment iterator2
		}
		buffer.erase(it1, it2); //delete lines from buffer
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Paste lines to buffer
 *
 * Ignores line address 2, if any. Pastes text from the 
 * clipboard into the buffer at line x. The current 
 * address is set to the last line pasted.
 *
 * @param line1 A variable of type unsigned long
 *
 */
void LineEd::paste(unsigned long line1)
{
	if (line1 > buffer.size()) line1 = 1; // if line1 more than buffer size then set it line 1
	saved = false; // set saved to false
	list<string>::iterator it{ buffer.begin() }; // set iterator1 to beginning of buffer
	advance(it, line1 - 1); // set iterator1 to beginning of buffer
	buffer.insert(it, clipboard.begin(), clipboard.end()); // insert values from clipboard to buffer
	currentLine = (line1-1) + clipboard.size(); // set current line to last line pasted
}

/**
 * Replace lines in buffer
 *
 * Prompts for and reads the text to be changed, and then 
 * prompts for and reads the replacement text. Searches 
 * each line in the line range for an occurrence of the
 * specified string and changes all matched strings to the replacement text.
 *
 * @param line1 A variable of type unsigned long, line2 A variable of type unsigned long
 *
 */
void LineEd::replaceLine(unsigned long line1, unsigned long line2)
{
	if (buffer.size() > 0)
	{// check if buffer size is not empty
		if (line2 == 999) line2 = buffer.size();// if line is 999 then take buffer size and line 2
		string changeFrom; // define changeFrom variable
		string changeTo; // define changeFrom variable
		int changeCount{ 0 }; // define changeCount and assign 0 to it
		saved = false; // set saved to false
		list<string>::iterator it{ buffer.begin() }; // set iterator1 to beginning of buffer
		advance(it, line1 - 1); // set iterator1 to beginning of buffer
		cout << "change? " ; // display messange to change
		getline(cin, changeFrom); // take input from user from change
		cout << "to? "; // display message to
		getline(cin, changeTo);// take input from user to change
		for (int k = line1; k <= line2; ++k)  // loop through line1 to line2
		{
			size_t pos = it->find(changeFrom, 0); // check if change requested is in buffer
			while (pos != string::npos) // if value found then loop
			{
				it->replace(pos, changeFrom.length(), changeTo); // replace the values to the desired values
				++changeCount; // keep a cound of how many changed
				break; // break from the loop after each change
			}
			it++; // increment iterator2
		}
		if(changeCount>0) // if buffer size is empty then set current line to 0
			currentLine = line1+ changeCount;
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Join lines in buffer
 *
 * Joins the text from the specified line range together 
 * on one line at address x, concatenating the characters 
 * in the lines. Line x becomes the current line.
 *
 * @param line1 A variable of type unsigned long, line2 A variable of type unsigned long
 *
 */
void LineEd::join(unsigned long line1, unsigned long line2)
{
	if (buffer.size() > 0)
	{// check if buffer size is not empty
		if (line2 == 999) line2 = buffer.size(); // if line is 999 then take buffer size and line 2

		if (line1 == line2)		// we have to deal with this case otherwise a space will be added at the end of the line
		{
			currentLine = line1;
			return;
		}

		saved = false;

		list<string>::iterator it1{ buffer.begin() };  // set iterator1 to beginning of buffer
		list<string>::iterator it2{ buffer.begin() };  // set iterator2 to beginning of buffer
		advance(it1, line1 - 1); // set iterator1 to beginning of buffer
		advance(it2, line1 - 1); // set iterator2 to beginning of buffer

		stringstream ss;  // define ss
		for (unsigned long k = line1; k <= line2; ++k) // loop from line1 to line2
		{
			ss << *it2 << " "; // join all the lines in range into one line
			++it2; // fetch the next line
		}
		(*it1) = ss.str(); // store the lines one line
		deletes(line1 + 1, line2); // delete the lines from where it was joined
		currentLine = line1; // set current line to the fist line
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Print lines in buffer
 *
 * Prints the line range x through y without affecting the current line address.
 *
 * @param line1 A variable of type unsigned long, line2 A variable of type unsigned long
 *
 */
void LineEd::print(unsigned long line1, unsigned long line2)
{
	if (buffer.size() > 0)
	{// check if buffer size is not empty
		if (line2 == 999) line2 = buffer.size(); // if line is 999 then take buffer size and line 2
		if (line2 > buffer.size()) line2 = buffer.size(); // if line2 greater than buffer size then set line2 to last lines
		list<string>::iterator it{ buffer.begin() }; // set iterator1 to beginning of buffer
		advance(it, line1 - 1); // set iterator1 to beginning of buffer

		if ((line1 <= line2) & (line1 > 0 && line2 <= buffer.size())) { // go in only if line1 and line2 are valid lines
			for (int k = line1; k <= line2; ++k) { // loop from line1 to line2
				cout << k << (currentLine == k ? "> " : ": ") << *it << endl; // print the lines and replace : with > if it is the pointed line
				++it; // increment interator
			}
		}
		else
		{
			cout << "Invalid lines to print" << endl;
		}
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Move Up line in buffer
 *
 * Ignores line range, if any. Moves the current line up 
 * by one line provided that there is a line above the 
 * current line; otherwise, prints the message BOF reached 
 * and sets the current line to the first line in the buffer.
 *
 */
void LineEd::moveUp()
{
	if (buffer.size() > 0)
	{// check if buffer size is not empty
		if (currentLine == 1) // if currentline is fist line then show message to user
		{
			cout << "BOF reached" << endl;
		}
		else
		{
			--currentLine; // decrement current line
			print(currentLine, currentLine); // call print to show the current line
		}		
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Move Down line in buffer
 *
 * Ignores line range, if any. Moves the current line down 
 * by one line provided that there is a line after the 
 * current line; otherwise, prints the message EOF reached 
 * and sets the current line to the last line in the buffer.
 *
 */
void LineEd::moveDown()
{
	if (buffer.size() > 0)
	{// check if buffer size is not empty
		if (currentLine == buffer.size()) // if currentline is last line then show message to user
		{
			cout << "EOF reached." << endl;
		}
		else
		{
			++currentLine; // increment current line
			print(currentLine, currentLine); // call print to show the current line
		}		
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Go to line in buffer
 *
 * Ignores line address 2, if any. Goes to the specified 
 * line x, meaning that it sets the current line to x and prints it.
 *
 * @param line1 A variable of type unsigned long
 *
 */
void LineEd::goTo(unsigned long line1)
{
	if (buffer.size() > 0)
	{// check if buffer size is not empty
		currentLine = line1;	// set current line as line1	
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Write lines from buffer to file
 *
 * Ignores line range, if any. If there is a file associated with 
 * the buffer, it prompts the user asking whether it is OK 
 * to replace that file with the buffer contents. If the answer 
 * is negative, or there is no file associated with the buffer, 
 * it prompts the user for the name of a file to save the buffer to.
 *
 */
void LineEd::write()
{
	if (buffer.size() > 0)
	{// check if buffer size is not empty
		bool write = false; // define write variable and set to false
		if (fileName.empty()) // if filename is empty then ask user to input a filename
		{
			cout << "Enter the name of the file to write to: ";
			getline(cin, fileName);
			//cout << endl;
		}
		bool reply = askYesNo("Save changes to the file: " + fileName + " (y or n)? "); // ask user to save file
		if(reply) // if user select yes then set write as ture
		{
			write = true; // set write as true
		}
		else if (!reply) // if user select no then ask user to give new name
		{
			cout << "Enter the name of the file to write to: ";
			getline(cin, fileName);
			//cout << endl;
			write = true;
		}

		if (write)
		{
			fstream file(fileName, ios::out | ios::trunc);
			// using ios::trunc will tell the program to overwrite the existing file

			// Check if object is valid
			if (file)
			{
				std::list<string>::iterator it;
				for (it = buffer.begin(); it != buffer.end(); ++it) {
					file << *it << endl; // save line by line into the file
				}
			}
			saved = true; // make saved variable as true
			file.close(); // close the file
			cout << buffer.size() << " lines written to file \"" << fileName << "\"" << endl;
		}
	}
	else
	{
		cout << "File empty. Must use one of I,A,Q commands." << endl;
	}
}

/**
 * Quit program
 *
 * Ignores line range, if any. Quits LineEd. Before quitting, 
 * however, it gives the user a last chance to save the buffer. 
 * If the user takes the chance, it simulates the w command, 
 * and then quits; otherwise, it quits, discarding buffer contents.
 *
 */
void LineEd::quit()
{
	if (!saved) // if file not saved then promot user to save the file
	{
		cout << "There are unsaved changes." << endl;
		if (askYesNo("Do you wish to save the changes (y or n)? ")) // call write function if user want to save file
		{
			write();
		}
	}
	exit(0);
}

/**
 * Confirmation Message
 *
 * Ask user to confirm a given message
 *
 * @param question A variable of type String
 *
 */
bool LineEd::askYesNo(const string& question)
{
	cout << question;
	string answer;
	char ch;
	do
	{
		cin >> skipws; // remove any white space from the beginning
		getline(cin, answer); // get input from user
		ch = tolower(answer[0]);
	} while (ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N'); // loop until user give yes or no
	return (ch == 'y' || ch == 'Y'); // return true if user says yes
}