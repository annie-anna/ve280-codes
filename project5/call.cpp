#include<iostream>
#include<cstdlib>
#include<string>
#include"dlist.h"
using namespace std;

int main() {
	struct caller {
		int timestamp;
		string name;
		string status;
		int duration;
	};

	Dlist<caller> AllCaller;
	Dlist<caller> Platinum;
	Dlist<caller> Gold;
	Dlist<caller> Silver;
	Dlist<caller> Regular;

	int tick = 0, duration = 0, oldTick = 0,ifBusy = 0;
	int num_of_caller,currentCall,unprocessedCall; //num_of_caller is the caller calls until tick i
	cin >> num_of_caller; unprocessedCall = num_of_caller;

	for (int row = 0; row < num_of_caller; row++) {
		caller call;
		cin >> (call).timestamp >> (call).name >> (call).status >> (call).duration;
		caller* cand = new caller(call);
		AllCaller.insertFront(cand);
	}

	do {
		currentCall = 0;
		cout << "Starting tick #" << tick <<endl;
		for (int row = 0; row < num_of_caller; row++) {
			caller* call = AllCaller.removeBack();
			if ((call)->timestamp == tick) {
				currentCall++;
				if ((call)->status == "platinum") {
					Platinum.insertFront(call);
					cout << "Call from " << (call)->name << " a platinum member"<<endl;
				}
				else if ((call)->status == "gold") {
					Gold.insertFront(call);
					cout << "Call from " << (call)->name << " a gold member"<<endl;
				}
				else if ((call)->status == "silver") {
					Silver.insertFront(call);
					cout << "Call from " << (call)->name << " a silver member"<<endl;
				}
				else {
					Regular.insertFront(call);
					cout << "Call from " << (call)->name << " a regular member"<<endl;
				}
			}
			else AllCaller.insertFront(call);
		}
		if (currentCall) num_of_caller = num_of_caller - currentCall;
		if (!ifBusy&&(!Platinum.isEmpty() || !Gold.isEmpty() || !Silver.isEmpty()
			|| !Regular.isEmpty())) {
			caller* customer=nullptr;
			if (!Platinum.isEmpty()) {
				customer = Platinum.removeBack();
				cout << "Answering call from " << customer->name<<endl;
			}
			else if (!Gold.isEmpty()) {
				customer = Gold.removeBack();
				cout << "Answering call from " << customer->name << endl;
			}
			else if (!Silver.isEmpty()) {
				customer = Silver.removeBack();
				cout << "Answering call from " << customer->name << endl;
			}
			else if (!Regular.isEmpty()) {
				customer = Regular.removeBack();
				cout << "Answering call from " << customer->name << endl;
			}
			ifBusy = 1;
			duration = customer->duration;
			oldTick = tick;
			unprocessedCall--;
			delete customer;
		}
		tick++;
		if (oldTick + duration <= tick) ifBusy = 0;
	} while (unprocessedCall);
	while (tick <= oldTick + duration) {
		cout << "Starting tick #" << tick << endl;
		tick++;
	}
	//system("pause");
	return 0;
}