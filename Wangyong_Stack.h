#pragma once

template<class T>
class Wangyong_Stack {
private:
	Node<T>* pTop;
	int count;
public:
	Wangyong_Stack() {
		pTop = nullptr;
		count = 0;
	}
	void push(T _data) {
		Node<T>* pNode = new Node<T>;
		pNode->data = _data;
		pNode->link = pTop;
		pTop = pNode;
		count++;
	}
	T pop() {
		if (pTop == nullptr) return -1;

		T data = pTop->data;
		Node<T>* pNode = pTop->link;
		delete pTop;
		pTop = pNode;
		count--;
		return data;
	}
	T top() {
		if (pTop == nullptr) return -1;
		return pTop->data;
	}
	bool empty() {
		if (pTop == nullptr)
			return true;
		return false;
	}
	int size() {
		return count;
	}
	~Wangyong_Stack() {
		while (empty() == false)
			pop();
	}
};