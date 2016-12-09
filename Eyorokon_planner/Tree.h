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
		vector<State> checked;
		Node * ptr = (buildTree(starting, checked));
		starting->parent = ptr;
		ptr->parent = NULL;
		return starting;
	}

	Node* buildTree(Node * root, vector<State> checked) {
		if (root && root->checked && !(*root->checked)) {
			if (root->current == *goal) {
				return root;
			}
			//Get Permutations
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					root->getAllStates(i, j);
				}
			}
			Node * ptr = root;
			//Check right sibling states
			while (ptr != NULL) {
				bool isIn = false;
				for (int count = 0; count < checked.size(); count++) {
					if (ptr->current == checked[count]) isIn = true;
					else *(ptr->checked) = true;
				}
				checked.push_back(ptr->current);
				ptr = ptr->rightSibling;
			}
		}
		if (root) {
			buildTree(root->rightSibling, checked);
			buildTree(root->leftChild, checked);
		}
	}

};

