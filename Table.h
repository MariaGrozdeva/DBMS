#include <vector>
#include "Cell.h"

class Table
{
	vector<vector<Cell>> columns;
	vector<string> names;
	vector<CellType> types;

	int primaryKeyColIndex;

	int getIndexOfColumn(const string& column);
	
	bool existsValueInPrimaryKey(const Cell& cell);
	void insertIntoColumn(int colIndex, const string& value);

	vector<int> where(const string& column, const string& op, const string& value);

	void updateCertainCell(int indexOfRow, int indexOfColumn, const string& newValue);
	void updateValuesInColumn(const string& column, const string& newValue, const vector<int>& indicesOfDesiredRows);

	void resizeNewTable(Table& newTable, int columnsSize);
	void setNewTable(Table& newTable, int posOfRow, int posOfCol, int posInNewTable);
	void createRowInNewTable(Table& newTable, int indexOfDesiredRow, const vector<int>& indicesOfDesiredColumns);

	void swapRows(Table& table, int row1, int row2);
	void sortTable(Table& tableToSort, int posOfColumnToOrderBy, const string& modifier);

public:
	Table();
	Table(const vector<pair<string, CellType>>& columns, const string& primaryKey);

	void insertInto(const vector<string>& values);
	int update(const vector<pair<string, string>> newValues, const string& key = "", const string& op = "", const string& value = "");
	Table select(const vector<string>& columns = {}, const string& key = "", const string& op = "", const string& value = "");
	Table orderBy(const string& columnToOrderBy, const string& modifier, const vector<string>& columns = {},
		const string& key = "", const string& op = "", const string& value = "");

	void print() const;
};