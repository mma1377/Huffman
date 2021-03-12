#pragma once
#include <string>
#include <map>
#include <fstream>

class Decoder
{
public:
	static void DecodeSimpleCoded(std::string fileName, std::string outFileName);
	static void DecodeExtendedCoded(std::string fileName, std::string outFileName);
};
