#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"
using namespace std;

bool initWorld(world_t &world, const string &speciesFile,
	const string &creaturesFile);
// MODIFIES: world
//
// EFFECTS: Initialize "world" given the species summary file
// "speciesFile" and the world description file
// "creaturesFile". This initializes all the components of
// "world". Returns true if initialization is successful.

bool readFile(ifstream& iFile, const string& file);
// MODIFIES: iFile
// EFFECTS: If read the file successfully, return true; otherwise,
// print error message and return false.

bool initSpecies(world_t& world, const string& speciesFile);
// MODIFIES: world
//
// EFFECTS: Initialize species in the "world" given the species summary file
// "speciesFile". Returns true if initialization is successful.

bool initCreatures(world_t& world, const string& creaturesFile);
// MODIFIES: world
//
// EFFECTS: Initialize creatures in the "world" given the world description file
// "creaturesFile". Returns true if initialization is successful.

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS: Simulate one turn of "creature" and update the creature,
// the infected creature, and the grid if necessary.
// The creature programID is always updated. The function
// also prints to the stdout the procedure. If verbose is
// true, it prints more information.

bool ifWall(const creature_t &creature, const grid_t &grid);
// REQUIRES: creature is inside the grid.
// EFFECTS: If creature is facing the border of the grid, return true; 
// otherwise, return false.

bool ifEmpty(const creature_t &creature, const grid_t &grid);
// REQUIRES: creature is inside the grid.
// EFFECTS: If the square in front of the creature is inside the grid boundary 
// and unoccupied, return true; otherwise, return false.

bool ifSame(const creature_t &creature, const grid_t &grid);
// REQUIRES: creature is inside the grid.
// EFFECTS: If the square the creature is facing is occupied by a creature of the 
// same species, return true; otherwise, return false.

bool ifEnemy(const creature_t &creature, const grid_t &grid);
// REQUIRES: creature is inside the grid.
// EFFECTS: If the square the creature is facing is occupied by a creature of an 
// enemy species, return true; otherwise, return false.

void ifInstr(creature_t & creature, const grid_t &grid,
	instruction_t instr, bool(*fn)(const creature_t&, const grid_t&));
// REQUIRES: creature is inside the grid.
// MODIFIES: creature.
// EFFECTS: If instruction can be exercised, change programID to assigned address;
// otherwise, increment programID.

void printInstr(const creature_t &creature, instruction_t instr);
// REQUIRES: creature is inside the grid.
// EFFECTS: Print instructions.

void printGrid(const grid_t &grid);
// MODIFIES: cout.
//
// EFFECTS: print a grid representation of the creature world.

point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns a point that results from moving one square
// in the direction "dir" from the point "pt".

direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
// left from the given direction "dir".

direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
// right from the given direction "dir".

creature_t *updateCreature(const creature_t &creature, const grid_t &grid);
// REQUIRES: location is inside the grid.
//
// EFFECTS: Returns a pointer to the updated creature.

void initGrid(grid_t &grid);
// EFFECTS: Initialize all pointers in grid to be null pointers.

#endif