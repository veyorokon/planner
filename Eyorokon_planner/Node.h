#pragma once
#include "State.h"
#include "Node.h"
#include <vector>
using namespace std;

class Node
{
public:
	//vector<Node *> futureStates;
	Node * parent;
	Node * leftChild;
	Node * rightSibling;
	bool * checked;
	State current;
	string step[1];
	Node();
	~Node();
	Node(State, Node *);
	State Node::PickUp(const State *, block);
	State Node::PutDown(const State * , block, int);
	State Node::UnStack(const State *, block);
	State Node::Stack(const State *, block, block);
	void Node::getAllStates(block, block);
	void Node::Insert(Node * );
	//friend ostream& operator<<(std::ostream& os, const Node& obj);
};

