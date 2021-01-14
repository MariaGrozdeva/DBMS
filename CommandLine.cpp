#include "CommandLine.h"

void enterCommand(string& command) // reading a command
{
	getline(cin, command);
}

void readPrimaryKey(const string& columnsNamesTypesAndKeyValue, string& primaryKey)
{
	int i = columnsNamesTypesAndKeyValue.size() - 1;
	for (i; columnsNamesTypesAndKeyValue[i] < 'A' || columnsNamesTypesAndKeyValue[i] > 'z'; i--); // setting i at the end of the primaryKeyValue

	stack<char> reversedPrimaryKey;
	for (i; columnsNamesTypesAndKeyValue[i] != ' '; i--)
		reversedPrimaryKey.push(columnsNamesTypesAndKeyValue[i]); // getting the primary key reversed

	while (!reversedPrimaryKey.empty())
	{
		primaryKey.push_back(reversedPrimaryKey.top()); // getting the primary key ordered correctly
		reversedPrimaryKey.pop(); 
	}
}
void setColumnsTypes(const string& tempWord, vector<CellType>& columnsTypes)
{
	if (tempWord == "int")
		columnsTypes.push_back(typeInt);
	else if (tempWord == "double")
		columnsTypes.push_back(typeDouble);
	else if (tempWord == "string")
		columnsTypes.push_back(typeString);
	else if (tempWord == "bool")
		columnsTypes.push_back(typeBool);
}
// reading the columns' attributes: name, type and primary key value
void readColumnsNamesTypesAndKeyValue(vector<string>& columnsNames, vector<CellType>& columnsTypes, string& primaryKey) 
{
	string columnsNamesTypesAndKeyValue;
	getline(cin, columnsNamesTypesAndKeyValue); // reading the mentioned attributes as a sting

	string tempWord;
	int countOfSpaces = 0;

	for (int i = 0; columnsNamesTypesAndKeyValue[i] != ')'; i++) // parsing the read string
	{
		if ((columnsNamesTypesAndKeyValue[i] >= 'A' && columnsNamesTypesAndKeyValue[i] <= 'z') || columnsNamesTypesAndKeyValue[i] == '_')
			tempWord.push_back(columnsNamesTypesAndKeyValue[i]);

		if (columnsNamesTypesAndKeyValue[i] == ' ')
		{
			countOfSpaces++;

			if (countOfSpaces % 2) // having read an odd number of spaces means that we have read the name of a certain column
				columnsNames.push_back(tempWord); // pushing the name into the vector of names
			else // having read an even number of spaces means that we have read the type of a certain column
				setColumnsTypes(tempWord, columnsTypes); // pushing the type into the vector of types

			tempWord.clear();
		}
	}

	setColumnsTypes(tempWord, columnsTypes); // Setting the type of the last column. We need this because the for-loop ends when ")"  is meeted.
	// But we push the type when we meet a space. So that's why we need to push the last type explicitly.
	readPrimaryKey(columnsNamesTypesAndKeyValue, primaryKey); // reading the primary key and setting it
}

// reading the columns' values
void readValuesInColumns(vector<string>& valuesInColumns)
{
	string values;
	getline(cin, values); // reading the values as a string

	string tempWord;

	for (int i = 0; values[i] != ')'; i++) // parsing the read string
	{
		if (values[i] == '\"')
		{
			while (values[++i] != '\"')
				tempWord.push_back(values[i]);
			continue;
		}

		if (values[i] != '(' && values[i] != ' ' && values[i] != ',')
			tempWord.push_back(values[i]);

		if (values[i] == ',')
		{
			valuesInColumns.push_back(tempWord);
			tempWord.clear();
		}
	}
	valuesInColumns.push_back(tempWord);
}

bool bothAreSpaces(char lhs, char rhs) 
{ 
	return (lhs == rhs) && (lhs == ' ');
}
void replaceSpacesWithOneSpace(string& str)
{
	string::iterator newEnd = unique(str.begin(), str.end(), bothAreSpaces);
	str.erase(newEnd, str.end());
}

void splitString(string str, const string& delimiter, vector<string>& tokens)
{
	size_t pos = 0;
	string token;

	while ((pos = str.find(delimiter)) != string::npos)
	{
		token = str.substr(0, pos);
		tokens.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	tokens.push_back(str);
}

int searchInVector(const vector<string>& tokens, const string& str)
{
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == str)
			return i;
	}
	return -1;
}

// separated the string aggFuncAndColumn into two string (aggFunc, column), e.g., MAX(sdp_grade) -> MAX and sdp_grade
void parseAggFuncAndColumn(string& aggFuncAndColumn, string& aggFunc, string& column)
{
	string delimiter1 = "(";
	aggFunc = aggFuncAndColumn.substr(0, aggFuncAndColumn.find(delimiter1));

	string delimiter2 = ")";

	string temp = aggFuncAndColumn.substr(0, aggFuncAndColumn.find(delimiter2));
	column = temp.substr(aggFuncAndColumn.find(delimiter1) + 1);
}
// separated the string columnAndNewValue into two string (column, newValue), e.g., sdp_grade=6.00 -> sdp_grade and 6.00
void parseColumnAndNewValue(string& columnAndNewValue, string& column, string& newValue)
{
	string delimiter = "=";

	column = columnAndNewValue.substr(0, columnAndNewValue.find(delimiter));
	newValue = columnAndNewValue.substr(columnAndNewValue.find(delimiter) + 1);

	string temp = newValue.substr(0, newValue.size() - 1);
	newValue = temp;
}

// false - not aggregate, true - aggregate
bool readInputForSelectAndOrderBy(vector<string>& desiredColumns, vector<pair<string, string>>& agg,
	string& key, string& op, string& value, vector<string>& tokens, int& fromIndex)
{
	string inputWithSemiColon; 
	getline(cin, inputWithSemiColon);

	string input = inputWithSemiColon.substr(0, inputWithSemiColon.size() - 1); // removing the semicolon in the end	
	replaceSpacesWithOneSpace(input); // removing the multiple spaces
	splitString(input, " ", tokens); // splitting the whole input into tokens(separate words)

	fromIndex = searchInVector(tokens, "FROM");
	bool shouldAggregate = tokens[fromIndex - 1][tokens[fromIndex - 1].size() - 1] == ')';

	for (int i = 0; shouldAggregate && i < fromIndex; i++) // if should aggregate, creates a vector of pairs of agg funcs and columns
	{
		string tempAggFunc;
		string tempColumn;

		parseAggFuncAndColumn(tokens[i], tempAggFunc, tempColumn);
		agg.push_back(make_pair(tempAggFunc, tempColumn));
	}
	
	if (!(fromIndex == 1 && tokens[0] == "*") && !shouldAggregate) // no select*
		desiredColumns.insert(desiredColumns.begin(), tokens.begin(), tokens.begin() + fromIndex);

	if (!(tokens.size() <= fromIndex + 2)) // where..
	{
		key = tokens[fromIndex + 3];
		op = tokens[fromIndex + 4];
		value = tokens[fromIndex + 5];
	}

	return shouldAggregate;
}


void CommandLine::startProgram()
{
	while (true)
	{
		string command;
		enterCommand(command);

		ofstream file;

		if (command == "CREATE TABLE")
		{
			string tableName;
			cin >> tableName; // reading the name of the table
			cin.ignore();

			vector<string> columnsNames;
			vector<CellType> columnsTypes;
			string primaryKey;

			readColumnsNamesTypesAndKeyValue(columnsNames, columnsTypes, primaryKey);

			vector<pair<string, CellType>> columns;
			for (int i = 0; i < columnsNames.size(); i++)
				columns.push_back(pair<string, CellType>(columnsNames[i], columnsTypes[i])); // The table constr accepts a vector of pairs
			// of names and types. That's why we should merge our two vectors into one of pairs.

			Table newTable(columns, primaryKey); // creating the table
			tables[tableName] = newTable; // adding the table into the unordered_map tables

			file.open(tableName + ".txt");
			for (int i = 0; i < columnsNames.size(); i++) // writing the table into a text file
			{
				file << columnsNames[i];
				file << ",";
			}
			file.close();

			cout << "Table " << tableName << " created." << endl;
		}

		if (command == "INSERT INTO")
		{
			string tableName;
			cin >> tableName;
			cin.ignore();

			vector<string> valuesInColumns;

			readValuesInColumns(valuesInColumns);
			tables[tableName].insertInto(valuesInColumns); // inserting the row into the table

			file.open(tableName + ".txt", ios::app);
			file << '\n';
			for (int i = 0; i < valuesInColumns.size(); i++) // writing the row into the corresponding file
			{
				file << valuesInColumns[i];
				file << ",";
			}
			file.close();

			cout << "Record inserted." << endl;
		}

		if (command == "UPDATE")
		{
			string inputWithSemiColon;
			getline(cin, inputWithSemiColon);

			string input = inputWithSemiColon.substr(0, inputWithSemiColon.size() - 1); // removing the semicolon in the end
			vector<string> tokens;
			splitString(input, " ", tokens);

			string tableName;
			vector<pair<string, string>> newValues;
			string key, op, value;

			int indexOfSet = searchInVector(tokens, "SET");
			int indexOfWhere = searchInVector(tokens, "WHERE");

			tableName = tokens[indexOfSet - 1];

			for (int i = indexOfSet + 1; i < (indexOfWhere == -1 ? tokens.size() : indexOfWhere); i++)
			{
				string tempColumn, tempNewValue;
				parseColumnAndNewValue(tokens[i], tempColumn, tempNewValue);
				newValues.push_back(make_pair(tempColumn, tempNewValue));
			}

			if (indexOfWhere != -1)
			{
				key = tokens[indexOfWhere + 1];
				op = tokens[indexOfWhere + 2];
				value = tokens[indexOfWhere + 3];
			}

			int numOfUpdatedRows = tables[tableName].update(newValues, key, op, value);
			cout << numOfUpdatedRows << " rows updated.";
		}

		if (command == "SELECT")
		{
			vector<string> desiredColumns; // not agg columns
			vector<pair<string, string>> desiredAggregateColumns; // agg columns
			string key, op, value;

			vector<string> tokens;
			int fromIndex;

			bool shouldAggregate = readInputForSelectAndOrderBy(desiredColumns, desiredAggregateColumns, key, op, value, tokens, fromIndex);
			if (shouldAggregate) // use aggregate func if should aggregate
			{
				vector<double> agg = tables[tokens[fromIndex + 1]].aggregate(desiredAggregateColumns, key, op, value);
				for (int i = 0; i < agg.size(); i++)
					cout << agg[i] << " ";
				cout << endl;
				continue;
			}

			Table result = tables[tokens[fromIndex + 1]].select(desiredColumns, key, op, value); // no aggregate -> select func
			int numOfRowsSelected = result.getColumns()[0].size();

			result.print();
			cout << numOfRowsSelected << " rows selected." << endl;
		}

		if (command == "ORDER BY")
		{
			vector<string> desiredColumns; // columns we want to order
			vector<pair<string, string>> desiredAggregateColumns; // a parameter we don't use. needed only to be passed to the 
			// "readInputForSelectAndOrderBy" function
			string key, op, value;

			vector<string> tokens;
			int fromIndex = searchInVector(tokens, "FROM");
			int orderIndex = searchInVector(tokens, "ORDER");

			string columnNameToOrderBy = tokens[orderIndex + 2];
			string modifier = tokens[orderIndex + 3];

			readInputForSelectAndOrderBy(desiredColumns, desiredAggregateColumns, key, op, value, tokens, fromIndex);

			Table result = tables[tokens[fromIndex + 1]].orderBy(columnNameToOrderBy, modifier, desiredColumns, key, op, value);
			int numOfRowsSelected = result.getColumns()[0].size();

			result.print();
			cout << numOfRowsSelected << " rows selected." << endl;
		}

		if (command == "CREATE INDEX ON")
		{
			string inputWithSemiColon;
			getline(cin, inputWithSemiColon);

			string input = inputWithSemiColon.substr(0, inputWithSemiColon.size() - 1); // removing the semicolon in the end

			string tableName, columnName;
			parseAggFuncAndColumn(input, tableName, columnName); // using this func because here the delimiter is same ("(")

			tables[tableName].createIndex(columnName);
			cout << "Index created.";
		}

		if (command == "PRINT")
		{
			string tableName;
			cin >> tableName;
			cin.ignore();

			tables[tableName].print();
		}

		if (command == "QUIT")
		{
			cout << "Exitting. Good bye!" << endl;
			break;
		}
	} 
}