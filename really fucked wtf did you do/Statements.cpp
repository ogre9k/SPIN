#include "Statements.hpp"
void die(std::string where, std::string message, Token &token) {
	std::cout << where << " " << message << std::endl;
	token.print();
	std::cout << std::endl;
	exit(1);
}

// Statement
Statement::Statement(Token op): _op(op) {}

// Statements

Statements::Statements() {}
void Statements::addStatement(Statement *statement) { _statements.push_back(statement); }

void Statements::print() {
	for (auto s : _statements)
		s->print();
}

void Statements::evaluate() {
	for (auto s : _statements)
		s->evaluate();
}