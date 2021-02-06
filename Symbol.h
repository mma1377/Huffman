#pragma once
#include "BinaryTreeNode.h"

class Symbol
{
private:
	int _symbolAscii;
	BinaryTree::Node* _leaf;
	std::string _code;
public:
	Symbol(int symbolAscii);
	void IncrementFrequency();
	int Frequency();
	int AsciiCode();
	BinaryTree::Node* Leaf();
	void CreateCode();
	std::string Code();
};