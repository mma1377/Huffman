#include "BinaryTreeNode.h"

namespace BinaryTree 
{
	Node::Node(Node* left, Node* right)
	{
		_leftChild = left;
		_rightChild = right;
		_leftChild->_parent = this;
		_rightChild->_parent = this;
		_parent = nullptr;
		_rank = _leftChild->Rank() + _rightChild->Rank();
	}

	Node::Node()
	{
		_leftChild = nullptr;
		_rightChild = nullptr;
		_parent = nullptr;
		_rank = 0;
	}

	bool Node::IsRoot()
	{
		return _parent == nullptr;
	}

	int Node::Rank()
	{
		return _rank;
	}

	void Node::IncrementRank()
	{
		_rank++;
	}

	std::string Node::CreateCode()
	{
		if (this->IsRoot())
			return "";
		if (this == _parent->_leftChild)
			return _parent->CreateCode() + "0";
		return _parent->CreateCode() + "1";
	}
}
