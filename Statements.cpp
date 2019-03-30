#include "Statements.hpp"
void die(std::string where, std::string message) {
	std::cout << where << " " << message << std::endl;
	exit(1);
}

// Statement
Statement::Statement() {}

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

// SimpleStatement
SimpleStatement::SimpleStatement() {}

void SimpleStatement::evaluate() {
	POINTER->spin();
}

void SimpleStatement::print() {
	std::cout << "SPIN";
}

// TargetStatement
TargetStatement::TargetStatement(std::string target, std::string op): _target(target), _op(op) {}

void TargetStatement::evaluate() {
	Buffer *tar = NULL;
	if (_target == "L") {
		tar = L;
	}
	else if (_target == "R") {
		tar = R;
	}
	else {
		die("TargetStatement::evaluate", "invalid buffer specified, " + _target);
	}

	if (_op == "write")
		tar->write();
	else if (_op == "read")
		tar->read();
	else if (_op == "sub")
		tar->sub();
	else if (_op == "dub")
		tar->dub();
	else if (_op == "copy")
		tar->copy();
	else if (_op == "in")
		tar->in();
	else if (_op == "out")
		tar->out();
	else
		die("TargetStatement::evaluate", "invalid operation specified, " + _op);
}

void TargetStatement::print() {
	std::cout << _target << "." << _op;
}

// LoopStatement
LoopStatement::LoopStatement(Statements* statements) : _statements(statements) {}

void LoopStatement::evaluate() {
	while (POINTER->read() != 0) {
		_statements->evaluate();
	}
}

void LoopStatement::print() {
	std::cout << "(" << std::endl;
	_statements->print();
	std::cout << ")" << std::endl;
}