#include <iostream>
#include "Encoder.h"
#include "Decoder.h"

void encode() {
	std::string inputFileName;
	std::string outputFileName;
	std::string encodingFormat;

	std::cout << "Enter file name:\n";
	std::cin >> inputFileName;
	std::cout << "Enter your desired extension: .sha(simple huffman algorithm, .eha(extended huffman algorithm)\n";
	std::cin >> encodingFormat;
	while (encodingFormat != ".sha" && encodingFormat != ".eha") {
		std::cout << "Invalid extension, try again:\n";
		std::cin >> encodingFormat;
	}
	std::cout << "Enter ouput file name without extension:\n";
	std::cin >> outputFileName;
	Encoder encoder(inputFileName, encodingFormat[1]);
	std::cout << "Calculation codewords...\n";
	encoder.CalcualteCodewords();
	std::cout << "Encoding...\n";
	encoder.Encode(outputFileName + encodingFormat);
}

void decode() {
	std::string inputFileName;
	std::string outputFileName;

	std::cout << "Enter file name:\n";
	std::cin >> inputFileName;
	char e1 = inputFileName[inputFileName.length() - 3];
	char e2 = inputFileName[inputFileName.length() - 2];
	char e3 = inputFileName[inputFileName.length() - 1];
	std::string extention = "";
	extention += e1;
	extention += e2;
	extention += e3;
	while (extention != "sha" && extention != "eha") {
		std::cout << "File format is invalid. Enter valid file name:\n";
		std::cin >> inputFileName;
		e1 = inputFileName[inputFileName.length() - 3];
		e2 = inputFileName[inputFileName.length() - 2];
		e3 = inputFileName[inputFileName.length() - 1];
		extention = "";
		extention += e1;
		extention += e2;
		extention += e3;
	}
	std::cout << "Enter ouput file name without extension:\n";
	std::cin >> outputFileName;
	std::cout << "Decoding...\n";
	if (extention == "sha")
		Decoder::DecodeSimpleCoded(inputFileName, outputFileName);
	else if (extention == "eha")
		Decoder::DecodeExtendedCoded(inputFileName, outputFileName);
}

int main() {

	int termination = 0;
	int decodeFlag;

	while (!termination) {

		std::cout << "Enter 0 to encode file or 1 to decode file:\n";
		std::cin >> decodeFlag;
		if (decodeFlag)
			decode();
		else
			encode();
		
		std::cout << "Job is done. Enter 1 to finish program or 0 to try something else:\n";
		std::cin >> termination;
	}

	return 0;
}