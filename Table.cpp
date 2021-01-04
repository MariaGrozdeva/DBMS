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
void setCorrectValueInCell(Cell& cellToBeSet, const string& value)
{
    CellType typeOfValue = cellToBeSet.getType();

    switch (typeOfValue)
    {
    case typeInt: cellToBeSet.setInteger(stoi(value)); break;
    case typeDouble: cellToBeSet.setDouble(stof(value)); break;
    case typeString: cellToBeSet.setString(value); break;
    case typeBool: cellToBeSet.setBool(value == "TRUE"); break;
    }
}

Table::Table() {}
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

int Table::getIndexOfColumn(const string& column)
{
    for (int i = 0; i < columns.size(); i++)
    {
        if (names[i] == column)
            return i;
    }
    throw "Error! Such column does not exist!";
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

vector<int> Table::where(const string& column, const string& op, const string& value)
{
    vector<int> indicesOfDesiredRows;

    if (column == "" && op == "" && value == "")
    {
        for (int i = 0; i < columns[0].size(); i++)
            indicesOfDesiredRows.push_back(i);
        return indicesOfDesiredRows;
    }

    int indexOfColumn = getIndexOfColumn(column);

    CellType typeOfColumn = types[indexOfColumn];
    Cell cellInColumn(typeOfColumn);
    setCorrectValueInCell(cellInColumn, value);

    for (int i = 0; i < columns[0].size(); i++)
    {
        if (op == "=")
        {
            if (columns[indexOfColumn][i] == cellInColumn)
                indicesOfDesiredRows.push_back(i);
        }

        else if (op == "!=")
        {
            if (columns[indexOfColumn][i] != cellInColumn)
                indicesOfDesiredRows.push_back(i);
        }

        else if (op == "<")
        {
            if (columns[indexOfColumn][i] < cellInColumn)
                indicesOfDesiredRows.push_back(i);
        }

        else if (op == "<=")
        {
            if (columns[indexOfColumn][i] <= cellInColumn)
                indicesOfDesiredRows.push_back(i);
        }

        else if (op == ">")
        {
            if (columns[indexOfColumn][i] > cellInColumn)
                indicesOfDesiredRows.push_back(i);
        }

        else if (op == ">=")
        {
            if (columns[indexOfColumn][i] >= cellInColumn)
                indicesOfDesiredRows.push_back(i);
        }
    }

    return indicesOfDesiredRows;
}

void Table::updateCertainCell(int indexOfRow, int indexOfColumn, const string& newValue)
{
    CellType typeOfNewValue = getTypeOfString(newValue);

    if (typeOfNewValue != types[indexOfColumn] && !(typeOfNewValue == typeInt && types[indexOfColumn] == typeDouble))
        throw "Error! Update failed! The new value is not of the correct type!";

    setCorrectValueInCell(columns[indexOfColumn][indexOfRow], newValue);
}
void Table::updateValuesInColumn(const string& column, const string& newValue, const vector<int>& indicesOfDesiredRows)
{
    int indexOfColumn = getIndexOfColumn(column);
    Cell toCheckIfExist(getTypeOfString(newValue));
    setCorrectValueInCell(toCheckIfExist, newValue);

    if (indexOfColumn == primaryKeyColIndex && existsValueInPrimaryKey(toCheckIfExist))
        throw "Error! Update failed! Duplicate primary key value!";

    for (int i = 0; i < indicesOfDesiredRows.size(); i++)
        updateCertainCell(indicesOfDesiredRows[i], indexOfColumn, newValue);
}
int Table::update(const vector<pair<string, string>> newValues, const string& key, const string& op, const string& value)
{
    vector<int> indicesOfDesiredRows = where(key, op, value);

    for (int i = 0; i < newValues.size(); i++)
        updateValuesInColumn(newValues[i].first, newValues[i].second, indicesOfDesiredRows);

    return indicesOfDesiredRows.size();
}

void Table::resizeNewTable(Table& newTable, int columnsSize)
{
    newTable.columns.resize(columnsSize);
    newTable.names.resize(columnsSize);
    newTable.types.resize(columnsSize);
}
void Table::setNewTable(Table& newTable, int posOfRow, int posOfCol, int posInNewTable)
{
    newTable.columns[posInNewTable].push_back(this->columns[posOfCol][posOfRow]);
    newTable.types[posInNewTable] = this->types[posOfCol];
    newTable.names[posInNewTable] = this->names[posOfCol];
    newTable.primaryKeyColIndex = this->primaryKeyColIndex;
}
void Table::createRowInNewTable(Table& newTable, int indexOfDesiredRow, const vector<int>& indicesOfDesiredColumns)
{
    for (int i = 0; i < indicesOfDesiredColumns.size(); i++)
        setNewTable(newTable, indexOfDesiredRow, indicesOfDesiredColumns[i], i);
}
Table Table::select(const vector<string>& namesOfDesiredColumns, const string& key, const string& op, const string& value)
{
    Table newTable;
    vector<int> indicesOfDesiredRows;
    vector<int> indicesOfDesiredColumns;

    if (key == "" && op == "" && value == "") // no where (select all rows)
    {
        for (int i = 0; i < this->columns[0].size(); i++)
            indicesOfDesiredRows.push_back(i);
    }
    else // where (select certain rows)
        indicesOfDesiredRows = where(key, op, value);

    if (!namesOfDesiredColumns.size()) // select *
    {
        resizeNewTable(newTable, this->columns.size());
        for (int i = 0; i < this->columns.size(); i++)
            indicesOfDesiredColumns.push_back(i);
    } 
    else // select col1 col2 .. coln
    {
        resizeNewTable(newTable, namesOfDesiredColumns.size());
        for (int i = 0; i < namesOfDesiredColumns.size(); i++)
            indicesOfDesiredColumns.push_back(getIndexOfColumn(namesOfDesiredColumns[i]));
    }

    for (int i = 0; i < indicesOfDesiredRows.size(); i++)
        createRowInNewTable(newTable, indicesOfDesiredRows[i], indicesOfDesiredColumns);

    return newTable;
}

void Table::swapRows(Table& table, int row)
{
    for (int i = 0; i < table.columns.size(); i++)
        swapCells(table.columns[i][row], table.columns[i][row + 1]);
}
Table Table::orderBy(const string& columnToOrderBy, const string& modifier, const vector<string>& namesOfDesiredColumns,
    const string& key, const string& op, const string& value)
{
    Table tableCreatedFromSelect = select(namesOfDesiredColumns, key, op, value);
    if (!tableCreatedFromSelect.columns[0].size())
        throw "Error! Value in no column corresponds to the given value of key!";

    int posOfColumnToOrderBy = getIndexOfColumn(columnToOrderBy);

    for (int i = 0; i < tableCreatedFromSelect.columns[0].size() - 1; i++)
    {
        bool isSwapped = false;
        for (int j = 0; j < tableCreatedFromSelect.columns[0].size() - i - 1; j++)
        {
            if (modifier == "ASC" &&
                tableCreatedFromSelect.columns[posOfColumnToOrderBy][j] > tableCreatedFromSelect.columns[posOfColumnToOrderBy][j + 1])
            {
                swapRows(tableCreatedFromSelect, j);
                isSwapped = true;
            }
            else if (modifier == "DESC" &&
                tableCreatedFromSelect.columns[posOfColumnToOrderBy][j] < tableCreatedFromSelect.columns[posOfColumnToOrderBy][j + 1])
            {
                swapRows(tableCreatedFromSelect, j);
                isSwapped = true;
            }
        }
        if (!isSwapped)
            return tableCreatedFromSelect;
    }

    return tableCreatedFromSelect;
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