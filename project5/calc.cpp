#include<iostream>
#include<cstdlib>
#include<string>
#include"dlist.h"
using namespace std;

void print(Dlist<int>& l) {
	int* top = l.removeFront();
	cout << *top << endl;
	l.insertFront(top);
}

void clear(Dlist<int>& l) {
	l.~Dlist();
}

void printAll(Dlist<int>& l) {
	if (l.isEmpty()) cout << endl;
	else {
		int* current = l.removeFront();
		int* test=nullptr;
		cout << *current << flush;
		try {
			test = l.removeFront();
			cout << " " << flush;
			l.insertFront(test);
		}
		catch (emptyList e) {
		}
		printAll(l);
		l.insertFront(current);
	}
}

int main() {
	Dlist<int> stack;
	string op;
	
	do {
		cin >> op;
		if (op == "q") break;
		if (op[0] != '+' && op[0] != '-' && (op[0]<'0' || op[0]>'9') && op[0] != '*'&&op[0] != '/'
			&&op[0] != 'n'&&op[0] != 'd'&&op[0] != 'r'&&op[0] != 'p'&&op[0] != 'c'
			&&op[0] != 'a') {
			cout << "Bad input\n";
			continue;
		}
		else {
			if ((op[0] == '-'&&op.size()!=1) || (op[0] >= '0' && op[0] <= '9')) {
				int flag = 0;
				for (int i = 1; i < (int)op.size(); i++) {
					if (op[i]<'0' || op[i]>'9') {
						cout << "Bad input\n";
						flag = 1;
						break;
					}
				}
				if (flag) continue;
				int* op_int = new int(atoi(&op[0]));
				stack.insertFront(op_int);
			}
			else {
				if (op.length() != 1) {
					cout << "Bad input\n";
					continue;
				}
			}
		}
		if (op[0] == '+' || (op[0] == '-'&&op.size()==1) || op[0] == '*' || op[0] == '/' || op[0] == 'r') {
			int count = 0;
			int *first=nullptr, *second=nullptr;
			try {
				first = stack.removeFront();
				count++;
				second = stack.removeFront();
				count++;
				stack.insertFront(second);
				stack.insertFront(first);
			}
			catch (emptyList e) {
				cout << "Not enough operands\n";
				if (count) stack.insertFront(first);
				continue;
			}
		}
		if (op[0] == 'n' || op[0] == 'd'|| op[0] == 'p') {
			int count = 0;
			int *first=nullptr;
			try {
				first = stack.removeFront();
				count++;
				stack.insertFront(first);
			}
			catch (emptyList e) {
				cout << "Not enough operands\n";
				continue;
			}
		}
		if (op[0] == '/') {
			int *divisor = stack.removeFront();
			if (!(*divisor)) {
				cout << "Divide by zero\n";
				stack.insertFront(divisor);
				continue;
			}
			else stack.insertFront(divisor);
		}
		
			if (op[0] == '+' || (op[0] == '-'&&op.size()==1) || op[0] == '*' || op[0] == '/' || op[0] == 'r') {
				int* first = stack.removeFront();
				int* second = stack.removeFront();
				int* answer;
				if (op[0] != 'r') {
					if (op[0] == '+') {
						answer = new int((*first) + (*second));
						stack.insertFront(answer);
					}
					else if (op[0] == '-') {
						answer = new int((*second) - (*first));
						stack.insertFront(answer);
					}
					else if (op[0] == '*') {
						answer = new int((*first) * (*second));
						stack.insertFront(answer);
					}
					else if (op[0] == '/') {
						answer = new int((*second) / (*first));
						stack.insertFront(answer);
					}
					delete first;
					delete second;
				}
				else {
					stack.insertFront(first);
					stack.insertFront(second);
				}
			}
			else if (op[0] == 'n' || op[0] == 'd') {
				int* first = stack.removeFront();
				int *answer, *answer_cp;
				if (op[0] == 'n') {
					answer = new int((*first)*(-1));
					stack.insertFront(answer);
				}
				else {
					answer = new int(*first);
					answer_cp = new int(*first);
					stack.insertFront(answer);
					stack.insertFront(answer_cp);
				}
				delete first;
			}
			else if (op[0] == 'p') print(stack);
			else if (op[0] == 'c') clear(stack);
			else if(op[0]=='a') printAll(stack);
	} while (true);
	//system("pause");
	return 0;
}