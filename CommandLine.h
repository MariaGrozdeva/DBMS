#include <stack>
#include <fstream>
#include "Table.h"

class CommandLine
{
	unordered_map<string, Table> tables;

public:
	void startProgram();
};