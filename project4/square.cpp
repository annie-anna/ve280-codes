#include"square.h"
#include"exceptions.h"
#include<cstring>
#include<iostream>

Square::Square(Vaxis v, Haxis h): v(v),h(h), p(nullptr) {
}

Vaxis Square::getV() const {
	return v;
}

void Square::setV(Vaxis v) {
	this->v = v;
}

Haxis Square::getH() const {
	return h;
}

void Square::setH(Haxis h) {
	this->h = h;
}

const Piece & Square::getPiece() const {
	if (!isEmpty()) return (*p);
	else {
		SquareException exp(*this, "empty");
		throw exp;
	}

}

void Square::setPiece(const Piece *p) {
	this->p = p;
}

bool Square::isEmpty() const {
	return(p == nullptr);
}

bool Square::isOnFirstDiagonal() const {
	return((int)v == (int)h);
}

bool Square::isOnSecondDiagonal() const {
	return(v == 3 - h);
}

std::string Square::toString() const {
	const std::string Vax[] = { "A","B","C","D" };
	const std::string Hax[] = { "1","2","3","4" };
	std::string str = Vax[(int)v] + Hax[(int)h];
	return str;
}