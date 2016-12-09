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

		starting->futureStates.push_back(planHelper(0, 0));
	}

	Node* planHelper(block first, block second) {

	}

	


};

