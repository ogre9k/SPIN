#pragma once
#include <iostream>
#include <vector>
#include "Memory.hpp"
#include "Token.hpp"
#include "Globals.hpp"
// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement {
public:
	Statement();

	virtual void print() = 0;
	virtual void evaluate() = 0;
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

class SimpleStatement: public Statement {
public:
	SimpleStatement();

	void evaluate();
	void print();
};

class TargetStatement : public Statement {
public:
	TargetStatement(std::string target, std::string op);

	void evaluate();
	void print();

private:
	std::string _target;
	std::string _op;
};

class LoopStatement : public Statement {
public:
	LoopStatement(Statements *statements);
	LoopStatement(Statements *statements, std::string start, std::string end);

	void evaluate();
	void print();

private:
	Statements *_statements;
	Buffer *_start;
	Buffer *_end;
};

class DebugStatement : public Statement {
public:
	DebugStatement(std::string op, int value);

	void evaluate();
	void print();
private:
	int _value;
	std::string _op;
};