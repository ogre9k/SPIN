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

	while (!tok.eof() && !tok.isCloseLoop()) {
		if (tok.isRegister()) {
			tokenizer.ungetToken();
			stmts->addStatement(targetStatement());
		}
		else if (tok.isSPIN()) {
			tokenizer.ungetToken();
			stmts->addStatement(simpleStatement());
		}
		else if (tok.isOpenLoop()) {
			tokenizer.ungetToken();
			stmts->addStatement(loopStatement());
		}
		else if (tok.isDebug()) {
			tokenizer.ungetToken();
			stmts->addStatement(debugStatement());
		}
		tok = tokenizer.getToken();
	}

	tokenizer.ungetToken();
	return stmts;
}

SimpleStatement *Parser::simpleStatement() {
	Token tok = tokenizer.getToken();
	if (!tok.isSPIN())
		die("Parser::simpleStatement", "Expcted a SPIN token, instead got", tok);

	return new SimpleStatement();
}

TargetStatement *Parser::targetStatement() {
	std::string target;
	std::string op;
	
	Token tok = tokenizer.getToken();
	if (!tok.isRegister())
		die("Parser::targetStatement", "Expected a register, instead got", tok);
	target = tok.symbol();

	tok = tokenizer.getToken();
	if (!tok.isDot())
		die("Parser::targetStatement", "Expected a period, instead got", tok);

	tok = tokenizer.getToken();
	if (!tok.isInstruction())
		die("Parser::targetStatement", "Expected an instruction, instead got", tok);
	op = tok.symbol();

	return new TargetStatement(target, op);
}

LoopStatement *Parser::loopStatement() {

	std::string start = "";
	std::string end = "";

	Token tok = tokenizer.getToken();
	if (!tok.isOpenLoop())
		die("Parser::loopStatement", "Expected an (, instead got", tok);

	// Check to see if this uses L or R
	tok = tokenizer.getToken();
	if (tok.isDot()) {
		tok = tokenizer.getToken();
		if (!tok.isRegister()) {
			die("Parser::loopStatement", "While parsing (.X, X wasn't a register. Was: ", tok);
		}
		start = tok.symbol();
	}
	else {
		tokenizer.ungetToken();
	}

	Parser parser(tokenizer);
	Statements *stmts = parser.statements();

	tok = tokenizer.getToken();
	if (!tok.isCloseLoop())
		die("Parser::loopStatement", "Expected an ), instead got", tok);

	// Check to see if this uses L or R
	tok = tokenizer.getToken();
	if (tok.isDot()) {
		tok = tokenizer.getToken();
		if (!tok.isRegister()) {
			die("Parser::loopStatement", "While parsing ).X, X wasn't a register. Was: ", tok);
		}
		end = tok.symbol();
	}
	else {
		tokenizer.ungetToken();
	}

	return new LoopStatement(stmts, start, end);
}

DebugStatement *Parser::debugStatement() {
	std::string op;
	int value;

	Token tok = tokenizer.getToken();
	if (!tok.isDebug())
		die("Parser::debugStatement", "Expected a debug command, got ", tok);
	op = tok.symbol();

	tok = tokenizer.getToken();
	if (op == "-dump" && !tok.isNumber())
		die("Parser::debugStatement", "Expected a number argument for -dump, got ", tok);
	value = tok.getNumber();

	return new DebugStatement(op, value);
}