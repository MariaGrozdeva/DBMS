#include "Table.h"

int main()
{
	vector<pair<string, CellType>> v;
	v.push_back(make_pair("id", typeInt));
	v.push_back(make_pair("first_name", typeString));
	v.push_back(make_pair("last_name", typeString));
	v.push_back(make_pair("age", typeInt));
	v.push_back(make_pair("grade", typeDouble));

	Table students(v, "id");
	students.insertInto({ "1","Angel","Ivanov","17","5.5" });
	students.insertInto({ "5","Maria","Georgieva","11","6" });
	students.print();

	vector<pair<string, string>> v1;
	v1.push_back(make_pair("age", "25"));
	v1.push_back(make_pair("grade", "2"));
	students.update(v1, "first_name", "=", "Angel");
	students.print();
}