#pragma once
#include <string>

namespace BinaryTree 
{
	class Node
	{
	private:
		Node* _leftChild;
		Node* _rightChild;
		Node* _parent;
		int _rank;
	public:
		Node(Node* left, Node* right);
		Node();
		bool IsRoot();
		int Rank();
		void IncrementRank();
		std::string CreateCode();
	};
}