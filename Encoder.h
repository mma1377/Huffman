#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Symbol.h"

class Encoder
{
private:
	char _version; // s:simple, e:extended, a:adaptive
	std::map<int, Symbol*> _symbols;
	std::map<std::pair<int, int>, Symbol2Char*> _symbols2Char;
	std::vector<BinaryTree::Node*> _leafsNodes;
	std::vector<BinaryTree::Node*> _internalNodes;
	std::string _rawData;
	std::string _fileExtension;
public:
	Encoder(std::string fileName, char version);
	void CalcualteCodewords();
	void Encode(std::string fileName);
};