#pragma once

#include <string>

class Token {

public:
	Token();

	// Set symbol
	void symbol(std::string c) { _symbol = c; }
	void symbol(char c) { _symbol = c; }
	// Get symbol
	std::string symbol() { return _symbol; }

	// Symbol checkers
	bool &eof() { return _eof; }
	bool eof() const { return _eof; }
	bool isSPIN() const { return _symbol == "SPIN"; }
	bool isL() const { return _symbol == "L"; }
	bool isR() const { return _symbol == "R"; }
	bool isDot() const { return _symbol == "."; }
	bool isWrite() const { return _symbol == "write"; }
	bool isRead() const { return _symbol == "read"; }
	bool isSub() const { return _symbol == "sub"; }
	bool isDub() const { return _symbol == "dub"; }
	bool isCopy() const { return _symbol == "copy"; }
	bool isIn() const { return _symbol == "in"; }
	bool isOut() const { return _symbol == "out"; }
	bool isOpenLoop() const { return _symbol == "("; }
	bool isCloseLoop() const { return _symbol == ")"; }

	bool isRegister() const { return isL() || isR(); }
	bool isInstruction() const { return isWrite() || isRead() || isSub() || isDub() || isCopy() || isIn() || isOut(); } // an "instruction" is anything after a .

	void print() const;
private:
	std::string _symbol;
	bool _eof;
};