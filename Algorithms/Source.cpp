#include <iostream>
#include <vector>
#include "Functions.h"
#include "BinaryTree.h"
#include "LinkedList.h"

struct User {
	unsigned int id;
	std::string name;

	User(const unsigned int& NewId, std::string NewName) {
		id = NewId;
		name = NewName;
	}
};

auto comparatorById = [](User Value, User NodeValue) {
	return Value.id < NodeValue.id;
	};

int main() {
	// Example of the OrderBy method usage
	LinkedList<User> list;
	list.Push(User(4, "Paco"));
	list.Push(User(2, "Karen")); 
	list.Push(User(6, "Juan"));
	list.Push(User(5, "Victor"));
	list.Shift(User(7, "Ana"));
	list.Push(User(1, "Nahomi"));
	list.Push(User(3, "Luis"));
	list.Push(User(0, "Rafael"));

	list.OrderBy(comparatorById);

	return 0;
}