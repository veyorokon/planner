#pragma once
#include "State.h"
#include "Relation.h"
#include "Node.h"
#include <fstream>
#include <algorithm>

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
		int phase = 0;

		//correct count
		while (ptr != NULL) {
			phase++;
			ptr = ptr->parent;
		}
		ptr = &planNode;
		while (ptr != NULL){
			output << "\n\n";
			output << "|--------------|--------------| " 
				+ to_string(phase) + " |---------------|--------------| \n";
			drawState(ptr->current, output);
			output << "                          "<< ptr->plan;
			phase--;
			ptr = ptr->parent;
		}
		output.close();
	}


	//http://stackoverflow.com/questions/890164/how-can-i-split-a-string-by-a-delimiter-into-an-array
	vector<string> explode(const string& str, const char& ch) {
		string next;
		vector<string> result;

		// For each character in the string
		for (string::const_iterator it = str.begin(); it != str.end(); it++) {
			// If we've hit the terminal character
			if (*it == ch) {
				// If we have some characters accumulated
				if (!next.empty()) {
					// Add them to the result vector
					result.push_back(next);
					next.clear();
				}
			}
			else {
				// Accumulate the next character into the sequence
				next += *it;
			}
		}
		if (!next.empty())
			result.push_back(next);
		return result;
	}

	void drawState(State & state, ofstream& myfile) {
		string space = "       ";
		//create 2d map
		int height = 7, width = 4;
		string** array2D = 0;
		array2D = new string*[height];

		for (int h = 0; h < height; h++)
		{
			array2D[h] = new string[width];
			for (int w = 0; w < width; w++)
			{
				array2D[h][w] = " ";
			}
		}

		//PROCESS VECTOR
		vector<int> order;
		vector<int> heights;
		getOrdering(heights,  order,state);
		cout << "Print order " << endl;
		string ordering = "";
		for (int i = 0; i < order.size(); i++) {
			cout << order[i] << " ";
		}		
		cout << endl;
		for (int i = 0; i < heights.size(); i++) {
			cout << heights[i] << " ";
		}

		int ptr =1;
		int col = 4, row =6;
		while( col >= 0 && ptr < order.size()) {
			while( row >= 0 && ptr < order.size()) {
				if (order[(order.size() - ptr)] == -1) {
					col--;
					row = 6;
				}
				else {
					array2D[row][col] = to_string(order[(order.size()-ptr)]);
					cout << "HKHK: " << array2D[row][col] << endl;
					row -= 1;
				}
				ptr++;
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << array2D[i][j] << " ";
			}
			cout << endl;
		}


		cout << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				myfile << space << array2D[i][j] << space;
			}
			//cout << endl;
			myfile << "\n";
		}
		myfile << "|-------------|--------------|--------------|--------------|\n";
		myfile << "      l0              l1             l2             l3       \n\n\n";
	}

	void getOrdering( vector<int>& heights, vector<int>& order, State & state) {
		int ** locations = state.getLocations();
		int held = locations[4][0];
		vector<int> ordering;
		order.push_back(held);
		
		for (int i = 0; i < 4; i++) {
			block top = getTopBlock(locations, state, i); //Get the topmost block for row
			addToVec(heights, order, state, top);
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


	void addToVec(vector<int>& heights, vector<int>& order, State & state, block blk) {
		int height = 0;
		order.push_back(blk);
		if (blk == -1) {
			heights.push_back(height);
			return;
		}

		while (blk != -1) {
			height++;
			blk = state.GetOn(blk);
			order.push_back(blk); //check the next block
		}
		heights.push_back(height);
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

