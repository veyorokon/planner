#pragma once
#include "State.h"
#include "Relation.h"
#include "Node.h"
#define block int
#define holding 4

class Tree
{
private:

public:
	
	Node * starting;
	State * goal;
	Node * ending;

	Tree(State newStart, State newGoal)
	{
		starting = new Node(newStart, NULL);
		*goal = newGoal;
	}

	~Tree()
	{
	}

	void findPlan() {
		
	}

	Node* planHelper(block first, block second, vector<Node *> futureStates) {
		//PERMUTATE
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++)
				starting->getAllStates(i, j);
		}
		/*
		for (int i = 0; i < futureStates; i++) {
			if (futureStates[i]->current.
		}
		*/
	}

	


};

