#pragma once
#include "State.h"
#include "Relation.h"
#include "Node.h"
#define block int
#define holding 4
using namespace std;

class Tree
{
private:

public:
	
	Node * starting;
	State * goal;
	Node * ending;

	Tree(State *newStart, State newGoal)
	{
		starting = new Node(*newStart, NULL);
		State nState;
		goal = &nState;
		*goal = newGoal;
	}

	~Tree()
	{
	}

	Node * plan() {
		Node * ptr = (buildTree(starting));
		starting->parent = ptr;
		ptr->parent = NULL;
		return starting;
	}

	Node* buildTree(Node * root) {
		if (root->current == *goal) {
			return root;
		}
		if (root) {
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					root->getAllStates(i, j);
					if (root->rightSibling) buildTree(root->rightSibling);
				}
			}
		}
		return root->leftChild;
	}

};

