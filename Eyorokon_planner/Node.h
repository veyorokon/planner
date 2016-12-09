#pragma once
#include "State.h"
#include "Node.h"
#include <vector>
using namespace std;

class Node
{
public:
	vector<Node *> futureStates;
	Node * parent;
	State current;
	//string * steps[];
	Node();
	~Node();
	Node(State, Node *);
	State Node::PickUp(const State *, block);
	State Node::PutDown(const State * , block, int);
	State Node::UnStack(const State *, block);
	State Node::Stack(const State *, block, block);
	vector<Node *>& Node::getAllStates(block, block);
};

