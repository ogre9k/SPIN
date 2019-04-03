#pragma once

#include <fstream>
#include <vector>
#include "Token.hpp"

class Tokenizer {

public:
	Tokenizer(std::istream &inStream);
	Token getToken();
	void ungetToken();
	void printProcessedTokens();
	Token lastToken;
private:
	bool ungottenToken;
	std::istream &inStream;
	std::vector<Token> _tokens;
	std::string readName();
};
