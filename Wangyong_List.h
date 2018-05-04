#include <iostream>

template <typename T>
class Node
{
private:

public:
	T data;
	Node* link;
};

template <typename T>
class Wangyong_List
{
private:
	Node<T>* head;
	int length;
public:
	Wangyong_List()
	{
		head = new Node<T>;
		head->link = NULL;
		head->data = 0;
		length = 0;
	}

	Node<T>* createNode(T data)
	{
		Node<T> * newNode = new Node<T>;
		newNode->data = data;
		newNode->link = NULL;
		return newNode;
	}

	Node<T>* begin()
	{
		return head->link;
	}

	Node<T>* end()
	{
		Node<T>* pNode = begin();
		if (pNode != NULL)
		{
			while (pNode->link != NULL)
			{
				pNode = pNode->link;
			}
			return pNode;
		}
		else
		{
			return head;
		}
	}

	Node<T>* prev_node(Node<T>* pNode)
	{
		Node<T>* prevNode = head;
		Node<T>* curNode = head->link;
		while (curNode != NULL)
		{
			if (curNode->data == pNode->data)
			{
				return prevNode;
			}
			prevNode = prevNode->link;
			curNode = curNode->link;
		}
		return NULL;
	}

	Node<T>* find(T data)
	{
		for (Node<T>* pNode = begin();
			pNode != end();
			pNode = pNode->link)
		{
			if (pNode->data == data)
			{
				return pNode;
			}
		}
		return NULL;
	}

	void insert(Node<T>* pNode, T data)
	{
		Node<T>* newNode = createNode(data);
		newNode->link = pNode->link;
		pNode->link = newNode;
		length++;
	}

	void push_front(T data)
	{
		insert(head, data);
	}

	void push_back(T data)
	{
		insert(end(), data);
	}

	void erase(Node<T>* delNode)
	{
		if (delNode == NULL || length == 0)
		{
			return;
		}
		else {
			Node<T>* prevNode = prev_node(delNode);
			prevNode->link = delNode->link;
			delete delNode;
			length--;
		}
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(end());
	}

	void erase(T data)
	{
		erase(find(data));
	}

	int size()
	{
		return length;
	}

	void sort()
	{
		Node<T>* node1 = NULL;
		Node<T>* node2 = NULL;
		for (int i = 0; i < length - 1; ++i)
		{
			int count = 0;
			node1 = head->link;
			while (count < i)
			{
				node1 = node1->link;
				count++;
			}
			for (int j = i; j < length; ++j)
			{
				int count = 0;
				node2 = head->link;
				while (count < j)
				{
					node2 = node2->link;
					count++;
				}
				if (node1->data > node2->data)
				{
					//swap
					int temp = node1->data;
					node1->data = node2->data;
					node2->data = temp;
				}
			}
		}
	}

};
