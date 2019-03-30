#include<vector>
#include<iostream>

#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

// Parser functions
void Parser::die(std::string where, std::string message, Token &token) {
	std::cout << where << " " << message << std::endl;
	token.print();
	std::cout << std::endl;
	std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
	tokenizer.printProcessedTokens();
	int test;
	std::cin >> test;
	exit(1);
}

Statements *Parser::statements() {
	// This function is called when we KNOW that we are about to parse
	// a series of assignment statements.


	Statements *stmts = new Statements();
	Token tok = tokenizer.getToken();

	return stmts;
}