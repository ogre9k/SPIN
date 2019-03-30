#pragma once

#include <vector>

class Tape {
public:
	Tape(int size);

	void spin();
	int rotation();
	std::vector<int> &tape();
	int read(int);
	void write(int, int);
private:
	std::vector<int> _tape;
	int _rotation;
	Tape *_next;
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
	void setValue(int val);

private:
	int _value;
};