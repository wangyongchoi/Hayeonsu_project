#pragma once

template <class T>
class Wangyong_Queue : public Node<T> 
{
private:
	Node *mfront;
	Node *mrear;
	int length;

public:

	Wangyong_Queue() 
	{
		mfront = nullptr;
		mrear = nullptr;
		length = 0;
	}

	void push(T _data) 
	{
		length++;
		Node<T>* pNode = new Node<T>;
		pNode->data = _data;
		pNode->link = nullptr;

		if (mrear == nullptr) 
		{
			mfront = pNode;
			mrear = pNode;
			return;
		}

		mrear->link = pNode;
		mrear = pNode;
	}

	T pop() 
	{
		if (mrear == nullptr) return -1;

		length--;

		int _data = mfront->data;
		Node<T>* tempNode = mfront;
		mfront = mfront->link;
		delete tempNode;
		return _data;
	}

	T front() 
	{
		if (mfront == nullptr) return -1;
		return mfront->data;
	}

	bool empty() 
	{
		if (length == 0) return true;
		return false;
	}

	int size() {
		return length;
	}

	~Wangyong_Queue() {
		while (mfront != nullptr) {
			pop();
		}
	}
};