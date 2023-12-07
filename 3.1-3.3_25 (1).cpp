using namespace std;
#include <iostream>
#include <queue>
#include<list>


template<typename T>
void print_queue(T& q) {
	while (!q.empty()) {
		cout << q.top() << " ";
		q.pop();
	}
	std::cout << '\n';
}


template <class T>
class Node
{
private:
	T value;
public:
	Node(){}
	T getValue() { return value; }
	void setValue(T v) { value = v; }
	bool operator<(Node* N)
	{
		return (this->value < N->value);
	}
	bool operator>(Node* N)
	{
		return (this->value > N->value);
	}
	bool operator<( Node N)
	{
		return (value < N.getValue());
	}
	bool operator>( Node N)
	{
		return (value > N.getValue());
	}

	void print()
	{
		cout << value;
	}

	template <class T1>
	friend ostream& operator <<(ostream& s, Node<T1>* node);

};
template <class T>
ostream& operator <<(ostream& s, Node<T>* node)
{
	s << node->getValue() << "\n";
	return s;
}
template <class T>
void print(Node<T>* N)
{
	cout << N->getValue() << "\n";
}

/*template <class T>
bool operator >(Node<T> a, Node<T> b)
{
	return (a.getValue() > b.getValue()) ? 1 : 0;
}
template <class T>
bool operator <(Node<T> a, Node<T> b)
{
	return (a.getValue() < b.getValue()) ? 1 : 0;
}*/

template <class T>
class Heap
{
private:
	Node<T>*arr;
	int len;
	int size;
public:

	int getCapacity() { return size; }
	int getCount() { return len; }

	Node<T>& operator[](int index)
	{
		if (index < 0 || index >= len)
			return NULL;
		return arr[index];
	}

	Heap<T>(int MemorySize = 100)
	{
		arr = new Node<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}

	void Swap(int index1, int index2)
	{
		if (index1 <= 0 || index1 >= len)
			return;
		if (index2 <= 0 || index2 >= len)
			return;
		Node<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	void Copy(Node<T>* dest, Node<T>* source)
	{
		dest->setValue(source->getValue());
	}

	Node<T>* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			return -1;
		return &arr[index * 2 + 1];
	}
	Node<T>* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			return -1;
		return &arr[index * 2 + 2];
	}
	Node<T>* GetParent(int index)
	{
		if (index <= 0 || index >= len)
			return -1;
		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}

	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			return -1;
		return index * 2 + 1;
	}
	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			return -1;
		return index * 2 + 2;
	}
	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			return -1;
		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}

	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;
		int parent = GetParentIndex(index);
		int index2 = GetLeftChildIndex(parent);
		if (index2 == index) 
			index2 = GetRightChildIndex(parent);
		int max_index = index;
		if (index < len && index2 < len && parent >= 0)
		{
			if (arr[index] > arr[index2])
				max_index = index;
			if (arr[index] < arr[index2])
				max_index = index2;
		}
		if (parent < len && parent >= 0 && arr[max_index] > arr[parent])
		{
			Swap(parent, max_index);
			SiftUp(parent);
		}
	}

	void SiftDown(int index = 0)
	{
		if (index < 0 || index >= len)return;

		int right = GetRightChildIndex(index);
		int left = GetLeftChildIndex(index);

		if (left == right == -1)return;

		if (left == -1 && arr[index] < arr[right])
		{
			Swap(index, right);
			return SiftDown(right);
		}

		if (right == -1 && arr[index] < arr[left])
		{
			Swap(index, left);
			return SiftDown(left);
		}

		int min_index = (arr[right] < arr[left]) ? right : left;

		if (arr[index] < arr[min_index])
		{
			Swap(index, min_index);
			return SiftDown(min_index);
		}
		return;
	}

	template <class T>
	void push(T v)
	{
		Node<T>* N = new Node<T>;
		N->setValue(v);
		push(N);
	}
	template <class T>
	void push(Node<T>* N)
	{
		if (len < size)
		{
			Copy(&arr[len], N);
			len++; SiftUp();
		}
	}

	void Straight(void(*f)(Node<T>*))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}

	Node<T>* ExtractMax()
	{
		if (len <= 0)
			return NULL;
		Node<T>* res = new Node<T>;
		res->setValue(arr[0].getValue());
		Swap(0, len - 1);
		--len;
		SiftDown(0);
		return res;
	}

	Node<T>* Remove(int index)
	{
		if (index < 0 || index >= len)return NULL;
		Node<T>* res = new Node<T>;
		res->setValue(arr[index].getValue());
		Swap(index, len);
		len--;
		SiftUp(index);
		SiftDown(index);
	}

	void InOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}
};

template <class T>
class FibHeap;

template <class T>
class FibNode
{
private:
	int degree;
	T value;
	list<FibNode<T>*>* children;
public:
	FibNode() { degree = 0; }

	int getDegree() { return degree; }
	T getValue() { return value; }
	list<FibNode<T>>* getChildren() { return children; }
	void addChild(FibNode<T>* node)
	{
		children->push_back(node);
		degree++;
	}
	void addChild(T val)
	{
		FibNode* newelem = new FibNode;
		newelem->setValue(val);
		children->push_back(newelem);
		degree++;
	}

	void setValue(T val) { value = val; }

	~FibNode()
	{
		if (!children.empty())
		{
			for (typename list<FibNode<T>*>::iterator it = children.begin(); it != children.end(); it++)
				delete* it;
			delete children;
		}
	}
	template <class T1>
	friend ostream& operator<<(ostream& s, FibNode<T1> node);
	template <class T1>
	friend class FibHeap;
};

template <class T>
ostream& operator<<(ostream& s, FibNode<T> node)
{
	s << node.getValue() << "\n";
}

template <class T>
class FibHeap
{
protected:
	list<FibNode<T>*>* arr;
	int size;
	typename list<FibNode<T>*>::iterator max;
private:
	void addChild(FibNode<T>* parent, FibNode<T>* child)
	{
		if (parent == NULL || child == NULL)return;
		parent->addChild(child);
	}
	void addChild(FibNode<T>* parent, T value)
	{
		if (parent == NULL)return;
		parent->addChild(value);
	}
	FibNode<T>* singleton(T value)
	{
		Node<T>* newelem = new Node<T>;
		newelem->setValue(value);
		arr->push_back(newelem);
		return newelem;
	}
public:
	FibHeap()
	{
		size = 0;
	}

	FibNode<T>* merge(FibNode<T>* a, FibNode<T>* b)
	{
		if (a == NULL)return b;
		if (b == NULL)return a;
		if (a->getValue() < b->getValue())
		{
			FibNode<T>* temp = a;
			a = b;
			b = temp;
		}
		addChild(a, b);
		return a;
	}

	FibNode<T>* push(T value)
	{
		FibNode<T>* newelem = singleton(value);
		if (size == 0)
		{
			max = arr->begin();
			size++;
			return *max;
		}
		else
		{
			if (value > (*max)->value)
				max = arr->end();
			typename list<FibNode<T>*>::iterator tomerge = arr->end();
			tomerge--;
			size++;
			return merge(*max, *tomerge);
		}
	}

	FibNode<T>* ExtractMax()
	{
		if (size == 0)return NULL;

		FibNode<T>* res = *max;

		arr->erase(max);

		if (res->getDegree() == 0)return res;

		arr->insert(arr->end(), res->getChildren()->begin(), res->getChildren()->end());
		res->getChildren()->clear();
		res->getChildren() = NULL;

		FibNode<T>* trees[64] = {NULL};

		typename list<FibNode<T>*>::iterator it = arr->begin();

		while (true)
		{
			if (trees[(*it)->getDegree()] != NULL)
			{
				FibNode<T>* t = trees[(*it)->getDegree()];
				if (t == *it)break;
				trees[(*it)->getDegree()] = NULL;
				if ((*it)->getValue() > t->getValue())
					addChild((*it), t);
				else
				{
					addChild(t, (*it));
					*it = t;
				}
				continue;
			}
			else
			{
				trees[(*it)->getDegree()] = *it;
			}
			it++;
		}
		
		it = arr->begin();
		
		FibNode<T>* maxprior = it;
		for (it++; it != arr->end();it++)
		{
			FibNode<T>* current = it;
			if (current->getValue() > max->getValue())
				maxprior = current;
		}

		max = *maxprior;

		return res;
	}
};

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

	programmer() {}

	programmer(string surname, string name, string email, string skype, string telegram, string mainlanguage, string currentjob, int level)
	{
		if (level > 10 || level < 1)
		{
			level = -1;
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

	bool greaterp(programmer p)
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

	bool lesserp(programmer const& p)
	{
		if (lvl == p.lvl)
		{
			if (language == p.language)
			{
				if (sname == p.sname)
					return (n > p.n) ? 1 : 0;
				return (sname > p.sname) ? 1 : 0;
			}
			return(language > p.language) ? 1 : 0;
		}
		return (lvl < p.lvl) ? 1 : 0;
	}

	bool operator<(programmer const& p)
	{
		return this->lesserp(p);
	}

	bool operator>(programmer const& p)
	{
		return this->greaterp(p);
	}

	friend ostream& operator<<(ostream& s, programmer p);
};

bool operator >(programmer p, programmer other)
{
	return p.greaterp(other);
}

bool operator <(programmer p, programmer other)
{
	return p.lesserp(other);
}

ostream& operator<<(ostream& s, programmer p)
{
	s << p.lvl << " " << p.language << " " << p.sname << " " << p.n << "\n";
	return s;
}

int main()
{
	cout << "priority_queue:" << "\n";
	programmer a("aa", "aa", "aa", "aa", "aa", "aa", "aa", 10);
	programmer b("bb", "bb", "bb", "bb", "bb", "bb", "bb", 9);
	programmer c("cc", "cc", "cc", "cc", "cc", "cc", "cc", 10);
	programmer d("dd", "dd", "dd", "dd", "dd", "dd", "dd", 10);
	programmer e("ee", "ee", "ee", "ee", "ee", "ee", "ee", 10);
	programmer A("AA", "AA", "AA", "AA", "AA", "AA", "AA", 10);
	programmer B("BB", "BB", "BB", "BB", "BB", "BB", "BB", 7);

	priority_queue<programmer> q;

	q.push(a);
	q.push(b);
	q.push(c);
	q.push(d);
	q.push(e);
	q.push(A);
	q.push(B);

	print_queue(q);

}