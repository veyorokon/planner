#pragma once
#include <map>
#include <string>
#include <vector>
#include "Relation.h"

#define block int
#define Relation int
#define SIZE 7
#define holding 4


class State
{
private:

public:


	int above[7][7];//Relation aboce
	//block blocks[7];
	Relation location[5];//Relation location where index 4 is HOLDING
	Relation on[7]; //Relation on
	Relation table[7];//Relation table
	Relation clear[7];//Relation clear

	State()
	{		
		for (int i = 0; i < SIZE; i++) {
			location[i] = -1;
			on[i] = -1;
			table[i] = -1;
			clear[i] = -1;
		}
	}

	~State()
	{
	}

	void operator = (State const state) {
		for (int i = 0; i < SIZE; i++) {
			location[i] = state.location[i];
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

	State* NotOn(State* s1, block block1, block block2) {
		s1->on[block1] = -1;
		return s1;
	}

	State* Holding(State* s1, block block1) {
		s1->location[holding] = block1;
		return s1;
	}
	State* NotHolding(State* s1) {
		s1->location[holding] = -1;
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
		s1->location[block1] = newLocation;
		return s1;
	}

	int operator == (State const state) {

	}
};

