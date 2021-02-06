#include "Encoder.h"

Encoder::Encoder(std::string fileName, char version)
{
	_version = version;
	std::ifstream input;
	input.open(fileName, std::ios_base::in | std::ios_base::binary);

	char c;

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
	for (auto it = _symbols.begin(); it != _symbols.end(); ++it)
		it->second->CreateCode();
}

void Encoder::Encode(std::string fileName)
{
	std::ofstream output;
	output.open(fileName, std::ios_base::out | std::ios_base::binary);
	unsigned char buffer = 0;
	int bitCounter = 0;
	for (auto it = _symbols.begin(); it != _symbols.end(); ++it)
		output << it->second->Code() << " -" << (char)it->second->AsciiCode() << " ";
	output << "endList ";
	for (int i = 0; i < _rawData.length(); ++i) {
		std::string code = _symbols[(int)_rawData[i]]->Code();
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
