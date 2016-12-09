#pragma once
#include "State.h"
#include "Node.h"


class Node
{
public:
	Node * futureStates[4];
	Node * parent;
	State current;
	Node();
	~Node();
	Node(State, Node *);
	State PickUp(State *, block);
	State Node::PutDown(State * , block, int);
};

