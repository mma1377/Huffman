#include "Decoder.h"

void Decoder::DecodeSimpleCoded(std::string fileName, std::string outFileName)
{
	std::ifstream input;
	input.open(fileName, std::ios_base::in | std::ios_base::binary);
	std::ofstream output;
	output.open(outFileName, std::ios_base::out | std::ios_base::binary);

	char c;

	std::string codeword = "";
	std::string symbolStr = "";
	char symbol = '\0';
	std::map<std::string, char> codesTable;

	input >> codeword;

	while (codeword != "endList") {
		input >> symbolStr;

		if (symbolStr.length() == 1)
			input.get(symbol);
		else
			symbol = symbolStr[1];

		codesTable.insert(std::pair<std::string, char>(codeword, symbol));

		input >> codeword;
	}
	input.get(c);

	std::string encodedBitmapString = "";
	int count = 0;
	while (input.get(c)) {
		count++;
		for (int i = 7; i >= 0; --i) {
			encodedBitmapString += char((c & (1 << i)) ? '1' : '0');

			auto foundCode = codesTable.find(encodedBitmapString);
			if (foundCode != codesTable.end()) {
				output << foundCode->second;
				encodedBitmapString = "";
			}
		}
	}

	input.close();
	output.close();
}
