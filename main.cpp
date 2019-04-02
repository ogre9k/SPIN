// SPIN version 1.2

#include <iostream>
#include "Tokenizer.hpp"
#include "Memory.hpp"
#include "Parser.hpp"
#include "Statements.hpp"
#include "Globals.hpp"

Buffer extern *L = new Buffer();
Buffer extern *R = new Buffer();
Tape extern *TAPE = new Tape(360);
Pointer extern *POINTER = new Pointer();

int main(int argc, char *argv[]) {

	std::ifstream inputStream;

	inputStream.open(argv[1], std::ios::in);
	if (!inputStream.is_open()) {
		std::cout << "Unable to open " << argv[1] << ". Terminating...";
		perror("Error when attempting to open the input file.");
		exit(2);
	}

	Tokenizer tokenizer(inputStream);
	Parser parser(tokenizer);
	Statements *statements = parser.statements();
	//statements->print();
	statements->evaluate();

	return 0;
}
