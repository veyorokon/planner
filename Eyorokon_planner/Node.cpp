#pragma once
#include "stdafx.h"
#include "State.h"
#include "Node.h"

/*Default constructor*/
Node::Node() {
	parent = NULL;
}

Node::~Node()
{
}

Node::Node(State currentState, Node * par)
{
	parent = par;
	current = currentState;
}

State& Node::PickUp(State * s1, block block1) {
	State newState = *s1;
	int oldLocation = newState.getLocation(s1, block1);
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
		newState.NotTable(&newState, block1);
		newState.NotLocation(&newState, block1, oldLocation);
	}
	return newState;
}

State& Node::PutDown(State * s1, block block1, int newLocation) {
	State newState = *s1;

	
	
	return newState;
}