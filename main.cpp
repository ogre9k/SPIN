#include <iostream>
#include "Tokenizer.hpp"


int main(int argc, char *argv[]) {

	std::ifstream inputStream;

	inputStream.open("test.txt", std::ios::in);
	if (!inputStream.is_open()) {
		std::cout << "Unable to open " << argv[1] << ". Terminating...";
		perror("Error when attempting to open the input file.");
		exit(2);
	}

	Tokenizer tokenizer(inputStream);
	while (!tokenizer.lastToken.eof())
		tokenizer.getToken();
	tokenizer.printProcessedTokens();

	return 0;
}
