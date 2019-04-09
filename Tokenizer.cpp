#include <iostream>
#include <string>
#include "Tokenizer.hpp"
#include <ctype.h>

bool extern debugFeatures;

bool isInstruction(char c) {
	return (c == 'L' || c == 'R' || c == '.' || c == '(' || c == ')' || c == 'S' || c == 'w' || c == 'r' || c == 's' || c == 'd' || c == 'c' || c == 'i' || c == 'o');
}

Tokenizer::Tokenizer(std::ifstream &stream) : ungottenToken{ false }, inStream{ stream }, lastToken{} {}

std::string Tokenizer::readName() {
	// This function is called when it is known that
	// the first character in input is an alphabetic character.
	// The function reads and returns all characters of the name.

	std::string name;
	char c;
	while (inStream.get(c) && isalnum(c)) {
		name += c;
	}
	if (inStream.good())  // In the loop, we have read one char too many.
		inStream.putback(c);
	return name;
}

std::string Tokenizer::readDebug() {
	// This function is called when it is known that
	// the first character in input is an alphabetic character.
	// The function reads and returns all characters of the name.

	std::string name;
	char c;
	inStream.get(c);
	name += c;
	while (inStream.get(c) && isalpha(c)) {
		name += c;
	}
	if (inStream.good())  // In the loop, we have read one char too many.
		inStream.putback(c);
	return name;
}

int Tokenizer::readNumber() {
	// This function is called when it is known that
	// the first character in input is a digit.
	// The function reads and returns all remaining digits.

	int intValue = 0;
	char c;
	while (inStream.get(c) && isdigit(c)) {
		intValue = intValue * 10 + c - '0';
	}
	if (inStream.good())  // In the loop, we have read one char too many.
		inStream.putback(c);
	return intValue;
}

Token Tokenizer::getToken() {

	if (ungottenToken) {
		ungottenToken = false;
		return lastToken;
	}

	char c;
	std::string name;

	Token token;
	// Skip leading whitespace
	while (inStream.get(c) && isspace(c)) {
		;
	}

	// If we see a comment specifier
	while (c == '#') {
		// Skip rest of line
		while (inStream.get(c) && (c != '\n'))
			;
		// Skip leading whitespace
		while (inStream.get(c) && isspace(c))
			;
	}


	if (inStream.eof())
		token.eof() = true;
	else if (c == 'L' || c == 'R' || c == '.' || c == '(' || c == ')')
		token.symbol(c);
	else if (c == 'S' || c == 'w' || c == 'r' || c == 's' || c == 'd' || c == 'c' || c == 'i' || c == 'o' || c == 'n') {
		inStream.putback(c);
		token.symbol(readName());
	}
	else if (c == '-') {
		inStream.putback(c);
		token.symbol(readDebug());
	}
	else if (isdigit(c)) {
		inStream.putback(c);
		token.symbol(readNumber());
	}
	else {
		std::cout << "Unknown character in input";
		printProcessedTokens();
		exit(1);
	}
	_tokens.push_back(token);
	return lastToken = token;
}

void Tokenizer::ungetToken() {
	ungottenToken = true;
}

void Tokenizer::printProcessedTokens() {
	for (auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
		iter->print();
	}
}