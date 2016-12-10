#pragma once
#include "State.h"
#include "Relation.h"
#include "Node.h"
#include <fstream>
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
	ofstream output;
	Tree(State *newStart, State * newGoal)
	{
		string s = "start";
		starting = new Node(*newStart, NULL, s);
		goal = newGoal;
	}

	~Tree()
	{
	}
	/*Get the plan*/
	Node * plan() {
		bool found = false;
		Node * planNode = new Node();
		(buildTree(starting, 0, found, *planNode));
		//RETURN LEFT CHILD FORCED!
		saveOutput(*planNode->leftChild);
		return planNode->leftChild;
	}

	/*Output the plan to a file*/
	void saveOutput(Node & planNode) {
		output.open("output.txt");
		Node * ptr = &planNode;
		int count = 0;
		while (ptr != NULL){
			output << "\n";
			output << "-------| " + to_string(count) + " |-------\n";
			output << ptr->plan;
			count++;
			ptr = ptr->parent;
		}
		output.close();
	}
	void drawState(State & state, ofstream& myfile) {
		string space = "       ";

		myfile << "|-------------|--------------|--------------|--------------|\n";
		myfile << "      l1              l2             l3             l4       \n";
	}

	/*For whatever reason, the plam node is the left child but it wont return? Instead,
	its parent is returned.*/
	Node* buildTree(Node * root, int level, bool &found, Node & planNode) {
		
		if (root && level < 6 ) {
			
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

