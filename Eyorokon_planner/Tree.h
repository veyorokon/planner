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

		vector<int> order;
		getOrdering(order, planNode.current);
		cout << "Print order " << endl;
		for (int i = 0; i < order.size(); i++) {
			cout << order[i] << " ";
		}

	}
	void drawState(State & state, ofstream& myfile) {
		string space = "       ";
		

		//if(held != -1)
		//myfile << "                                               holding: Block"+to_string(held)+"\n";
		
		myfile << "|-------------|--------------|--------------|--------------|\n";
		myfile << "      l1              l2             l3             l4       \n";
	}

	void getOrdering(vector<int>& order, State & state) {
		int ** locations = state.getLocations();
		int held = locations[4][0];
		vector<int> ordering;
		order.push_back(held);
		
		for (int i = 0; i < 4; i++) {
			block top = getTopBlock(locations, state, i); //Get the topmost block for row
			addToVec(order, state, top);
		}
	}

	/*Returns the top most block*/
	block getTopBlock(int** locations, State & state, int row) {
		for (int j = 0; j < 7; j++) {
			block top = locations[row][j];
			if (top != -1) {//Check if block is at location
				if (state.IsBlockClear(j)) {//Check if it's the top
					return j;
				}
			}
		}
		return -1;
	}


	void addToVec(vector<int>& order, State & state, block blk) {
		order.push_back(blk);
		if (blk == -1) return;

		while (blk != -1) {
			blk = state.GetOn(blk);
			order.push_back(blk); //check the next block
		}
		//order.push_back(-1); //end of row
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

