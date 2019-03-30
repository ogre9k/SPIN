#pragma once

#include <fstream>
#include <vector>
#include "Token.hpp"

class Tokenizer {

public:
	Tokenizer(std::ifstream &inStream);
	Token getToken();
	void ungetToken();
	void printProcessedTokens();

private:
	Token lastToken;
	bool ungottenToken;
	std::ifstream& inStream;
	std::vector<Token> _tokens;
	std::string readName();
};
