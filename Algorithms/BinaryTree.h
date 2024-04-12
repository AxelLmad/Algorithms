#pragma once

enum class BinaryTreeNodeSide {
	Root,
	LeftChild,
	RightChild,
};

template <typename T> class BinaryTreeNode {

	T Value;
	BinaryTreeNode* Parent { nullptr };
	BinaryTreeNode* Left { nullptr };
	BinaryTreeNode* Right { nullptr };;
	BinaryTreeNodeSide NodeSide;

public:

	BinaryTreeNode() = delete;

	BinaryTreeNode(T NewValue, BinaryTreeNode* NewParent, BinaryTreeNodeSide NewNodeSide) {
		Value = NewValue;
		Parent = NewParent;
		NodeSide = NewNodeSide;
	}

	void SetValue(T NewValue) { Value = NewValue; }

	void SetParent(BinaryTreeNode* NewParent) { Parent = NewParent; }

	void SetLeft(BinaryTreeNode* NewLeft) { Left = NewLeft; }

	void SetRight(BinaryTreeNode* NewRight) { Right = NewRight; }

	void SetNodeSide(BinaryTreeNodeSide NewNodeSide) { NodeSide = NewNodeSide; }

	T GetValue() { return Value; }

	BinaryTreeNode* GetLeft() { return Left; }

	BinaryTreeNode* GetRight() { return Right; }

	BinaryTreeNode* GetParent() { return Parent; }

	BinaryTreeNodeSide GetNodeSide() { return NodeSide; };
};

template <typename T> class BinaryTree {

	BinaryTreeNode<T>* Root;

public:

	BinaryTree(std::initializer_list<T> list) {
		for (const T& item : list) {
			Insert(item);
		}
	}

	~BinaryTree() {
		Empty();
	}

	void Insert(T NewValue) {
		InsertRecursive(Root, NewValue);
	}

	void Empty() {
		if (Root != nullptr) {
			EmptyRecursive(Root);
		}
	}

	bool Contains(T Value) {
		return SearchRecursive(Root, Value) != nullptr;
	}

	void Delete(T Value) {
		BinaryTreeNode<T>* node = SearchRecursive(Root, Value);
		if (node == nullptr) {
			return;
		}
		bool hasLeftChild = node->GetLeft() != nullptr;
		bool hasRightChild = node->GetRight() != nullptr;
		auto nodeSide = node->GetNodeSide();

		if (!hasLeftChild && !hasRightChild) {
			if (nodeSide == BinaryTreeNodeSide::LeftChild) {
				node->GetParent()->SetLeft(nullptr);
			} 
			else if (nodeSide == BinaryTreeNodeSide::RightChild) {
				node->GetParent()->SetRight(nullptr);
			}
		}
		else if (hasLeftChild && !hasRightChild) {
			BinaryTreeNode<T>* leftChild = node->GetLeft();
			leftChild->SetNodeSide(nodeSide);
			if (nodeSide == BinaryTreeNodeSide::LeftChild) {
				leftChild->SetParent(node->GetParent());
				node->GetParent()->SetLeft(leftChild);
			}
			else if (nodeSide == BinaryTreeNodeSide::RightChild) {
				leftChild->SetParent(node->GetParent());
				node->GetParent()->SetRight(leftChild);
				}
				else if (nodeSide == BinaryTreeNodeSide::Root) {
					Root = leftChild;
				}
			} 
			else if (!hasLeftChild && hasRightChild) {
				BinaryTreeNode<T>* rightChild = node->GetRight();
				rightChild->SetNodeSide(nodeSide);
				if (nodeSide == BinaryTreeNodeSide::LeftChild) {
					rightChild->SetParent(node->GetParent());
					node->GetParent()->SetLeft(rightChild);
				}
				else if (nodeSide == BinaryTreeNodeSide::RightChild) {
					rightChild->SetParent(node->GetParent());
					node->GetParent()->SetRight(rightChild);
				}
					else if (nodeSide == BinaryTreeNodeSide::Root) {
						Root = rightChild;
					}
			}
			else {
				BinaryTreeNode<T>* searchNode = node;
				searchNode = traverseToRightLeaf(searchNode);
				if (searchNode != node) {
					T auxValue = searchNode->GetValue();
					searchNode->SetValue(node->GetValue());
					node->SetValue(auxValue);
					if (searchNode->GetNodeSide() == BinaryTreeNodeSide::LeftChild) {
						searchNode->GetParent()->SetLeft(nullptr);
					}
					else if (searchNode->GetNodeSide() == BinaryTreeNodeSide::RightChild) {
						searchNode->GetParent()->SetRight(nullptr);
					}
					AdjustSwappedNode(node);
					node = searchNode;
				}

			}
		delete node;
	}

private:
	void InsertRecursive(BinaryTreeNode<T>* node, T NewValue) {
		if (node == nullptr) {
			Root = new BinaryTreeNode<T>(NewValue, nullptr, BinaryTreeNodeSide::Root);
			Root->SetValue(NewValue);
		}
		else {
			if (NewValue < node->GetValue()) {
				if (node->GetLeft() == nullptr) {
					BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(NewValue, node, BinaryTreeNodeSide::LeftChild);
					node->SetLeft(newNode);
				}
				else {
					InsertRecursive(node->GetLeft(), NewValue);
				}
			}
			else {
				if (node->GetRight() == nullptr) {
					BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(NewValue, node, BinaryTreeNodeSide::RightChild);
					node->SetRight(newNode);
				}
				else {
					InsertRecursive(node->GetRight(), NewValue);
				}
			}
		}
	}

	void EmptyRecursive(BinaryTreeNode<T>* node) {
		if (node->GetLeft() != nullptr) {
			EmptyRecursive(node->GetLeft());
		}
		else {
			if (node->GetRight() != nullptr) {
				EmptyRecursive(node->GetRight());
			}
			else {
				BinaryTreeNode<T>* parentNode = node->GetParent();
				auto nodeSide = node->GetNodeSide();
				delete node;
				if (nodeSide != BinaryTreeNodeSide::Root) {
					if (nodeSide == BinaryTreeNodeSide::LeftChild) {
						parentNode->SetLeft(nullptr);
					}
					else {
						parentNode->SetRight(nullptr);
					}
					EmptyRecursive(parentNode);
				}
			}
		}
	}

	BinaryTreeNode<T>* SearchRecursive(BinaryTreeNode<T>* node, T Value) {
		if (node->GetValue() == Value) {
			return node;
		}
		else {
			if (Value < node->GetValue()) {
				if (node->GetLeft() != nullptr) {
					return SearchRecursive(node->GetLeft(), Value);
				}
				else {
					return nullptr;
				}
			}
			else {
				if (node->GetRight() != nullptr) {
					return SearchRecursive(node->GetRight(), Value);
				}
				else {
					return nullptr;
				}
			}
		}
	}

	BinaryTreeNode<T>* traverseToRightLeaf(BinaryTreeNode<T>* searchNode) {

		if (searchNode->GetLeft() == nullptr && searchNode->GetRight() == nullptr) {
			return searchNode;
		}

		if (searchNode->GetRight() != nullptr) {
			return traverseToRightLeaf(searchNode->GetRight());
		}
		else {
			return traverseToRightLeaf(searchNode->GetLeft());
		}
	}

	void AdjustSwappedNode(BinaryTreeNode<T>* node) {
		if (BinaryTreeNode<T>* rightNode = node->GetRight()) {
			if (node->GetValue() > rightNode->GetValue()) {
				T auxValue = rightNode->GetValue();
				rightNode->SetValue(node->GetValue());
				node->SetValue(auxValue);
				AdjustSwappedNode(rightNode);
			}
		}
		else if (BinaryTreeNode<T>* leftNode = node->GetLeft()) {
			if (node->GetValue() < leftNode->GetValue()) {
				T auxValue = leftNode->GetValue();
				leftNode->SetValue(node->GetValue());
				node->SetValue(auxValue);
				AdjustSwappedNode(leftNode);
			}
			else {
				return;
			}
		}

	}
};