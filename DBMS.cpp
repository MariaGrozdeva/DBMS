#include "Table.h"

int main()
{
	vector<pair<string, CellType>> v;
	v.push_back(make_pair("id", typeInt));
	v.push_back(make_pair("first_name", typeString));
	v.push_back(make_pair("last_name", typeString));
	v.push_back(make_pair("age", typeInt));
	v.push_back(make_pair("grade", typeDouble));

	vector<pair<string, string>> v1;
	v1.push_back(make_pair("COUNT", "first_name"));
	v1.push_back(make_pair("SUM", "age"));
	v1.push_back(make_pair("AVG", "grade"));

	Table students(v, "id");
	students.insertInto({ "1","Angel","Ivanov","17","2" });
	students.insertInto({ "5","Maria","Georgieva","11","6" });
	students.insertInto({ "10","Uga","Buga","90","4" });
	students.print();
	cout << endl;

	vector<double> aggregatedValues;
	aggregatedValues = students.aggregate(v1, "id", ">", "1");

	for (int i = 0; i < aggregatedValues.size(); i++)
		cout << aggregatedValues[i] << " ";
	cout << endl;
}