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

State Node::PickUp(State * s1, block block1) {
	State newState = *s1;
	int oldLocation = newState.GetLocation(s1, block1);
	//IF BLOCK CLEAR
	if (newState.IsBlockClear(block1)) {
		//UPDATE HOLDING
		newState.Holding(&newState, block1); // set holding to block1
		//UPDATE NOT CLEAR
		newState.NotClear(&newState, block1);//set clear to false
		if (newState.GetOn(&newState, block1) != -1) {//If the block was ontop of another
			block underneath = newState.GetOn(&newState, block1);
			newState.Clear(&newState, underneath);
		}
		//UPDATE TABLE			
		newState.NotTable(&newState, block1);
		newState.NotLocation(&newState, block1, oldLocation);
	}
	return newState;
}

State Node::PutDown(State * s1, block block1, int newLocation) {
	State newState = *s1;
	//PLACE IN EMPTY LOCATION
	if (newState.GetHolding() == block1 && newState.IsLocationEmpty(newLocation)) {
		//TABLE BLOCK
		newState.Table(&newState, block1);
		//CLEAR BLOCK
		newState.Clear(&newState, block1);
		//NOT HOLDING
		newState.NotHolding(&newState);
		//PLACE BLOCK
		newState.Location(&newState, block1, newLocation);
	}
	return newState;
}