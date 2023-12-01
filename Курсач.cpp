using namespace std;
#define NULL nullptr
#include <iostream>
template <class T>
class Node
{
private:

	T priority; //приоритет
	int rank; //ранг 
	Node* child; //указатель на самого левого ребенка
	Node* right; //указатель на правого брата, либо на следующий корень, если текущий узел является корнем
	Node* left; // указатель на левого брата , либо на родителя, если текущий узел самый левый, либо null, если текущий узел корень

public:

	Node() { rank = 0; child = right = left = NULL; }
	Node(T priority_) { priority = priority_; rank = 0; child = right = left = NULL; }
	//~Node() { child = right = left = NULL; rank = -1; }
	T getPriority() { return priority; }
	int getRank() { return rank; }
	Node* getChild() { return child; }
	Node* getRight() { return right; }
	Node* getLeft() { return left; }

	T setPriority(T priority_) { priority = priority_; return priority_; }
	int setRank(int rank_) { rank = rank_; return rank_; }
	Node* setChild(Node* child_) { child = child_; return child; }
	Node* setRight(Node* right_) { right = right_; return right; }
	Node* setLeft(Node* left_) { left = left_; return left; }

	bool isThin()
	{
		if (getRank() == 0)return 0;
		if (getChild() == NULL)return 1;
		return (getRank() - getChild()->getRank() == 2 ? 1 : 0);
	}
};

template <class T>
class thinheap
{
public:
	Node<T>* first; //указатель на корень с максимальным приоритетом
	Node<T>* last; //указатель на последний корень

	thinheap() { first = last = NULL; }
	~thinheap() { first = last = NULL; }

	Node<T>* getMax() { return first; }

	Node<T>* insert(Node<T>* newnode_)
	{
		if (newnode_ == NULL)return NULL;
		
		if (first == NULL)
			first = last = newnode_;
		else
		{
			if (newnode_->getPriority() > first->getPriority())
			{
				newnode_->setRight(first);
				first = newnode_;
			}
			else
			{
				last->setRight(newnode_);
				last = newnode_;
				newnode_->setRight(NULL);
			}
		}
		
		return newnode_;
	}

	Node<T>* insert(T priority_)
	{
		Node<T>* newnode = new Node<T>;
		newnode->setPriority(priority_);
		return insert(newnode);
	}

	thinheap merge(thinheap heap_)
	{
		if (first->getPriority() > heap_.first->getPriority())
		{
			last->setRight(heap_.first);
			last = heap_.last;
		}
		else
		{
			heap_.last->setRight(first);
			first = heap_.first;
		}
		return *this;
	}

	Node<T>* extractMax()
	{
		//удаляем из корневого списка узел с максимальным приоритетом, после чего добавляем в корневой список всех его детей, и понижаем ранг всех "тонких" детей
		Node<T>* res = first;
		Node<T>* cur = res->getChild();
		while (cur != NULL)
		{
			Node<T>* next = cur->getRight();
			if (cur->isThin())
				cur->setRank(cur->getRank() - 1);
			cur->setLeft(NULL);
			cur->setRight(NULL);
			insert(cur);
			cur = next;
		}
		cur = res->getRight();
		//создаем массив из указателей на узлы i-й элемент которого будет хранить тонкое дерево ранга i
		Node<T>* nodes[64] = { NULL };
		int max_rank = -1;
		//заполняем массив узлами из корневого списка, сливая деревья одинакового ранга. int max_rank нужен для ограничения перебора всех элементов массива
		while (cur != NULL)
		{
			Node<T>* next = cur->getRight();
			while (nodes[cur->getRank()] != NULL)
			{
				if (cur->getPriority() < nodes[cur->getRank()]->getPriority()) std::swap(cur, nodes[cur->getRank()]);
				nodes[cur->getRank()]->setLeft(cur);
				if (cur->getChild() != NULL)
				{
					nodes[cur->getRank()]->setRight(cur->getChild());
					cur->getChild()->setLeft(nodes[cur->getRank()]);
				}
				else
					nodes[cur->getRank()]->setRight(NULL);
				cur->setChild(nodes[cur->getRank()]);
				nodes[cur->getRank()] = NULL;
				cur->setRank(cur->getRank() + 1);
				cur->setRight(NULL);
			}
			if (cur->getRank() > max_rank)
				max_rank = cur->getRank();
			nodes[cur->getRank()] = cur;
			cur = next;
		}
		//обнуляем указатели на первый и последний узлы корневого списка, после чего добавляем в него все тонкие деревья из массива nodes
		first = last = NULL;
		for (int i = 0; i <= max_rank; i++)
		{
			insert(nodes[i]);
		}
		return res;
	}

	//поиск квантилей?

	Node<T>* changePriority(Node<T>* node_, T newpriority_)
	{
		node_->setPriority(newpriority_);
		if (node_->getLeft() != NULL)
		{
			Node<T>* left = node_->getLeft();
			if (node_->getLeft()->getChild() == node_)
			{
				if (node_->getRight() == NULL)
					node_->getLeft()->setChild(NULL);
				else
				{
					node_->getLeft()->setChild(node_->getRight());
					node_->getRight()->setLeft(node_->getLeft());
				}
			}
			else
			{
				if (node_->getRight() == NULL)
					node_->getLeft()->setRight(NULL);
				else
				{
					node_->getLeft()->setRight(node_->getRight());
					node_->getRight()->setLeft(node_->getLeft());
				}
			}
			while (sibling_violation(left) && child_violation(left))
			{
				if (sibling_violation(left))
				{
					if (left->isThin())
					{
						left->setRank(left->getRank() - 1);
						left = left->getLeft();
					}
					else
					{
						if (left->getRight()->getRight() != NULL)
							left->getRight()->getRight()->setLeft(left);
						left->getLeft()->setChild(left->getRight());
						left->getRight()->setLeft(left->getLeft());
						left->setLeft(left->getRight());
						left->setRight(left->getLeft()->getRight());
						left->getLeft()->setRight(left);
					}
				}
				else
				{
					Node<T>* newviolation = left->getLeft();
					left->setRank(left->getRank() - 2);
					if (left->getLeft()->getChild() != left)
					{
						left->getLeft()->setRight(left->getRight());
						left->getRight()->setLeft(left->getLeft());
					}
					else
					{
						if (left->getRight() != NULL)
							left->getRight()->setLeft(left->getLeft());
						left->getLeft()->setChild(left->getRight());
					}
					left->setLeft(NULL);
					left->setRight(NULL);
					insert(left);
					left = newviolation;
				}
			}
		}
		node_->setLeft(NULL);
		node_->setRight(NULL);
		insert(node_);
		if (node_->isThin())
			node_->setRank(node_->getRank() - 1);
		return node_;
	}

	bool sibling_violation(Node<T>* node_)
	{
		if (node_->getRight() == NULL && node_->getRank() == 1)return 1;
		if (node_->getRight() != NULL && node_->getRight()->getRank() + 2 == node_->getRank())return 1;
		return 0;
	}

	bool child_violation(Node<T>* node_)
	{
		if (node_->getRank() == 2 && node_->getChild() == NULL)return 1;
		if (node_->getChild() != NULL && node_->getChild()->getRank() + 3 == node_->getRank())return 1;
		return 0;
	}
};

int main()
{
	thinheap<int> h;
	h.insert(25);
	h.insert(24);
	h.insert(22);
	h.insert(2);
	h.insert(45);
	h.insert(8);
	h.insert(555);

	thinheap<int> b;
	b.insert(45);
	b.insert(63);
	b.insert(111);
	b.insert(555);
	b.insert(943);
	Node<int>* aa = b.insert(0);
	b.insert(54);

	thinheap<int> a = h.merge(b);




	a.changePriority(aa, -227);

	for (int i = 1; a.getMax() != NULL; i++)
		cout << a.extractMax()->getPriority() << " ";
}