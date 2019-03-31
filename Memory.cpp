
#include "Memory.hpp"
#include "Globals.hpp"
#include <vector>
#include <iostream>

Tape extern *TAPE;
Pointer extern *POINTER;
Buffer extern *L;
Buffer extern *R;

// Tape

Tape::Tape(int size) : _tape(std::vector<int>(size, 0)), _rotation(0), _next(NULL), _parent(NULL) { _tape[0] = 1; }

void Tape::spin() {
	if (_rotation == 359) {
		_rotation = 0;
		if (_next == NULL) {
			_next = new Tape(360);
			_next->_parent = this;
		}
		else {
			_next->spin();
		}
	}
	else
		_rotation++;

	if (_parent == NULL)
		POINTER->spin();
	else
		_parent->spin();
}

int Tape::rotation() {
	return _rotation;
}

int Tape::read(int pointRot) {
	//std::cout << "Reading from " << (360+(pointRot - _rotation)) % 360 << std::endl;
	if (_rotation - pointRot == 0) {
		if (_next == NULL)
			return 1;
		else
			return _next->read(pointRot);
	}
	else
		return _tape[(360 + (pointRot - _rotation)) % 360];
}

void Tape::write(int pointRot, int val) {
	if (_rotation - pointRot == 0) {
		if (_next == NULL)
			return;
		else
			_next->write(pointRot, val);
	}
	else
		_tape[(360 + (pointRot - _rotation)) % 360] = val;
}
std::vector<int> &Tape::tape() {
	return _tape;
}

// Buffer
Buffer::Buffer(): _value(0) {}

int Buffer::getValue() {
	return _value;
}

void Buffer::setValue(int val) {
	_value = val;
}

void Buffer::write() {
	POINTER->write(_value);
}

void Buffer::read() {
	_value = POINTER->read();
}

void Buffer::sub() {
	_value--;
}

void Buffer::dub() {
	_value += _value;
}

void Buffer::copy() {
	if (this == L) {
		R->setValue(_value);
	}
	else {
		L->setValue(_value);
	}
}

void Buffer::in() {
	std::cin >> _value;
}

void Buffer::out() {
	std::cout << _value << std::endl;
}

// Pointer
Pointer::Pointer() : _rotation(0){}

void Pointer::spin() {
	if (_rotation == 359) {
		_rotation = 0;
		TAPE->spin();
	}
	else
		_rotation++;
}

int Pointer::rotation() {
	return _rotation;
}

int Pointer::read() {
	return TAPE->read(_rotation);
}

void Pointer::write(int val) {
	TAPE->write(_rotation, val);
}