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
	void updateCerainRow(int indexOfRow, int indexOfColumn, const string& newValue);
	void updateValuesInColumn(const string& column, const string& newValue, const vector<int>& indicesOfDesiredRows);

public:
	Table(const vector<pair<string, CellType>>& columns, const string& primaryKey);

	void insertInto(const vector<string>& values);
	int update(const vector<pair<string, string>> newValues, const string& key = "", const string& op = "", const string& value = "");

	void print() const;
};