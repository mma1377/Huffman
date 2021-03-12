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

class Symbol2Char
{
private:
	std::pair<int, int> _symbolsAscii;
	BinaryTree::Node* _leaf;
	std::string _code;
public:
	Symbol2Char(int symbolAscii1, int symbolAscii2);
	void IncrementFrequency();
	int Frequency();
	std::string StringCode();
	BinaryTree::Node* Leaf();
	void CreateCode();
	std::string Code();
};