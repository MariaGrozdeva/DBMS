#include "Cell.h"

Cell::Cell(CellType type) : type(type) {}

void Cell::setInteger(int value)
{
	this->valueInt = value;
}
void Cell::setDouble(double value)
{
	this->valueDouble = value;
}
void Cell::setString(string value)
{
	this->valueString = value;
}
void Cell::setBool(bool value)
{
	this->valueBool = value;
}

int Cell::getInteger() const
{
	return valueInt;
}
double Cell::getDouble() const
{
	return valueDouble;
}
string Cell::getString() const
{
	return valueString;
}
bool Cell::getBool() const
{
	return valueBool;
}

CellType Cell::getType() const
{
	return type;
}

void Cell::print() const
{
	switch (type)
	{
	case typeInt: cout << valueInt; break;
	case typeDouble: cout << valueDouble; break;
	case typeString: cout << valueString; break;
	case typeBool: cout << valueBool; break;
	}
}

bool operator==(const Cell& lhs, const Cell& rhs)
{
	if (lhs.getType() != rhs.getType())
		return false;

	switch (lhs.getType())
	{
	case typeInt: return lhs.getInteger() == rhs.getInteger();
	case typeDouble: return lhs.getDouble() == rhs.getDouble();
	case typeString: return lhs.getString() == rhs.getString();
	case typeBool: return lhs.getBool() == rhs.getBool();
	}

	return false;
}
bool operator!=(const Cell& lhs, const Cell& rhs)
{
	return !(lhs == rhs);
}
bool operator<(const Cell& lhs, const Cell& rhs)
{
	if (lhs.getType() != rhs.getType())
		return false;

	switch (lhs.getType())
	{
	case typeInt: return lhs.getInteger() < rhs.getInteger();
	case typeDouble: return lhs.getDouble() < rhs.getDouble();
	case typeString: return lhs.getString() < rhs.getString();
	case typeBool: return lhs.getBool() < rhs.getBool();
	}

	return false;
}
bool operator<=(const Cell& lhs, const Cell& rhs)
{
	if (lhs.getType() != rhs.getType())
		return false;

	switch (lhs.getType())
	{
	case typeInt: return lhs.getInteger() <= rhs.getInteger();
	case typeDouble: return lhs.getDouble() <= rhs.getDouble();
	case typeString: return lhs.getString() <= rhs.getString();
	case typeBool: return lhs.getBool() <= rhs.getBool();
	}

	return false;
}
bool operator>(const Cell& lhs, const Cell& rhs)
{
	return !(lhs <= rhs);
}
bool operator>=(const Cell& lhs, const Cell& rhs)
{
	return !(lhs < rhs);
}