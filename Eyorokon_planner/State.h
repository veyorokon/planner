#pragma once
#include <map>
#include <string>
#include <vector>
#include "Relation.h"

#define block int
#define Relation int
#define SIZE 7
#define holding 4
#define l1 0
#define l2 1
#define l3 2
#define l4 3
using namespace std;
class State
{
private:
	int above[7][7];//Relation aboce
					//block blocks[7];
	Relation location[5][7];//Relation location where index 4 is HOLDING
	Relation on[7]; //Relation on
	Relation table[7];//Relation table
	Relation clear[7];//Relation clear
public:


	

	State()
	{		
		for (int i = 0; i < SIZE; i++) {
			for(int j=0; j< SIZE -2; j++)
				location[j][i] = -1;
			on[i] = -1;
			table[i] = 0;
			clear[i] = 0;
		}
	}

	~State()
	{
	}

	void operator = (State const state) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j< SIZE - 2; j++)
				location[j][i] = state.location[j][i];
			on[i] = state.on[i];
			table[i] = state.table[i];
			clear[i] = state.clear[i];
		}
	}

	State* On(State* s1, block block1, block block2) {
		s1->on[block1] = block2;
		s1->clear[block2] = false;
		return s1;
	}

	block GetOn(block block1) {
		return on[block1];
	}

	State* NotOn(State* s1, block block1) {
		s1->on[block1] = -1;
		return s1;
	}

	State* Holding(State* s1, block block1) {
		s1->location[holding][0] = block1;
		return s1;
	}
	State* NotHolding(State* s1) {
		s1->location[holding][0] = -1;
		return s1;
	}

	State* Table(State* s1, block block1) {
		s1->table[block1] = true;
		return s1;
	}
	State* NotTable(State* s1, block block1) {
		s1->table[block1] = false;
		return s1;
	}

	State* Clear(State* s1, block block1) {
		s1->clear[block1] = true;
		return s1;
	}
	State* NotClear(State* s1, block block1) {
		s1->clear[block1] = false;
		return s1;
	}

	State * Location(State* s1, block block1, int newLocation) {
		s1->location[newLocation][block1] = 1;
		return s1;
	}

	State * NotLocation(State* s1, block block1, int oldLocation) {
		s1->location[oldLocation][block1] = -1;
		return s1;
	}

	int GetLocation( block block1) {
		int currentLocation;
		for (int i = 0; i < 4; i++) { // 4 locations
			if (location[i][block1] == 1) return i; //check column for block
		}
	}

	int GetHolding() {
		return location[holding][0];
	}
	
	bool IsBlockClear(block block1) {
		return clear[block1];
	}

	bool IsLocationEmpty(int loc) {
		for (int j = 0; j < SIZE; j++)
			if (location[loc][j] != -1) return false;
		return true;
	}

	bool IsBlockTable(block block1) {
		return table[block1];
	}
	/*
	int operator == (State const state) {

	}
	*/
};

