#include"board.h"
#include"exceptions.h"
#include<iostream>

Board::Board() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			grid[i][j].setV((Vaxis)i);
			grid[i][j].setH((Haxis)j);
			grid[i][j].setPiece(nullptr);
		}
	}
}

Square & Board::getSquare(Vaxis v, Haxis h) {
	return grid[v][h];
}

Square & Board::getEmptySquare(Vaxis v, Haxis h) {
	if (grid[v][h].isEmpty()) return grid[v][h];
	else {
		SquareException  exp(grid[v][h], "not empty");
		throw exp;
	}
}

Square & Board::getEmptySquare(const std::string &s) {
	Vaxis v = (Vaxis)(s[0] - 65);
	Haxis h = (Haxis)(s[1] - 49);
	return getEmptySquare(v, h);
}

void Board::place(Piece &p, Square &sq) {
	sq.setPiece(&p);
}

static void Compare(const Piece& cand, const Piece& p, int& h, int& c, int& s, int& t) {
	if (cand.compareHeight(p)) h++;
	if (cand.compareColor(p)) c++;
	if (cand.compareShape(p)) s++;
	if (cand.compareTop(p)) t++;
}

bool Board::isWinning(const Piece &p, const Square &sq) {
	int h = 1, c = 1, s = 1, t = 1;
	for (int i = 0; i < N; i++) {//row
		if ((grid[sq.getV()][i]).isEmpty() && (i != sq.getH())) break;
		if (i != sq.getH()) {
			try {
				Piece cand = (grid[sq.getV()][i]).getPiece();
				Compare(cand, p, h, c, s, t);
			}
			catch (SquareException& exp){ continue; }
		}
	}
	if (h == 4 || c == 4 || s == 4 || t == 4) return true;
	h = 1, c = 1, s = 1, t = 1;
	for (int i = 0; i < N; i++) {//column
		if ((grid[i][sq.getH()]).isEmpty() && i != sq.getV()) break;
		if (i != sq.getV()) {
			try {
				Piece cand = (grid[i][sq.getH()]).getPiece();
				Compare(cand, p, h, c, s, t);
			}
			catch (SquareException& exp) { continue;}
		}
	}
	if (h == 4 || c == 4 || s == 4 || t == 4) return true;
	h = 1, c = 1, s = 1, t = 1;
	if (sq.isOnFirstDiagonal()) {//first diagonal
		for (int i = 0; i < N; i++) {
			if ((grid[i][i]).isEmpty() && i!=sq.getH()) break;
			if (i != sq.getH()) {
				try {
					Piece cand = (grid[i][i]).getPiece();
					Compare(cand, p, h, c, s, t);
				}
				catch (SquareException& exp) { continue; }
			}
		}
		if (h == 4 || c == 4 || s == 4 || t == 4) return true;
	}
	h = 1, c = 1, s = 1, t = 1;
	if (sq.isOnSecondDiagonal()) {//second diagonal
		for (int i = 0; i < N; i++) {
			if ((grid[i][3-i]).isEmpty() && i!=sq.getV()) break;
			if (i != sq.getV()) {
				try {
					Piece cand = (grid[i][3 - i]).getPiece();
					Compare(cand, p, h, c, s, t);
				}
				catch (SquareException& exp) { continue; }
			}
		}
		if (h == 4 || c == 4 || s == 4 || t == 4) return true;
	}
	return false;
}

std::string Board::toString() const {
	std::string str; int i = 0;
	std::string Vax[] = { "a","b","c","d" };
	str = "    1    2    3    4\n  +----+----+----+----+\n";
	for (int k = 0; k < 3*N; k++) {
		for (int j = 0; j < N; j++) {
			if (k % 3 == 0) {
				if(j==0)str = str + Vax[i];
				str = str + " | ";
				try {
					if (grid[i][j].isEmpty()) str = str + "  ";
					else str = str + grid[i][j].getPiece().toString().substr(0, 2);
				}
				catch (SquareException& exp) { continue; }
			}
			if ((k + 2) % 3 == 0) {
				if (j == 0) str = str + " ";
				str = str + " | ";
				try {
					if (grid[i][j].isEmpty()) str = str + "  ";
					else str = str + grid[i][j].getPiece().toString().substr(2, 2);
				}
				catch (SquareException& exp) { continue; }
			}
		}
		if((k+1)%3==0) i++;
		if(k%3==0 || (k+2)%3==0)str = str + " |\n";
		else str = str + "  +----+----+----+----+\n";
	}
	return str;
}
