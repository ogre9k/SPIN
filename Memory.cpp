
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
		
		/* This is the code to enable automatic memory allocation after a full 360 tape rotation
		/* I've disabled it because it's a pretty awful idea
		/* Might play around with it more
		if (_next == NULL) {
			_next = new Tape(360);
			_next->_parent = this;
		}
		else {
			_next->spin();
		}
		*/
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

void Tape::dumpTape(int limit) {
	std::cout << "\nDEBUG: DUMPING MEMORY FROM [0] TO [" << limit-1 << "]\n";
	for (int i = 0; i < limit; i++) {
		std::cout << "[" << i << "]: " << _tape[i] << std::endl;
	}
	std::cout << "DEBUG: END DUMP\n\n";
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
	if (debugMessages)
		std::cout << "Writing value (" << _value << ") from " << name << " onto the tape" << std::endl;
	POINTER->write(_value);
}

void Buffer::read() {
	_value = POINTER->read();
	if (debugMessages)
		std::cout << "Reading value (" << _value << ") into from tape " << name << std::endl;
}

void Buffer::sub() {
	if (debugMessages)
		std::cout << "Subbing value (" << _value << ") in " << name << std::endl;
	_value--;
}

void Buffer::dub() {
	if (debugMessages)
		std::cout << "Doubling value (" << _value << ") in " << name << std::endl;
	_value += _value;
}

void Buffer::copy() {
	if (this == L) {
		if (debugMessages)
			std::cout << "Copying value in L (" << _value << "into R" << std::endl;
		R->setValue(_value);
	}
	else {
		if (debugMessages)
			std::cout << "Copying value in R (" << _value << ") into L" << std::endl;
		L->setValue(_value);
	}
}

void Buffer::in() {
	if (debugMessages)
		std::cout << "Reading value " << "into " << name << std::endl;
	std::cin >> _value;
}

void Buffer::out() {
	if (debugMessages)
		std::cout << "Outputing value (" << _value << ") from " << name << std::endl;
	std::cout << _value << std::endl;
}

void Buffer::neg() {
	if (debugMessages)
		std::cout << "Neg'ing value (" << _value << ") in " << name << std::endl;
	_value = _value * -1;
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