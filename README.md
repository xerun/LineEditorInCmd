# LineEditorInCmd

Typically, a line editor would prompt you for a command and then you would type in a command 
telling it which line you wanted displayed or edited. If you wanted to insert a line, then you would
tell it that you wanted to insert a line at a particular line address and then enter that line. If you
wanted to delete a line, you would have to specify the address of that line. You would repeatedly
issue editing commands and then wait until the computer responded. To get a visual view of the
program you were editing, you would issue a printing command and then wait until the computer
responded. The wait times would add up considerably. During peak hours, programmers' editing
commands could bring their editing sessions to a halt. Meanwhile, one popular line editor of the
time was ed under Unix; it worked in silent mode, demanding minimal input, generating minimal
output, and offering an extensive set of commands with forgiving syntax.
Today, line text editors are virtually useless, without practical applications. Nonetheless, the process 
of actually implementing a line text editor does provide not only an instructive programming
experience but also plenty of opportunity to practice using the STL sequential container classes
and iterators.

