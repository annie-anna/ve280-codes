#include"player.h"
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
using namespace std;

void printState(const Board& board, const Pool& pool) {
	cout << board.toString() << endl;
	cout << pool.toString() << endl;
}

int main(int argc, char* argv[]) {
	int i = 0, flag = 1; 
	unsigned int seed; 
	if (argc == 4) {
		seed = (unsigned int)atoi(argv[3]);
	}
	else seed = (unsigned int)time(NULL);
	Board board;
	Pool pool;
	Player* human=getHumanPlayer(&board,&pool);
	Player* myopic = getMyopicPlayer(&board,&pool,seed);
	printState(board, pool);
	while (flag) {
		flag = 0;
		cout << "Player " << i % 2 + 1 << "'s turn to select a piece:" << endl;
		
		if (*argv[i % 2 + 1] == 'h') {
			Piece& human_piece = human->selectPiece();
			cout << human_piece.toString() << " selected." << endl;
			cout << endl;
			human_piece.setUsed(1);
			if (*argv[2 - i % 2] == 'm') {
				cout << "Player " << 2 - i % 2  << "'s turn to select a square:" << endl;
				Square& myopic_square = myopic->selectSquare(human_piece);
				cout << myopic_square.toString() << " selected." << endl;
				cout << endl;
				board.place(human_piece, myopic_square);
				printState(board, pool);
				if (board.isWinning(human_piece, myopic_square)) {
					cout << "Player " << 2 - i % 2 << " has won!" << endl;
					break;
				}
			}
			else {
				cout << "Player " << 2 - i % 2 << "'s turn to select a square:" << endl;
				Square& human_square = human->selectSquare(human_piece);
				cout << human_square.toString() << " selected." << endl;
				cout << endl;
				board.place(human_piece, human_square);
				printState(board, pool);
				if (board.isWinning(human_piece, human_square)) {
					cout << "Player " << 2 - i % 2 << " has won!" << endl;
					break;
				}
			}
		}
		else {
			Piece& myopic_piece = myopic->selectPiece();	
			cout << myopic_piece.toString() << " selected." << endl;
			cout << endl;
			myopic_piece.setUsed(1);
			if (*argv[2 - i % 2] == 'm') {
				cout << "Player " << 2 - i % 2 << "'s turn to select a square:" << endl;
				Square& myopic_square = myopic->selectSquare(myopic_piece);
				cout << myopic_square.toString() << " selected." << endl;
				cout << endl;
				board.place(myopic_piece, myopic_square);
				printState(board, pool);
				if (board.isWinning(myopic_piece, myopic_square)) {
					cout << "Player " << 2 - i % 2 << " has won!" << endl;
					break;
				}
			}
			else {
				cout << "Player " << 2 - i % 2 << "'s turn to select a square:" << endl;
				Square& human_square = human->selectSquare(myopic_piece);
				cout << human_square.toString() << " selected." << endl;
				cout << endl;
				board.place(myopic_piece, human_square);
				printState(board, pool);
				if (board.isWinning(myopic_piece, human_square)) {
					cout << "Player " << 2 - i % 2 << " has won!" << endl;
					break;
				}
			}
		}
		for (int j = 0; j < N; j++) {//check if all squares are filled (draw).
			for (int k = 0; k < N; k++) {
				if (board.getSquare((Vaxis)j, (Haxis)k).isEmpty()) {
					flag = 1;
					break;
				}
			}
			if (flag) break;
		}
		if(!flag) cout << "It is a draw." << endl;
		i++;
	}
	return 0;
}