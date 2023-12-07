#include <iostream>
#include <map>
#include <list>

using namespace std;

//поиск по значению
template <class T, class T1>
list<T> znach_search(multimap<T, T1> m, T1 element)
{
    list<T> res;
    typename multimap<T,T1>::iterator it_m = m.begin();
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
list<T1> key_search(multimap<T, T1> m, T key)
{
    list<T1> res;
    typename multimap<T, T1>::iterator it_m = m.find(key);
    if(it_m->first == key)
        res.push_back(it_m->second);
    return res;
}

//вывод содержимого дерева в консоль
void show(multimap<string, int> m)
{
    for (multimap<string, int>::iterator it_m = m.begin(); it_m != m.end(); it_m++)
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
multimap<T, T1> filter(multimap<T, T1> m, bool(*predicate)(T1))
{
    multimap<T, T1> res;
    for (typename multimap<T, T1>::iterator it_m = m.begin(); it_m != m.end(); it_m++)
    {
        if (predicate(it_m->second))
            res.insert(*it_m);      
    }
    return res;
}

//функция возвращающая значения дерева с одинаковыми ключами
template<class T, class T1>
list<pair<T, T1>> same_keys(multimap<T, T1> m, T key)
{
    list<pair<T, T1>> res;
    for (typename multimap<T, T1>::iterator it_m = m.begin(); it_m != m.end(); it_m++)
    {
        if (it_m->first == key)
            res.push_back(*it_m);
    }
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

template<class T, class T1>
ostream& operator <<(ostream& s, pair<T, T1>& p)
{
    cout << "First: " << p.first << " Second: " << p.second << "\n";
    return s;
}

int main()
{
    multimap<string, int> p1;
    
    p1.emplace(string("Andrey Andreevich"), 8);
    p1.emplace(string("Ivanov Ivan"), 10); ; 
    p1.emplace(string("Ivanov Ivan"), 11);
    p1.emplace(string("Ivanov Ivan"), -6);
    p1.emplace(string("Petr Pavlovich"), 10);
    p1.emplace(string("Alexandr Smirnov"), 8);

    show(p1);

    list<int> l;

    string s = "Ivanov Ivan";

    l = key_search(p1, s);

    cout << l;

    multimap<string, int> p2;

    p2 = filter(p1, programmerlvl);

    show(p2);
}