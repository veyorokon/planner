// Eyorokon_planner.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "State.h"
#include <iostream>
#include "Tree.h"
#include "Node.h"

using namespace std;

int main()
{

	State s1;
	State s2;
	State s3;
	Node n1;

	s1.Location(&s1, 2, 3);
	s2 = s1;
	s1.Location(&s1, 2, 4);
	cout << s2.GetLocation(&s1, 2) << endl;

	//States are passed by reference on Relation Calls
	s1.Clear(&s1, 3);
	s3 = *(s1.Clear(&s1, 3));
	s1.NotClear(&s1, 3);
	cout << s3.IsBlockClear(3) << endl;
	
	//Test holding pointers
	s1.Clear(&s1, 2);
	n1.current = s1;
	State newState;
	newState = n1.PickUp(&n1.current, 2);
	
	cout << "Node holding: " << newState.GetHolding() << endl;
	cout << "State 1 holding: " << s1.GetHolding() << endl;
	cout << "Test empty location" << newState.IsLocationEmpty(1)<<endl;

	system("pause");
    return 0;
}

