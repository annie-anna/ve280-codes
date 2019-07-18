#include"player.h"
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include"exceptions.h"

class HumanPlayer :public Player {
public:
	HumanPlayer(Board* board, Pool* pool):Player(board, pool) {};
	void setPlayer(Board* b, Pool* p);
	Piece & selectPiece();
	Square & selectSquare(const Piece &p);
};

void HumanPlayer::setPlayer(Board* b, Pool* p) {
	board = b; pool = p;
}

Piece & HumanPlayer::selectPiece() {
	std::string str = ""; int flag = 0; Piece piece_cand;
	do {
		flag = 0;
		std::cout << "Enter a piece:" << std::flush;
		std::cin >> str;
		if (str.length() != 4) {
			InvalidInputException exp(str);
			std::cout << exp.what()<<std::endl;
			flag = 1;
		}
		else if ((str[0] != HCODE[0] && str[0] != HCODE[1]) || (str[1] != CCODE[0]&&str[1] != CCODE[1]) 
			|| (str[2] != SCODE[0]&&str[2] != SCODE[1]) ||(str[3] != TCODE[0]&&str[3] != TCODE[1])) {
			InvalidInputException exp(str);
			std::cout << exp.what() << std::endl;
			flag = 1;
		}
		else {
			try {
				piece_cand = pool->getUnusedPiece(str);
			}
			catch (UsedPieceException exp){
				std::cout << exp.what() << std::endl;
				flag = 1;
			}
		}
	} while (flag);
	return pool->getUnusedPiece(str);
}

Square & HumanPlayer::selectSquare(const Piece &p) {
	std::string str; int flag = 0; Square square_cand;
	do {
		flag = 0;
		std::cout << "Enter a position:" << std::flush;
		std::cin >> str;
		if (str.length() != 2) {
			InvalidInputException exp(str);
			std::cout << exp.what()<<std::endl;
			flag = 1;
		}
		else if ((str[0] != 'A'&&str[0] != 'B'&&str[0] != 'C'&&str[0] != 'D') ||
			(str[1] != '1'&&str[1] != '2'&&str[1] != '3'&&str[1] != '4')) {
			InvalidInputException exp(str);
			std::cout << exp.what()<<std::endl;
			flag = 1;
		}
		else {
			try {
				square_cand = board->getEmptySquare(str);
			}
			catch(SquareException exp){
				std::cout << exp.what() << std::endl;
				flag = 1;
			}
		}
	} while (flag);
	return board->getEmptySquare(str);
}

class MyopicPlayer :public Player {
public:
	MyopicPlayer(Board* board, Pool* pool) :Player(board, pool) {};
	void setPlayer(Board* b,Pool* p);
	Piece & selectPiece();
	Square & selectSquare(const Piece &p);
};

void MyopicPlayer::setPlayer(Board* b, Pool* p) {
	board = b; pool = p;
}

Piece & MyopicPlayer::selectPiece() {
	int flag = 0, sum = 0, num_bad_piece=0; 
	int index[NP] = { 0 }, bad_piece[NP] = { 0 };
	Piece temp;
	std::string piece_code[NP] = { "SBCH","SBCO","SBQH","SBQO","SECH","SECO","SEQH","SEQO","TBCH",
	"TBCO","TBQH","TBQO","TECH","TECO","TEQH","TEQO" };
	for (int i = 0; i < NP; i++) {
		flag = 0;
		try {
			temp = pool->getUnusedPiece(piece_code[i]);
			for (int m = 0; m < N; m++) {//whether the piece is a bad one
				for (int n = 0; n < N; n++) {
					Square candsqr;
					candsqr = board->getSquare((Vaxis)m, (Haxis)n);
					if (candsqr.isEmpty()) {
						if (board->isWinning(temp, candsqr)) {
							bad_piece[num_bad_piece] = i;
							num_bad_piece++;
							flag = 1;
							break;
						}
					}
				}
				if (flag) break;
			}
			if (!flag) { index[sum] = i; sum++; }//not bad piece
		}
		catch (UsedPieceException exp) { continue; }
	}
	if (!sum) return  pool->getUnusedPiece(piece_code[bad_piece[rand()%num_bad_piece]]);
	else return pool->getUnusedPiece(piece_code[index[rand()%sum]]);
}

Square & MyopicPlayer::selectSquare(const Piece &p) {
	Square square_cand; int index[NP] = { 0 }; int sum = 0;
	std::string square_code[NP] = { "A1","A2","A3","A4","B1","B2","B3","B4",
		"C1","C2","C3","C4","D1","D2","D3","D4" };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			square_cand = board->getSquare((Vaxis)i, (Haxis)j);
			if (square_cand.isEmpty()) {
				index[sum] = 4*i+j; sum++;
				if(board->isWinning(p, board->getSquare((Vaxis)i, (Haxis)j)))
				return board->getSquare((Vaxis)i, (Haxis)j);
			}
		}
	}
	int dec = index[rand() % sum];
	return board->getSquare((Vaxis)(dec/4),(Haxis)(dec%4));
}

static HumanPlayer hu_play(nullptr, nullptr);

extern Player *getHumanPlayer(Board *b, Pool *p) {
	hu_play.setPlayer(b, p);
	return &hu_play;
}

static MyopicPlayer my_play(nullptr,nullptr);

extern Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s) {
	srand(s);
	my_play.setPlayer(b, p);
	return &my_play;
}