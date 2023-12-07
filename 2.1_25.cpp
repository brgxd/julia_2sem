#include <iostream>
#include <map>
#include <list>
#include <set>

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

class SameKeyException : public Exception
{
protected:
    string Key;
public:
    SameKeyException(const char* s, string k) : Exception(s) { Key = k; }
    SameKeyException(const SameKeyException& c) : Exception(c) { Key = c.Key; }

    virtual void print()
    {
        cout << "Key " << Key << " is already present. " << str;
    }
};



//поиск по значению
template <class T , class T1>
list<T> znach_search(map<T, T1> m, T1 element)
{
    list<T> res;
    typename map<T, T1>::iterator it_m = m.begin();
    for (; it_m != m.end(); it_m++)
    {
        if (it_m->second == element)
        {
            T result = it_m->first;
            res.push_back(result);
        }     
    }
    return res;
}

//поиск по ключу
template <class T, class T1>
list<T1> key_search(map<T, T1> m, T key)
{
    list<T1> res;
    typename map<T,T1>::iterator it_m = m.begin();
    for (; it_m != m.end(); it_m++)
        if (it_m->first == key)res.push_back(it_m->second);
    return res;
}

//вывод содержимого дерева в консоль
void show(map<string, int> m)
{
    for (map<string,int>::iterator it_m = m.begin(); it_m != m.end(); it_m++)
        cout << "key: " << it_m->first << ", value: " << it_m->second << "\n";
    cout << "\n";
}

//предикат
bool programmerlvl(int value)
{
    return (value > 0 && value < 11) ? 1 : 0;
}

//фильтр
template<class T, class T1>
map<T, T1> filter(map<T, T1> m, bool(*predicate)(T1))
{
    map<T, T1> res;
    for (typename map<T, T1>::iterator it_m = m.begin(); it_m != m.end(); it_m++)
    {
        if (predicate(it_m->second))
            res[it_m->first] = it_m->second;
    }
    return res;
}

//добавление эллемента
template<class T, class T1>
void insert(map<T, T1> m, T key, T1 value)
{
    for (typename map<T, T1>::iterator it_m = m.begin(); it_m != m.end(); it_m++)
    {
        if (it_m->first == key)
            throw SameKeyException("All keys must be unique", key);
    }
    m[key] = value;
}

//функция возвращающая различные значения дерева
template<class T, class T1>
set<T1> unique_values(map<T, T1> m)
{
    set<T1> res;
    for (typename map<T, T1>::iterator it_m = m.begin(); it_m != m.end(); it_m++)
        res.insert(it_m->second);
    return res;
}

template<class T1>
ostream& operator <<(ostream& s, list<T1>& lst)
{
    for (typename list<T1>::iterator b = lst.begin(); b != lst.end(); b++)
    {
        cout << *b << " ";
    }
    cout << "\n";
    return s;
}

int main()
{
    try
    {
       map<string, int> p;

       p["Ivan Ivanov"] = 10;
       p["Petr Volkov"] = 7;
       p["Alexandr Smirnov"] = 7;
       p["Ivan Ivanov"] = 6;
       p["Aleksey Jukov"] = 11;
       p["Ignatiy Alekseev"] = -25;

       //insert(p, string("Ivan Ivanov"), 10);

       show(p);

       map<string, int> p2;

       p2 = filter(p, programmerlvl);

       show(p2);

       list<string> l = znach_search(p2, 7);

       cout << l << "\n";

       list<int> l2;

       l2 = key_search(p2, string("Ivan Ivanov"));

       cout << l2;

       set<int> s;

       s = unique_values(p2);

       for (set<int>::iterator it = s.begin(); it != s.end(); it++)
           cout << *it << " ";

    }
    catch(SameKeyException e)
    {
        cout << "\nCaught SameKeyException: "; e.print();
    }
}

