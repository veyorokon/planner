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

	Tree(State *newStart, State * newGoal)
	{
		string s = "start";
		starting = new Node(*newStart, NULL, s);
		goal = newGoal;
	}

	~Tree()
	{
	}

	Node * plan() {
		bool found = false;
		Node * planNode = new Node();
		(buildTree(starting, 0, found, *planNode));
		//RETURN LEFT CHILD FORCED!
		return planNode->leftChild;
	}

	/*For whatever reason, the plam node is the left child but it wont return? Instead,
	its parent is returned.*/
	Node* buildTree(Node * root, int level, bool &found, Node & planNode) {
		
		if (root && level < 3 ) {
			
			//Permuations
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					Node * ptr = root->getAllStates(i, j, goal);
					if (ptr && (ptr->current) == *goal) {
						cout << "FOUND FOUND FOUND FOUND FOUDN FOUDN" << endl;
						found = true;
						planNode = *root;
						return ptr;
					}
				}
			}

			if (root->leftChild && !found) {
				Node * lc = root->leftChild;
				buildTree(lc, level + 1, found, planNode);
				//lc = lc->rightSibling;
				while (lc != NULL && !found) {
					lc = lc->rightSibling;
					if(lc != NULL)
						buildTree(lc, level + 1, found, planNode);
				}
			}
		}
		if (found) return &planNode;
		return root;
	}

};

