#include <iostream>
#include "Token.hpp"


Token::Token() : _symbol("\0"), _eof(false) {}

void Token::print() const {
	if (eof()) std::cout << "EOF";
	else if (isL()) std::cout << "L";
	else if (isR()) std::cout << "R";
	else if (isDot()) std::cout << ".";
	else if (isWrite()) std::cout << "writen";
	else if (isRead()) std::cout << "read\n";
	else if (isSub()) std::cout << "sub\n";
	else if (isDub()) std::cout << "dub\n";
	else if (isCopy()) std::cout << "copy\n";
	else if (isIn()) std::cout << "in\n";
	else if (isOut()) std::cout << "out\n";
	else if (isOpenLoop()) std::cout << "(\n";
	else if (isCloseLoop()) std::cout << ")\n";
	else if (isSPIN()) std::cout << "SPIN\n";
	else if (isNeg()) std::cout << "neg\n";
	else std::cout << "Uninitialized token.\n";
}