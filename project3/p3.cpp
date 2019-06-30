#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>
#include"simulation.h"
using namespace std;

int main(int argc, char* argv[]) {
	int verbose, round,i;
	istringstream iStream;
	string str;
	world_t world;

	if (argc < 4) {
		cout << "Error: Missing arguments!" << endl;
		cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
		return 0;
	}
	round = atoi(argv[3]);
	if (round < 0) {
		cout << "Error: Number of simulation rounds is negative!" << endl;
		return 0;
	}
	if (argc == 5) {
		iStream.str(argv[4]);
		iStream >> str;
		if(str=="v" || str=="verbose") verbose = 1;
		else verbose = 0;
	}
	else verbose = 0;
	if(!initWorld(world, argv[1], argv[2])) 
		return 0;
	cout << "Initial state"<<endl;
	printGrid(world.grid);
	for (i = 0; i < round; i++) {
		cout << "Round " << i + 1<<endl;
		for (unsigned int j = 0; j < world.numCreatures; j++) {
			simulateCreature(world.creatures[j], world.grid, verbose);
			if (verbose)printGrid(world.grid);
		}
		if (!verbose) printGrid(world.grid);
	}
	return 0;
}