#include <list>
#include <iostream>
#include<cmath>
using namespace std;

class Exception : public exception
{
protected:
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class Invalidlvlexception : public Exception
{
public:
	Invalidlvlexception(const char* s) : Exception(s) {}
	Invalidlvlexception(const Invalidlvlexception& c) : Exception(c) {}

	virtual void print()
	{
		cout << "Invalidlvlexception: " << str << what();
	}
};

template<class T>
void insert(list<T>& lst, T element)
{
	auto p = lst.begin();
	while (p != lst.end())
	{
		if (*p > element)
			break;
		p++;
	}lst.insert(p, element);
}

template<class T>
void push(list<T>& lst, T element)
{
	auto b = lst.begin();
	if (lst.empty() || *b == element)
	{
		lst.push_front(element);
		return;
	}
	for (; b != lst.end();)
	{
		if (element > *b)
		{
			lst.insert(b, element);
			return;
		}
		b++;
	}
	lst.push_back(element);
	return;
}

template<class T>
T pop(list<T>& lst)
{
	auto b = lst.begin();
	T res = *b;
	lst.erase(b);
	return res;
}

bool iscube(int value)
{
	double a = (pow(abs(value), 1 / 3.0));
	return abs(a - round(a)) < 0.000001 ? 1 : 0;
}

template<class T>
list<T> filter(const list<T> lst, bool (*predicate)(T))
{
	list<T> res;
	auto b = lst.begin();
	for (; b != lst.end(); b++)
	{
		if (predicate(*b) == true)
			res.push_back(*b);
	}
	return res;
}

template<class T1>
ostream& operator <<(ostream& s, list<T1>& lst)
{
	for (auto b = lst.begin(); b != lst.end(); b++)
	{
		cout << *b << " ";
	}
	cout << "\n";
	return s;
}

class programmer
{
public:
	string sname;
	string n;
	string mail;
	string s;
	string tg;
	string language;
	string job;
	int lvl;

	programmer(string surname, string name, string email, string skype, string telegram, string mainlanguage, string currentjob, int level)
	{
		if (level > 10 || level < 1)
		{
			throw Invalidlvlexception("level needs to be in[1, 10]");
		}
		sname = surname;
		n = name;
		mail = email;
		s = skype;
		tg = telegram;
		language = mainlanguage;
		job = currentjob;
		lvl = level;
	}

	~programmer() {}

	programmer operator =(programmer p)
	{
		sname = p.sname;
		n = p.n;
		mail = p.mail;
		s = p.s;
		tg = p.tg;
		language = p.language;
		job = p.job;
		lvl = p.lvl;
		return *this;
	}

	bool operator ==(programmer p)
	{
		return (lvl == p.lvl && language == p.language && sname == p.sname && n == p.n) ? 1 : 0;
	}

	bool operator >(programmer p)
	{
		if (lvl == p.lvl)
		{
			if (language == p.language)
			{
				if (sname == p.sname)
					return (n < p.n) ? 1 : 0;
				return (sname < p.sname) ? 1 : 0;
			}
			return(language < p.language) ? 1 : 0;
		}
		return (lvl > p.lvl) ? 1 : 0;
	}

	friend ostream& operator<<(ostream& s, programmer p);
};

ostream& operator<<(ostream& s, programmer p)
{
	s << p.lvl << " " << p.language << " " << p.sname << " " << p.n << "\n";
	return s;
}

int main()
{

	list<int> lst{ 11 };
	push(lst, 13);
	push(lst, 1);
	push(lst, 2);
	push(lst, 27);
	push(lst, 9);

	cout << lst << "\n";

	list<int> lst2 = filter(lst, iscube);

	cout << lst2 << "\n";

	try
	{

		list<programmer> lst;

		programmer a("aa", "aa", "aa", "aa", "aa", "aa", "aa", 10);
		programmer b("bb", "bb", "bb", "bb", "bb", "bb", "bb", 9);
		programmer c("cc", "cc", "cc", "cc", "cc", "cc", "cc", 10);
		programmer d("dd", "dd", "dd", "dd", "dd", "dd", "dd", 10);
		programmer e("ee", "ee", "ee", "ee", "ee", "ee", "ee", 10);
		programmer A("AA", "AA", "AA", "AA", "AA", "AA", "AA", 10);
		programmer B("BB", "BB", "BB", "BB", "BB", "BB", "BB", 7);

		push(lst, a);
		push(lst, c);
		push(lst, e);
		push(lst, A);
		push(lst, d);
		push(lst, b);
		push(lst, B);

		cout << lst << "\n";

		cout << pop(lst) << "\n";

		cout << lst << "\n";

	}

	catch (Invalidlvlexception e)
	{
		cout << "\nCaught Invalidlvlexception: "; e.print();
	}
}
