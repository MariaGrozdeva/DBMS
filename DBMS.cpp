#include "Table.h"

int main()
{
	vector<pair<string, CellType>> v;
	string s1 = "id";
	string s2 = "first_name";
	string s3 = "last_name";
	string s4 = "age";
	string s5 = "grade";

	v.push_back(make_pair(s1, typeInt));
	v.push_back(make_pair(s2, typeString));
	v.push_back(make_pair(s3, typeString));
	v.push_back(make_pair(s4, typeInt));
	v.push_back(make_pair(s5, typeDouble));

	Table students(v, s1);
	students.insertInto({ "1","Angel","Ivanov","17","5.5" });
	students.insertInto({ "5","Maria","Georgieva","11","6.0" });
	students.print();
}