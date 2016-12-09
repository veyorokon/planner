#pragma once
#include "stdafx.h"
#include "State.h"
#include "Node.h"
using namespace std;
/*Default constructor*/
Node::Node() {
	parent = NULL;
	leftChild = NULL;
	rightSibling = NULL;
	State nState;
	current = nState;
	checked = false;
}

Node::~Node()
{
}

Node::Node(State currentState, Node * par)
{
	parent = par;
	current = currentState;
	leftChild = NULL;
	rightSibling = NULL;
	checked = false;
}
void Node::Insert(Node * futureState) {
	if (leftChild == NULL) {
		leftChild = futureState;
		leftChild->parent = this; // UPdate parent pointers for new child
	}
	else {
		Node * ptr = leftChild;
		while (ptr->rightSibling != NULL)
			ptr = ptr->rightSibling;
		ptr->rightSibling = futureState;
		futureState->parent = this; //Update parent pointers for new child
	}

}

State Node::PickUp(const State * s1, block block1) {
	State newState = *s1;
	
	int oldLocation = newState.GetLocation(block1);
	//IF BLOCK CLEAR, IF NOT HOLDING, IS NOT ON (Is on = unstack)
	if (newState.IsBlockClear(block1) && newState.GetHolding()==-1 && newState.GetOn(block1) == -1) {
		Node * futureState;
		//UPDATE HOLDING
		newState.Holding(&newState, block1); // set holding to block1
		//UPDATE NOT CLEAR
		newState.NotClear(&newState, block1);//set clear to false
		//UPDATE TABLE			
		newState.NotTable(&newState, block1);
		newState.NotLocation(&newState, block1, oldLocation);
		
		string steps = ("Pickup(block" + to_string(block1) + ")");
		//cout << (steps);
		
		futureState = new Node(newState, this);
		//UPDATE STEPS
		//
		//futureStates.push_back(futureState);
		//ADD TO LIST OF CHILDREN
		Insert(futureState);
	}
	return newState;
}

State Node::PutDown(const State * s1, block block1, int newLocation) {
	State newState = *s1;
	

	//PLACE IN EMPTY LOCATION
	if (newState.GetHolding() == block1 && newState.IsLocationEmpty(newLocation)) {
		Node * futureState;
		//TABLE BLOCK
		newState.Table(&newState, block1);
		//CLEAR BLOCK
		newState.Clear(&newState, block1);
		//NOT HOLDING
		newState.NotHolding(&newState);
		//PLACE BLOCK
		newState.Location(&newState, block1, newLocation);

		//string step = ("Pickup(block" + to_string(block1) + ")");
		futureState = new Node(newState, this);
		//UPDATE STEPS
		
		string steps = 
		("PutDown(block" + to_string(block1) + ", location" + to_string(newLocation) + ")\n");
		//cout << (steps);
		
		Insert(futureState);
	}
	return newState;
}

State Node::UnStack(const State * s1, block block1) {
	State newState = *s1;
	
	int oldLocation = newState.GetLocation(block1);
	//CHECK BLOCK ON, BLOCK CLEAR
	if (newState.IsBlockClear(block1) && newState.GetOn(block1) != -1) {
		Node * futureState;
		//UPDATE HOLDING
		newState.Holding(&newState, block1); // set holding to block1
		//UPDATE NOT CLEAR
		newState.NotClear(&newState, block1);//set clear to false
		//UPDATE UNDERNEATH BLOCK
		block underneath = newState.GetOn(block1);
		newState.Clear(&newState, underneath);
		//UPDATE LOCATION			
		newState.NotLocation(&newState, block1, oldLocation);
		//UPDATE ON
		newState.NotOn(&newState, block1);

		//string step = ("Pickup(block" + to_string(block1) + ")");
		futureState = new Node(newState, this);
		//UPDATE STEPS
		
		string steps = ("UnStack(block" + to_string(block1) + ")");
		//cout <<(steps);
		
		Insert(futureState);
	}
	return newState;
}

State Node::Stack(const State * s1, block block1, block block2) {
	State newState = *s1;
	
	int location = newState.GetLocation(block2);
	//CHECK HOLDING BLOCK, CLEAR, NOT EQUAL
	if (newState.GetHolding() == block1 && newState.IsBlockClear(block2)) {
		Node * futureState;
		//NOT HOLDING
		newState.NotHolding(&newState); 
		//UPDATE NOT CLEAR
		newState.NotClear(&newState, block2);//set clear to false
		//UPDATE LOCATION
		newState.Location(&newState, block1, location);
		//UPDATE ON
		newState.On(&newState, block1, block2);
		//UPDATE TOP CLEAR
		newState.Clear(&newState, block1);

		//string step = ("Pickup(block" + to_string(block1) + ")");
		futureState = new Node(newState, this);
		//UPDATE STEPS
		
		string steps;
		steps=("Stack(block" + to_string(block1) + ", block" + to_string(block2) + ")\n");
		//cout <<(steps);
		
		Insert(futureState);
	}
	return newState;
}

Node* Node::getAllStates(block first, block second, State* goal) {
	PickUp(&current, first);
	PutDown(&current, first, 0);
	PutDown(&current, first, 1);
	PutDown(&current, first, 2);
	PutDown(&current, first, 3);
	UnStack(&current, first);
	Stack(&current, first, second);
	if (first != second) {
		PickUp(&current, second);
		PutDown(&current, second, 0);
		PutDown(&current, second, 1);
		PutDown(&current, second, 2);
		PutDown(&current, second, 3);
		UnStack(&current, second);
		Stack(&current, second, first);
	}
	if (leftChild == NULL ) return NULL;
	Node * ptr = leftChild;
	while (ptr != NULL) {
		if ((ptr->current) == *goal) {
			cout << "FJDKSLJFKLDSJFDKSLJFKSLJFKLSDJ" << endl;
			return ptr;
		}
		ptr = ptr->rightSibling;
	}
	return NULL;
}

ostream & operator<<(std::ostream & os, const Node & obj)
{
	//os << "Node Step: " << obj.step[0] << endl;
	return os;
}

