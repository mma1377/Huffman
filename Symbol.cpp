#include "Symbol.h"

Symbol::Symbol(int symbolAscii)
{
	_symbolAscii = symbolAscii;
	_leaf = new BinaryTree::Node();
	_code = "";
}

void Symbol::IncrementFrequency()
{
	_leaf->IncrementRank();
}

int Symbol::Frequency()
{
	return _leaf->Rank();
}

int Symbol::AsciiCode()
{
	return _symbolAscii;
}

BinaryTree::Node* Symbol::Leaf()
{
	return _leaf;
}

void Symbol::CreateCode()
{
	_code = _leaf->CreateCode();
}

std::string Symbol::Code()
{
	return _code;
}
