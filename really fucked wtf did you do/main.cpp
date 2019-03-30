#include <iostream>
#include <vector>
#include <string>
//#include "Memory.hpp"
//#include "Globals.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

//Buffer extern *L = new Buffer();
//Buffer extern *R = new Buffer();
//Tape extern *TAPE = new Tape(4);
//Pointer extern *POINTER = new Pointer();

int main(int argc, char *argv[]) {

	std::ifstream inputStream;

	inputStream.open("test.txt", std::ios::in);
	if (!inputStream.is_open()) {
		std::cout << "Unable to open " << argv[1] << ". Terminating...";
		perror("Error when attempting to open the input file.");
		exit(2);
	}

	Tokenizer tokenizer(inputStream);
	tokenizer.printProcessedTokens();
	//Parser parser(tokenizer);
	//Statements *statements = parser.statements();
	//tokenizer.printProcessedTokens();
	//statements->evaluate();

	return 0;
}
