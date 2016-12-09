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

State Node::PickUp(const State * s1, block block1) {
	State newState = *s1;
	int oldLocation = newState.GetLocation(block1);
	//IF BLOCK CLEAR, IF NOT HOLDING, NOT ON
	if (newState.IsBlockClear(block1) && newState.GetHolding()==-1 && newState.GetOn(block1) == -1) {
		//UPDATE HOLDING
		newState.Holding(&newState, block1); // set holding to block1
		//UPDATE NOT CLEAR
		newState.NotClear(&newState, block1);//set clear to false
		//UPDATE TABLE			
		newState.NotTable(&newState, block1);
		newState.NotLocation(&newState, block1, oldLocation);
	}
	return newState;
}

State Node::PutDown(const State * s1, block block1, int newLocation) {
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

State Node::UnStack(const State * s1, block block1) {
	State newState = *s1;
	int oldLocation = newState.GetLocation(block1);
	//CHECK BLOCK ON, BLOCK CLEAR
	if (newState.IsBlockClear(block1) && newState.GetOn(block1) != -1) {
		//UPDATE HOLDING
		newState.Holding(&newState, block1); // set holding to block1
		//UPDATE NOT CLEAR
		newState.NotClear(&newState, block1);//set clear to false
		//UPDATE UNDERNEATH BLOCK
		block underneath = newState.GetOn(block1);
		newState.Clear(&newState, underneath);
		//UPDATE LOCATION			
		newState.NotLocation(&newState, block1, oldLocation);
	}
	return newState;
}

State Node::Stack(const State * s1, block block1, block block2) {
	State newState = *s1;
	int location = newState.GetLocation(block2);
	//CHECK HOLDING BLOCK
	if (newState.GetHolding() == block1 && newState.IsBlockClear(block2)) {
		//NOT HOLDING
		newState.NotHolding(&newState); 
		//UPDATE NOT CLEAR
		newState.NotClear(&newState, block2);//set clear to false
		//UPDATE LOCATION
		newState.Location(&newState, block1, block2);
		//UPDATE ON
		newState.On(&newState, block1, block2);
		//UPDATE TOP CLEAR
		newState.Clear(&newState, block1);
	}
	return newState;
}