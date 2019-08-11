#include"pool.h"
#include"exceptions.h"
#include<cstring>
#include<iostream>

static void DecToBin(int n,int* bin, int size) {
    int i = size-1;
	while (n != 0) {
		bin[i] = n % 2;
		n = n / 2;
		i--;
	}
}

static int BinToDec(int a[],int size) {
	int dec=0;
	for (int i = 0; i < size-1; i++) {
		dec = (dec + a[i]) * 2;
	}
	dec = dec + a[size - 1];
	return dec;
}

Piece & Pool::getUnusedPiece(int index) {
	if (!pieces[index].isUsed()) return pieces[index];
	else {
		UsedPieceException exp(pieces[index]);
		throw exp;
	}
}

Pool::Pool() {
	for (int i = 0; i < NP; i++) {
		int bin[N] = { 0 };
		DecToBin(i,bin,N);
		Piece p((Height)(*bin), (Color)(*(bin + 1)), (Shape)(*(bin+2)), (Top)(*(bin+3)));
		pieces[i] = p;
	}
}

Piece & Pool::getUnusedPiece(Height h, Color c, Shape s, Top t) {
	int b[N] = { (int)h, (int)c, (int)s, (int)t };
	return getUnusedPiece(BinToDec(b, N));
}

Piece & Pool::getUnusedPiece(const std::string &in) {
	int bin[4] = { 0 };
	bin[0] = (in[0] == HCODE[1]);
	bin[1] = (in[1] == CCODE[1]);
	bin[2] = (in[2] == SCODE[1]);
	bin[3] = (in[3] == TCODE[1]);
	return getUnusedPiece(BinToDec(bin, N));
}

std::string Pool::toString() const {
	int flag = 0, j = 0; Piece p; std::string str;
	for (int i = 0; i < NP; i++) {
		if (!pieces[i].isUsed()) {
			if(!flag){
				str = "Available:\n";
				flag = 1;
			}
			if(j < NP)str = str + (pieces[i].toString()).substr(0, 2)+" ";
			else str = str + (pieces[i].toString()).substr(2, 2) + " ";
		}
		if (i == NP - 1 && flag && j==15) { i = -1; str = str + "\n"; }
		j++;
	}
	if(flag)str = str + "\n";
	return str;
}
