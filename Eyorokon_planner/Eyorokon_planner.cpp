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

	s1.location[0] = 12;
	s2 = s1;
	s1.location[0] = 10099;
	cout << s2.location[0] << endl;

	//States are passed by reference on Relation Calls
	s1.clear[3] = false;
	s3 = *(s1.Clear(&s1, 3));
	s1.clear[3] = false;
	cout << s1.clear[3];

	//Test holding pointers
	s1.clear[0] = true;
	n1.current = s1;
	n1.PickUp(&n1.current, 0);

	cout << "Node holding: " << n1.current.location[4] << endl;
	cout << "State 1 holding: " << s1.location[4] << endl;

	system("pause");
    return 0;
}

