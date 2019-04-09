#pragma once

#include <string>

class Token {

public:
	Token();

	// Set symbol
	void symbol(std::string c) { _symbol = c; }
	void symbol(char c) { _symbol = c; }
	void symbol(int c) { _number = c; }
	// Get symbol
	std::string symbol() { return _symbol; }
	// Get number
	int getNumber() { return _number; }

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
	
	//debug features
	bool isDebug() const { return _symbol[0] == '-'; }
	bool isDump() const { return _symbol == "-dump"; }
	bool isNumber() const { return _number != NULL; }

	//temporary features (will be removed / depreciated)
	bool isNeg() const { return _symbol == "neg"; } //this is TEMPORARY and will be removed

	bool isRegister() const { return isL() || isR(); }
	bool isInstruction() const { return isWrite() || isRead() || isSub() || isDub() || isCopy() || isIn() || isOut() || isNeg(); }

	void print() const;
private:
	std::string _symbol;
	int _number;
	bool _eof;
};