#pragma once

#include <vector>

class Tape {
public:
	Tape(int size);

	void spin();
	int rotation();
	std::vector<int> &tape();
private:
	std::vector<int> _tape;
	int _rotation;
};

class Pointer {
public:
	Pointer();

	void spin();
	int rotation();

	int read();
	void write(int);
private:
	int _rotation;
};

class Buffer {
public:
	Buffer();

	void write();
	void read();
	void sub();
	void dub();
	void copy();
	void in();
	void out();

	int getValue();

private:
	int _value;
};