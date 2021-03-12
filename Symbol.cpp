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

Symbol2Char::Symbol2Char(int symbolAscii1, int symbolAscii2)
{
	_symbolsAscii = std::make_pair(symbolAscii1, symbolAscii2);
	_leaf = new BinaryTree::Node();
	_code = "";
}

void Symbol2Char::IncrementFrequency()
{
	_leaf->IncrementRank();
}

int Symbol2Char::Frequency()
{
	return _leaf->Rank();
}

std::string Symbol2Char::StringCode()
{
	std::string retVal;
	retVal = (char)_symbolsAscii.first;
	retVal += (char)_symbolsAscii.second;
	return retVal;
}

BinaryTree::Node* Symbol2Char::Leaf()
{
	return _leaf;
}

void Symbol2Char::CreateCode()
{
	_code = _leaf->CreateCode();
}

std::string Symbol2Char::Code()
{
	return _code;
}
