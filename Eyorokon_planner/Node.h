#pragma once
#include "State.h"
#include <string>

class Node
{
	/*Node class is the atomic data structure in the tree that contains one key,
	value pair. The Node also tracks relations. */
public:
	State current; //Keeps track of the original state
	Node futureStates[4]; // One for each function
	Node * parent;

	/*Default constructor*/
	Node() {
		
	}
	Node(State currentState, Node * par)
	{
		parent = par;
		current = currentState;
	}

	State& PickUp(State * s1, block block1) {
		State newState = *s1;

		if (newState.clear[block1]) {
			//UPDATE HOLDING
			newState.Holding(&newState, block1); // set holding to block1
			//UPDATE CLEAR
			newState.clear[block1] = 0; //set clear to false
			if (newState.on[block1] != -1) {//If the block was ontop of another
				block underneath = newState.on[block1];
				newState.Clear(&newState, underneath);
			}
			//UPDATE TABLE
			if (newState.table[block1] != -1) {//If the block was on the table
				newState.NotTable(&newState, block1);
			}
		}
		return newState;
	}
};