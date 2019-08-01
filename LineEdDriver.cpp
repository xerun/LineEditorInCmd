#include <iostream>
#include <string>
#include<cstdlib> // for EXIT_FAILURE

using  std::string;
using  std::cout;
using std::cerr;
using std::endl;
#include "LineEd.h"

// function prototypes
void testLineEd(const string& filename);

int main(int argc, char* argv[])
{
	if (argc > 2)  // too many arguments
	{
		cerr << "Usage 1: " << argv[0] << "\n";
		cerr << "Usage 2: " << argv[0] << " filename\n";
		exit(EXIT_FAILURE);
	}

	string filename{}; // empty file name, in case argc==1
	if (argc == 2) // only one argument, a file name expected
	{
		filename = argv[1];
	};

	// Normally, we'd run the editor by uncommenting the following two lines
	LineEd ed(filename); // create a LineED object
	ed.run();             // run the line editor

	// test our line editor
	//testLineEd(filename); // normally we'd comment out this line

	return 0;
}


void testLineEd(const string& filename)
{
	LineEd ed(filename);    // create a LineED object

	ed.runCommand("z1,$");  // bad command
	ed.runCommand("1,$p");  // bad command
	ed.runCommand("1$");    // bad command
	ed.runCommand(",.p");   // bad command

	ed.runCommand("1,$");   // print all

	// next the given invalid line range 
	// $,1 is first adjusted to 1,$,
	// then the line range 1,$ is cut out 
	// from the buffer into the clipboard,
	// leaving the buffer empty. 
	ed.runCommand("x$, 1");

	ed.runCommand("p");// not allowed on empty buffer

	ed.runCommand("v");     // paste ino empty buffer
	ed.runCommand("1,$");   // print all

	ed.runCommand("i2");    // insert at line 2
	ed.runCommand("1,$");   // print all

	ed.runCommand("x4,5"); // cut lines 4 and 5
	ed.runCommand("v100,1"); // same as "v1"
	ed.runCommand("1,$");   // print all

	ed.runCommand("w");   // save changes
	////////////////////////////////////////////////////////

	ed.runCommand("1,$");   // print all
	ed.runCommand("c3,6");  // change 2. to two.
	ed.runCommand("1,$");   // print all

	ed.runCommand("."); // same as p.,.
	ed.runCommand("n"); // down one line
	ed.runCommand("n"); // down one line
	ed.runCommand("1,$");   // print all
	ed.runCommand("w"); // save buffer
	////////////////////////////////////////////////////////

	ed.runCommand("x3"); // cut line 3
	ed.runCommand("d1"); // del line 1
	ed.runCommand("1,$");   // print all

	ed.runCommand("d2,3"); // del line 2-3
	ed.runCommand("1,$");   // print all
	ed.runCommand("v1"); // paste at 1
	ed.runCommand("1,$");   // print all

	ed.runCommand("j2,$");  // join lines
	ed.runCommand("1,$");   // print all

	ed.runCommand("j1,$");  // join all lines
	ed.runCommand("1,$");   // print all
	ed.runCommand("w"); // save buffer
	////////////////////////////////////////////////////////

	ed.runCommand("a"); // append
	ed.runCommand("$,1"); // print all
	ed.runCommand("q"); // quit

}
