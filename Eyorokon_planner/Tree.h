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
		starting = new Node(*newStart, NULL);
		goal = newGoal;
	}

	~Tree()
	{
	}

	Node * plan() {
		bool found = false;
		Node * planNode = new Node();
		(buildTree(starting, 0, found, planNode));
		return planNode;
	}

	Node*& buildTree(Node * root, int level, bool &found, Node *& planNode) {
		
		if (root && level < 3 ) {
			
			//Permuations
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					Node * ptr = root->getAllStates(i, j, goal);
					if (ptr && (ptr->current) == *goal) {
						cout << "FOUND FOUND FOUND FOUND FOUDN FOUDN" << endl;
						found = true;
						planNode = root;
						return ptr;
					}
				}
			}

			if (root->leftChild && !found) {
				Node * lc = root->leftChild;
				buildTree(lc, level + 1, found, planNode);
				lc = lc->rightSibling;
				while (lc != NULL && !found) {
					buildTree(lc, level+1, found, planNode);
					lc = lc->rightSibling;
				}
			}
		}
		if (found) return planNode;
		return root;
	}

	/*if (root && root->checked && !(*root->checked)) {
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
		}*/
};

