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
	State Node::PickUp(const State *, block);
	State Node::PutDown(const State * , block, int);
	State Node::UnStack(const State *, block);
	State Node::Stack(const State *, block, block);

};

