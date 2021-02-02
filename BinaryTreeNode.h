#pragma once

namespace BinaryTree 
{
	class Node
	{
	private:
		Node* _leftChild;
		Node* _rightChild;
		Node* _parent;
	public:
		Node(Node* left, Node* right);
		Node();
		bool IsRoot();
	};
}