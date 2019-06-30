#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include"simulation.h"
using namespace std;

bool initWorld(world_t &world, const string &speciesFile,const string &creaturesFile) {
	return ((initSpecies(world, speciesFile)) && (initCreatures(world, creaturesFile)));
}

bool readFile(ifstream& iFile, const string& file) {
	iFile.open(file);
	if (!iFile) {
		cout << "Error: Cannot open file " << file << "!" << endl;
		return false;
	}
	return true;
}

bool initSpecies(world_t& world, const string& speciesFile) {
	ifstream iFile, in;
	int num_instr = 0, flag = 0;
	string species, directory, instr, path, command;
	unsigned int address;
	world.numSpecies = 0;

	if (!readFile(iFile, speciesFile)) return false;
	getline(iFile, directory);
	while (getline(iFile, species)) {
		path = directory + '/' + species;
		if (!readFile(in, path)) return false;
		(world.species[world.numSpecies]).name = species;
		num_instr = 0;
		while (getline(in, instr)) {
			if (instr == "") break;
			istringstream iStream;
			flag = 0;
			iStream.str(instr);
			iStream >> command >> address;
			for (int i = 0; i < 9; i++) {
				if (command == opName[i]) {
					((world.species[world.numSpecies]).program[num_instr]).op = (opcode_t)i;
					flag = 1;
					break;
				}
			}
			if (!flag) {
				cout << "Error: Instruction " << command << " is not recognized!" << endl;
				return false;
			}
			((world.species[world.numSpecies]).program[num_instr]).address = address - 1;
			num_instr++;
			if (num_instr == MAXPROGRAM && getline(in,instr)){
				if (instr != "") {
					cout << "Error: Too many instructions for species " << species << "!" << endl;
					cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
					return false;
				}
			}
		}
		in.close();
		(world.species[world.numSpecies]).programSize = num_instr;
		world.numSpecies++;
		if (world.numSpecies == MAXSPECIES && getline(iFile, species)) {
			cout << "Error: Too many species!" << endl;
			cout << "Maximal number of species is " << MAXSPECIES << "." << endl;
			return false;
		}
	}
	iFile.close();
	return true;
}

bool initCreatures(world_t& world, const string& creaturesFile) {
	ifstream iFile;
	istringstream iStream;
	world.numCreatures = 0;
	string line;
	int flag = 0; unsigned int height, width;

	if (!readFile(iFile, creaturesFile)) return false;
	for (int i = 0; i < 2; i++) {
		getline(iFile, line);
		iStream.str(line);
		if (i == 0) {
			iStream >> height;
			if (height<1 || height>MAXHEIGHT) {
				cout << "Error: The grid height is illegal!" << endl;
				return false;
			}
			else (world.grid).height = height;
		}
		else if (i == 1) {
			iStream >> width;
			if (width<1 || width>MAXWIDTH) {
				cout << "Error: The grid width is illegal!" << endl;
				return false;
			}
			else (world.grid).width = width;
		}
		iStream.clear();
		iStream.str("");
	}
	initGrid(world.grid);
	while (getline(iFile, line)) {
		iStream.str(line);
		string species, dir; unsigned int row, col;
		iStream >> species >> dir >> row >> col;
        (world.creatures[world.numCreatures]).programID = 0;
	    if ((row<0 || row>=(world.grid).height) || (col<0 || col>=(world.grid).width)) {
			cout << "Error: Creature (" << species << " " << dir << " " << (int)row << " " 
				<< (int)col << ") is out of bound!" << endl;
			cout << "The grid size is " << (world.grid).height << "-by-" << (world.grid).width 
				<< "." << endl;
			return false;
		}
		point_t location; location.r = row; location.c = col;
		if ((world.grid).squares[row][col] != nullptr) {
			cout << "Error: Creature (" << species << " " << dir << " " << row << " " << col
				<< ") overlaps with creature (" << (((world.grid).squares[row][col])->species)->name
				<< " " << directName[((world.grid).squares[row][col])->direction] << " " << row << " "
				<< col << ")!" << endl;
			return false;
		}
		(world.creatures[world.numCreatures]).location = location;
		(world.grid).squares[row][col] = &(world.creatures[world.numCreatures]);
		flag = 0;
		for (int i = 0; i < 4; i++) {
			if (directName[i] == dir) {
				(world.creatures[world.numCreatures]).direction = (direction_t)i;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			cout << "Error: Direction " << dir << " is not recognized!" << endl;
			return false;
		}
		flag = 0;
		for (unsigned int i = 0; i < world.numSpecies; i++) {
			if ((world.species[i]).name == species) {
				(world.creatures[world.numCreatures]).species = &(world.species[i]);
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			cout << "Error: Species " << species << " not found!" << endl;
			return false;
		}
		world.numCreatures++;
		if ((world.numCreatures == MAXCREATURES) && getline(iFile, line)) {
			cout << "Error: Too many creatures!" << endl;
			cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
			return false;
		}
		iStream.clear();
		iStream.str("");
	}
	iFile.close();
	return true;
}

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose) {
	cout <<"Creature (" << (creature.species)->name << " " << directName[creature.direction] << " "
		<< (creature.location).r << " " << (creature.location).c << ") takes action:";
	if(verbose) cout << endl;

	instruction_t instr = (creature.species)->program[creature.programID];
	while (instr.op >= 4 && instr.op <= 8) {
		if (verbose) printInstr(creature, instr);
		if (instr.op == IFEMPTY) ifInstr(creature,grid,instr,ifEmpty);
		else if (instr.op == IFWALL) ifInstr(creature, grid, instr, ifWall);
		else if (instr.op == IFSAME) ifInstr(creature, grid, instr, ifSame);
		else if (instr.op == IFENEMY) ifInstr(creature, grid, instr, ifEnemy);
		else if(instr.op == GO)creature.programID=instr.address;
		if (creature.programID == (creature.species)->programSize)
			creature.programID = 0;
		instr= (creature.species)->program[creature.programID];
	}
	if (verbose) printInstr(creature, instr);
	if (instr.op == HOP) {
		if (ifEmpty(creature, grid)) {
			grid.squares[(creature.location).r][(creature.location).c] = nullptr;
			creature.location = adjacentPoint(creature.location, creature.direction);
			grid.squares[(creature.location).r][(creature.location).c] = &creature;
		}
		creature.programID++;
	}
	else if (instr.op == LEFT) {
		creature.direction = leftFrom(creature.direction);
		creature.programID++;
	}
	else if (instr.op == RIGHT) {
		creature.direction = rightFrom(creature.direction);
		creature.programID++;
	}
	else if (instr.op == INFECT) {
		if (ifEnemy(creature,grid)) {
			creature_t* infect = updateCreature(creature, grid);
			infect->species = creature.species;
			infect->programID = 0;
		}
		creature.programID++;
	}
	if (!verbose)cout<< " " << opName[instr.op]<<endl;
	if (creature.programID == (creature.species)->programSize)
		creature.programID = 0;
	return;
}

bool ifWall(const creature_t &creature, const grid_t& grid) {
	if (creature.direction==EAST && (unsigned int)(creature.location).c == grid.width-1) return true;
	else if (creature.direction == SOUTH && (unsigned int)(creature.location).r == grid.height-1) return true;
	else if (creature.direction == WEST && (unsigned int)(creature.location).c == 0) return true;
	else if (creature.direction == NORTH && (unsigned int)(creature.location).r == 0) return true;
	else return false;
}

bool ifEmpty(const creature_t &creature, const grid_t &grid) {
	if (ifWall(creature, grid) || updateCreature(creature,grid) != nullptr) return false;
	else return true;
}

bool ifSame(const creature_t &creature, const grid_t &grid) {
	if (!ifWall(creature,grid)&&updateCreature(creature,grid)!=nullptr) {
		if ((updateCreature(creature, grid)->species)->name == (creature.species)->name)
			return true;
	}
	return false;
}

bool ifEnemy(const creature_t &creature, const grid_t &grid) {
	if (!ifWall(creature,grid)&&updateCreature(creature,grid)!=nullptr) {
		if ((updateCreature(creature, grid)->species)->name != (creature.species)->name)
			return true;
	}
	return false;
}

void ifInstr(creature_t & creature, const grid_t &grid,
	instruction_t instr, bool(*fn)(const creature_t&, const grid_t&)) {
	if (fn(creature, grid)) creature.programID = instr.address;
	else creature.programID++;
	return;
}

void printInstr(const creature_t &creature, instruction_t instr) {
	if (instr.op >= 4 && instr.op <= 8)
		cout << "Instruction " << creature.programID + 1 << ": "
		<< opName[instr.op] << " " << instr.address + 1<<endl;
	else cout << "Instruction " << creature.programID + 1 << ": " << opName[instr.op] << endl;
	return;
}

void printGrid(const grid_t &grid) {
	for (unsigned int i = 0; i < grid.height; i++) {
		for (unsigned int j = 0; j < grid.width; j++) {
			if (grid.squares[i][j] == nullptr)
				cout << "____ ";
			else {
				cout << (((grid.squares[i][j])->species)->name).substr(0, 2) << "_"
					<< directShortName[(int)((grid.squares[i][j])->direction)] << " ";
			}
		}
		cout << endl;
	}
	return;
}

point_t adjacentPoint(point_t pt, direction_t dir) {
	if (dir == EAST) pt.c++;
	else if (dir == SOUTH) pt.r++;
	else if (dir == WEST) pt.c--;
	else pt.r--;
	return pt;
}

direction_t leftFrom(direction_t dir) {
	if (dir == EAST) return NORTH;
	return (direction_t)((int)dir - 1);
}

direction_t rightFrom(direction_t dir) {
	if (dir == NORTH) return EAST;
	return (direction_t)((int)dir + 1);
}

creature_t *updateCreature(const creature_t &creature,const grid_t &grid) {
	int row = (creature.location).r;
	int col = (creature.location).c;
	if(creature.direction==EAST)return grid.squares[row][col+1];
	else if (creature.direction == SOUTH)return grid.squares[row+1][col];
	else if(creature.direction == WEST)return grid.squares[row][col - 1];
	else if (creature.direction == NORTH)return grid.squares[row-1][col];
	else return nullptr;
}

void initGrid(grid_t &grid) {
	for (unsigned int i = 0; i < grid.height; i++) {
		for (unsigned int j = 0; j < grid.width; j++) {
			grid.squares[i][j] = nullptr;
		}
	}
	return;
}