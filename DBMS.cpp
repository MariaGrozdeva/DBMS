#include "CommandLine.h"

// After the name of the command, enter should be pressed! For example:
// INSERT INTO '\n'
// students ("Ivan Petrov", 1000, 1, 4.00);

// Spaces should be put as in the example. More spaces are not a problem, but lack of such, is.
// Spaces shouldn't be put only in functions "update" after SET (when listing the columns and their new values)
//                                            and "select with aggregate" when listing the agg funcs and columns, e.g.,
// UPDATE '\n'
// students SET sdp_grade=6.00 WHERE group = 2;
// SELECT '\n'
// MIN(sdp_grade), MAX(sdp_grade), AVG(sdp_grade) FROM students;

// Example input is attached.


int main()
{
	CommandLine c;
	c.startProgram();
}