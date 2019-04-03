// SPIN version 1.2

#include <iostream>
#include <sstream>
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


	while (true) {
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		std::istringstream inputStream;
		inputStream.str(input);

		Tokenizer tokenizer(inputStream);
		Parser parser(tokenizer);
		Statements *statements = parser.statements();
		//statements->print();
		statements->evaluate();
	}

	return 0;
}
