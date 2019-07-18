#include<string>
#include"piece.h"

Piece::Piece(Height h, Color c, Shape s, Top t) :
	h(h), c(c), s(s), t(t), used(0) {
}

bool Piece::compareHeight(const Piece &p) const {
	return(h == p.h);
}

bool Piece::compareColor(const Piece &p) const {
	return(c == p.c);
}

bool Piece::compareShape(const Piece &p) const {
	return(s == p.s);
}

bool Piece::compareTop(const Piece &p) const {
	return(t == p.t);
}

bool Piece::isUsed() const {
	return(used);
}

void Piece::setUsed(bool u) {
	used = u;
}

std::string Piece::toString() const {
	std::string str;
	if (h == SHORT) str = "S";
	else str = "T";
	if (c == BEIGE) str = str + "B";
	else str = str + "E";
	if (s == CIRCLE) str = str + "C";
	else str = str + "Q";
	if (t == HOLLOW) str = str + "H";
	else str = str + "O";
	return str;
}