#include "BinaryTreeNode.h"

namespace BinaryTree 
{
	Node::Node(Node* left, Node* right)
	{
		_leftChild = left;
		_rightChild = right;
		_leftChild->_parent = _parent;
		_rightChild->_parent = _parent;
		_parent = nullptr;
	}

	Node::Node()
	{
		_leftChild = nullptr;
		_rightChild = nullptr;
		_parent = nullptr;
	}

	bool Node::IsRoot()
	{
		return _parent == nullptr;
	}
}
