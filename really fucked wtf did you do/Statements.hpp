#pragma once
#include <iostream>
#include <vector>
//#include "Memory.hpp"
#include "Token.hpp"
#include "Globals.hpp"
// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement {
public:
	Statement(Token op);

	virtual void print() = 0;
	virtual void evaluate() = 0;

protected:
	Token _op;
};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.

class Statements {
public:
	Statements();

	void addStatement(Statement *statement);
	void evaluate();
	void print();

private:
	std::vector<Statement *> _statements;
};
