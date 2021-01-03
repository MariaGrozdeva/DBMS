#include "Table.h"

bool checkIfStringIsValidNumber(const string& str)
{
    if (str[0] == '.' || str[str.size() - 1] == '.')
        return false;

    int countOfDots = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != '.' && !(str[i] >= '0' && str[i] <= '9'))
            return false;

        if (str[i] == '.')
            countOfDots++;
        if (countOfDots > 1)
            return false;
    }

    return true;
}
bool checkIfStringIsBoolean(const string& str)
{
    return str == "TRUE" || str == "FALSE";
}
CellType getTypeOfString(const string& str)
{
    if (checkIfStringIsValidNumber(str))
        return stoi(str) == stof(str) ? typeInt : typeDouble;

    return checkIfStringIsBoolean(str) ? typeBool : typeString;
}

Table::Table(const vector<pair<string, CellType>>& columns, const string& primaryKey)
{
    for (int i = 0; i < columns.size(); i++)
    {
        names.push_back(columns[i].first);
        types.push_back(columns[i].second);
        this->columns.push_back(vector<Cell>());

        if (primaryKey == columns[i].first)
            primaryKeyColIndex = i;
    }
}

bool Table::existsValueInPrimaryKey(const Cell& cell)
{
    for (int i = 0; i < columns[primaryKeyColIndex].size(); i++)
    {
        if (columns[primaryKeyColIndex][i] == cell)
            return true;
    }
    return false;
}
void Table::insertIntoColumn(int colIndex, const string& value)
{
    switch (types[colIndex])
    {
    case typeInt:
        if (checkIfStringIsValidNumber(value) && stoi(value) == stof(value))
        {
            Cell newCell(typeInt);

            if (colIndex == primaryKeyColIndex && existsValueInPrimaryKey(newCell))
                throw "Error! Duplicate primary key value!";

            newCell.setInteger(stoi(value));
            columns[colIndex].push_back(newCell);
        } 
        else
            throw "Error! Values in this column should be integers!";
        break;

    case typeDouble:
        if (checkIfStringIsValidNumber(value))
        {
            Cell newCell(typeDouble);

            if (colIndex == primaryKeyColIndex && existsValueInPrimaryKey(newCell))
                throw "Error! Duplicate primary key value!";

            newCell.setDouble(stof(value));
            columns[colIndex].push_back(newCell);
        }
        else
            throw "Error! Values in this column should be double numbers!";
        break;

    case typeBool:
        if (checkIfStringIsBoolean(value))
        {
            Cell newCell(typeBool);

            if (colIndex == primaryKeyColIndex && existsValueInPrimaryKey(newCell))
                throw "Error! Duplicate primary key value!";

            newCell.setBool(value == "TRUE");
            columns[colIndex].push_back(newCell);
        }
        else
            throw "Error! Values in this column should be booleans!";
        break;

    case typeString:
        Cell newCell(typeString);

        if (colIndex == primaryKeyColIndex && existsValueInPrimaryKey(newCell))
            throw "Error! Duplicate primary key value!";

        newCell.setString(value);
        columns[colIndex].push_back(newCell);
    }
}
void Table::insertInto(const vector<string>& values)
{
    if (values.size() != columns.size())
        throw "Invalid number of values!";

    for (int i = 0; i < values.size(); i++)
        insertIntoColumn(i, values[i]);
}

void Table::print() const
{
    for (int i = 0; i < columns.size(); i++)
        cout << names[i] << "    ";
    cout << endl;

    for (int i = 0; i < columns[0].size(); i++)
    {
        for (int j = 0; j < columns.size(); j++)
        {
            columns[j][i].print();
            cout << "       ";
        }
        cout << endl;
    }
}