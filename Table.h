#include <vector>
#include "Cell.h"

class Table
{
	vector<vector<Cell>> columns;
	vector<string> names;
	vector<CellType> types;

	int primaryKeyColIndex;
	
	bool existsValueInPrimaryKey(const Cell& cell);
	void insertIntoColumn(int colIndex, const string& value);

	int getIndexOfColumn(const string& column);

	vector<int> where(const string& column, const string& op, const string& value);

public:
	Table(const vector<pair<string, CellType>>& columns, const string& primaryKey);

	void insertInto(const vector<string>& values);

	void print() const;
};