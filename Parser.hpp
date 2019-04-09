#pragma once

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "Memory.hpp"
#include "Statements.hpp"

#include<vector>
#include<iostream>

class Parser {
public:
	Parser(Tokenizer &tokenizer) : tokenizer{ tokenizer } {}

	Statements *statements();
	SimpleStatement *simpleStatement();
	TargetStatement *targetStatement();
	LoopStatement *loopStatement();
	DebugStatement *debugStatement();

private:
	Tokenizer &tokenizer;

	void die(std::string where, std::string message, Token &token);

};