#ifndef LINEED_H
#define LINEED_H
#include <string>
#include <list>
#include <vector>
class LineEd
{
private:
	std::list <std::string> buffer; //stores a copy of file contents in a list
	std::vector<std::string> clipboard; //a place in memory where cut/copied text are stored
	unsigned long currentLine = 0; //stores the current pointed line in the list buffer
	std::string fileName; //stores the supplied filename
	bool saved = false; //stores the file status

	bool validateCommand(const std::string& command); // check if the command supplied is valid
	void execute(const std::string& symbol, const int& line1, const int& line2); // call the desired commands depending on the input
	bool askYesNo(const std::string& question); //confirmation message
	void append(); // changes the lines in the buffer
	void insert(unsigned long line1); // add new lines in the buffer
	void deletes(unsigned long line1, unsigned long line2); // remove lines from the buffer
	void cut(unsigned long line1, unsigned long line2); // cut lines from buffer to clipboard
	void paste(unsigned long line1); // paste lines from clipboard to buffer
	void replaceLine(unsigned long line1, unsigned long line2); // replace text with given text in lines
	void join(unsigned long line1, unsigned long line2); // merge a given range of lines into one line
	void print(unsigned long line1, unsigned long line2); // print a given range of lines
	void moveUp(); // move the current pointed line one step up
	void moveDown(); // move the current pointed line one step down
	void goTo(unsigned long line1); // show the current pointed line
	void write(); // saves the lines from buffer to file
	void quit(); // promot to save the file then quit
public:
	LineEd(const std::string& filename); // ctor, sets and open file
	void run(); //start the command screen after the input
	void runCommand(const std::string& cmd); // run a sequence of test commands 
};
#endif