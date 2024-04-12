#pragma once
#include <iostream>
#include <functional>

template <typename T> class LinkedList;

template <typename T> class LinkedListNode {

	friend LinkedList<T>; // :)

	LinkedListNode* Next{ nullptr };
	LinkedListNode* Prev{ nullptr };
	T Value;

public:

	LinkedListNode() = delete;

	LinkedListNode(T NewValue, LinkedListNode* NewNext, LinkedListNode* NewPrev)
		: Value(NewValue), Next(NewNext), Prev(NewPrev) { std::cout << "DEBUG: LL Created" << std::endl; }

	~LinkedListNode() { std::cout << "DEBUG: LL Deleted" << std::endl; }

	void SetValue(T NewValue) {
		Value = NewValue;
	}

	T GetValue() { return Value; }
};

template <typename T> class LinkedList {

	LinkedListNode<T>* Head{ nullptr };
	LinkedListNode<T>* Tail{ nullptr };
	size_t Size{ 0 };

public:

	LinkedList() = default;

	LinkedList(std::initializer_list<T> list) {
		for (const T& item : list) {
			Push(item);
		}
	}

	~LinkedList() {
		Empty();
	}

	size_t GetSize() {
		return Size;
	}

	void Push(T NewValue) {
		if (Head == nullptr) {
			Head = Tail = new LinkedListNode<T>(NewValue, nullptr, nullptr);
		}
		else {
				Tail->Next = new LinkedListNode<T>(NewValue, nullptr, Tail);
				Tail = Tail->Next;
		}
		++Size;
	}

	T Pop() {
		if (Size == 0) {
			throw std::out_of_range("List is empty!");
		}
		T value = Tail->Value;
		LinkedListNode<T>* prevNode = Tail->Prev;
		prevNode->Next = nullptr;
		delete Tail;
		Tail = prevNode;
		--Size;
		return value;
	}

	void Shift(T NewValue) {
		if (Head == nullptr) {
			Head = Tail = new LinkedListNode<T>(NewValue, nullptr, nullptr);
		}
		else { 
			Head->Prev = new LinkedListNode<T>(NewValue, Head, nullptr);
			Head = Head->Prev;
		}
		++Size;
	}

	T Unshift() {
		if (Size == 0) {
			throw std::out_of_range("List is empty!");
		}
		T value = Head->Value;
		LinkedListNode<T>* nextNode = Head->Next;
		nextNode->Prev = nullptr;
		delete Head;
		Head = nextNode;
		--Size;
		return value;
	}

	void InsertOnIndex(T NewValue, size_t index) {
		if (index >= Size) {
			throw std::out_of_range("Index is out of range!");
		}
		if (index == 0) {
			Push(NewValue);
		}
		else {
			LinkedListNode<T>* node = GetNodeByIndex(index);
			LinkedListNode<T>* nextNode = node->Next;
			node->Next = new LinkedListNode<T>(node->Value, nextNode, node);
			nextNode->Prev = node->Next;
			node->Value = NewValue;
		}
		++Size;
	}

	void OrderBy(std::function<bool(T, T)> comparator) {
		OrderByRecursive(comparator, Head, Tail);
	}

	void Empty() {
		LinkedListNode<T>* node = Head;
		while (node->Next != nullptr) {
			node = node->Next;
			delete node->Prev;
			--Size;
		}
		delete node;
		--Size;
	}
	T& operator[](size_t index) {
		LinkedListNode<T>* node = GetNodeByIndex(index);
		return node->Value;
	}

private:

	LinkedListNode<T>* GetNodeByIndex(size_t index) {
		if (index >= Size) {
			throw std::out_of_range("Index is out of range!");
		}
		LinkedListNode<T>* node = Head;
		for (size_t i = 0; i < index; ++i) {
			node = node->Next;
		}
		return node;
	}

	void OrderByRecursive(std::function<bool(T, T)> comparator, LinkedListNode<T>* begin, LinkedListNode<T>* end) {
		if (begin == nullptr || end == nullptr || begin == end) {
			return;
		}

		LinkedListNode<T>* pivot = begin;
		LinkedListNode<T>* current = begin->Next;
		bool beginSet = false;
		bool reachedEnd = false;

		while (current != nullptr && !reachedEnd) {
			if (current == end) {
				reachedEnd = true;
			}
			LinkedListNode<T>* nextNode = current->Next;
			if (comparator(current->Value, pivot->Value)) {
				current->Prev->Next = current->Next;
				if (current->Next != nullptr) {
					current->Next->Prev = current->Prev;
				}
				if (pivot->Prev != nullptr) {
					current->Prev = pivot->Prev;
					pivot->Prev->Next = current;
				}
				else {
					Head = current;
					current->Prev = nullptr;
				}
				pivot->Prev = current;
				current->Next = pivot;
				if (!beginSet) {
					begin = current;
					beginSet = true;
				}
			}
			current = nextNode;
		}

		if (pivot->Prev != nullptr) {
			OrderByRecursive(comparator, begin, pivot);
		}
		else {
			Head = pivot;
		}

		if (pivot->Next != nullptr) {
			OrderByRecursive(comparator, pivot->Next, end);
		}
		else {
			Tail = pivot;
		}
	}
};