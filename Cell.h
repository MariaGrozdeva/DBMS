#include <iostream>
#include <string>

using namespace std;

enum CellType { typeInt, typeDouble, typeString, typeBool };

class Cell
{
	int valueInt;
	double valueDouble;
	string valueString;
	bool valueBool;

	CellType type;

public:
	Cell(CellType type);

	void setInteger(int value);
	void setDouble(double value);
	void setString(string value);
	void setBool(bool value);

	int getInteger() const;
	double getDouble() const;
	string getString() const;
	bool getBool() const;

	CellType getType() const;

	void print() const;
};

bool operator==(const Cell& lhs, const Cell& rhs);
bool operator!=(const Cell& lhs, const Cell& rhs);
bool operator<(const Cell& lhs, const Cell& rhs);
bool operator<=(const Cell& lhs, const Cell& rhs);
bool operator>(const Cell& lhs, const Cell& rhs);
bool operator>=(const Cell& lhs, const Cell& rhs);

void swapCells(Cell& lhs, Cell& rhs);