#include "Encoder.h"
#include <iostream>;

Encoder::Encoder(std::string fileName, char version)
{
	int dotIndex = 0;
	for (int i = fileName.length() - 1; i >= 0; --i) {
		if (fileName[i] == '.')
			dotIndex = i;
	}
	_fileExtension = fileName.substr(dotIndex, fileName.length() - dotIndex);

	_version = version;
	std::ifstream input;
	input.open(fileName, std::ios_base::in | std::ios_base::binary);

	char c;
	char c2;

	if (_version == 's') {
		_rawData = "";
		while (input.get(c)) {
			int symbolAscii = int(c);
			_rawData += c;
			auto currentSymbol = _symbols.find(symbolAscii);
			if (currentSymbol == _symbols.end()) {
				auto newSymbol = std::pair<int, Symbol*>(symbolAscii, new Symbol(symbolAscii));
				newSymbol.second->IncrementFrequency();
				_symbols.insert(newSymbol);
			}
			else
				currentSymbol->second->IncrementFrequency();
		}
		input.close();

		for (auto it = _symbols.begin(); it != _symbols.end(); ++it)
			_leafsNodes.push_back(it->second->Leaf());
		std::sort(_leafsNodes.begin(), _leafsNodes.end(),
			[](BinaryTree::Node* a, BinaryTree::Node* b) -> bool
			{
				return a->Rank() < b->Rank();
			});
	}
	else {
		_rawData = "";
		while (input.get(c)) {
			_rawData += c;
			if (!input.get(c2)) {
				c2 = (char)'\0';
			}
			_rawData += c2;
			auto symbolsAscii = std::make_pair((int)c, (int)c2);
			auto currentSymbol = _symbols2Char.find(symbolsAscii);
			if (currentSymbol == _symbols2Char.end()) {
				auto newSymbol = std::pair<std::pair<int, int>, Symbol2Char*>(symbolsAscii, new Symbol2Char((int)c, (int)c2));
				newSymbol.second->IncrementFrequency();
				_symbols2Char.insert(newSymbol);
			}
			else
				currentSymbol->second->IncrementFrequency();

		}
		input.close();

		for (auto it = _symbols2Char.begin(); it != _symbols2Char.end(); ++it)
			_leafsNodes.push_back(it->second->Leaf());
		std::sort(_leafsNodes.begin(), _leafsNodes.end(),
			[](BinaryTree::Node* a, BinaryTree::Node* b) -> bool
			{
				return a->Rank() < b->Rank();
			});
	}
}

void Encoder::CalcualteCodewords()
{
	auto itLeafs = _leafsNodes.begin();
	auto itInternals = _internalNodes.begin();
	int itInternalCounter = 0;
	BinaryTree::Node* firstNode;
	BinaryTree::Node* secondNode;
	BinaryTree::Node* root;
	while (itLeafs != _leafsNodes.end() || itInternals != _internalNodes.end()) {
		firstNode = nullptr;
		secondNode = nullptr;
		for (int i = 0; i < 2; ++i) {
			if (itInternals != _internalNodes.end() || itLeafs != _leafsNodes.end()) {
				if (itInternals == _internalNodes.end() || (itLeafs != _leafsNodes.end() && (*itLeafs)->Rank() < (*itInternals)->Rank())) {
					if (i == 0)
						firstNode = *itLeafs;
					else
						secondNode = *itLeafs;
					itLeafs++;
				}
				else {
					if (i == 0)
						firstNode = *itInternals;
					else
						secondNode = *itInternals;
					itInternals++;
					itInternalCounter++;
				}
			}
		}
		if (secondNode) {
			_internalNodes.push_back(new BinaryTree::Node(firstNode, secondNode));
			itInternals = _internalNodes.begin() + itInternalCounter;
		}
		else {
			root = firstNode;
		}
	}
	if (_version == 's') {
		for (auto it = _symbols.begin(); it != _symbols.end(); ++it)
			it->second->CreateCode();
	}
	else {
		for (auto it = _symbols2Char.begin(); it != _symbols2Char.end(); ++it)
			it->second->CreateCode();
	}
}

void Encoder::Encode(std::string fileName)
{
	std::ofstream output;
	output.open(fileName, std::ios_base::out | std::ios_base::binary);
	unsigned char buffer = 0;
	int bitCounter = 0;
	output << _fileExtension << " ";
	if (_version == 's'){
		for (auto it = _symbols.begin(); it != _symbols.end(); ++it)
			output << it->second->Code() << " -" << (char)it->second->AsciiCode() << " ";
	}
	else {
		for (auto it = _symbols2Char.begin(); it != _symbols2Char.end(); ++it)
			output << it->second->Code() << " -" << it->second->StringCode() << " ";
	}

	output << "endList ";
	int i = 0;
	for (i; i < _rawData.length(); ++i) {
		std::string code;
		if (_version == 's') {
			code = _symbols[(int)_rawData[i]]->Code();
		}
		else {
			auto index = std::make_pair((int)_rawData[i], (int)_rawData[i + 1]);
			code = _symbols2Char[index]->Code();
			i++;
		}
		for (int j = 0; j < code.length(); ++j) {

			buffer |= (code[j] == '1') << (7 - bitCounter);
			bitCounter++;
			if (bitCounter == 8)
			{
				output << buffer;
				buffer = 0;
				bitCounter = 0;
			}
		}
	}
	output.close();
}
