// Eyorokon_planner.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "State.h"
#include <iostream>
#include "Tree.h"
#include "Node.h"
#include "Tree.h"
using namespace std;


State * genStart();
State * genGoal();

int main()
{
	/*
	State s1;
	State s2;
	State s3;
	Node n1;

	s1.Location(&s1, 2, 3);
	s2 = s1;
	s1.Location(&s1, 2, 4);
	cout << s2.GetLocation( 2) << endl;

	//States are passed by reference on Relation Calls
	s1.Clear(&s1, 3);
	s3 = *(s1.Clear(&s1, 3));
	s1.NotClear(&s1, 3);
	cout << s3.IsBlockClear(3) << endl;
	
	//Test holding pointers, Future state
	s1.Clear(&s1, 2);
	n1.current = s1;
	State * newState;
	cout << "Test future state size: " << n1.futureStates.size() << endl;
	newState = &(n1.PickUp(&n1.current, 2));
	cout << "Test future state size: " << n1.futureStates.size() << endl;

	//Test Pickup
	cout << "Node holding: " << newState->GetHolding() << endl;
	cout << "State 1 holding: " << s1.GetHolding() << endl;
	cout << "Test empty location: " << newState->IsLocationEmpty(1)<<endl;
	newState = &(n1.UnStack(newState, 2));
	newState->Holding(newState, 4);

	//Test Putdown
	newState = &(n1.PutDown(newState,4, 2));
	cout << "Test holding " << newState->GetHolding() << endl;
	cout << "Test location " << newState->GetLocation(4) << endl;
	*/

	/*
	//Test getAllStates
	State sTest = *genStart();
	State sTest2 = sTest;
	Node nTest;
	nTest.current = sTest;
	
	nTest.getAllStates(0, 0);
	cout << "Testing Get All States. nTest (node): " << endl ;
	vector<Node *> fTest = nTest.futureStates;

	//Test state == overload
	cout << "Location of blk1: " << sTest.GetLocation(1) << endl;

	sTest.Location(&sTest, 1, 2);
	sTest.NotLocation(&sTest, 1, 2);
	sTest.Location(&sTest, 1, 0);
	cout << "Testing state overload == " << (sTest == sTest2) << endl;
	*/

	State sTest = *genStart();
	State gTest = *genGoal();
	Tree planner(&sTest, &gTest);
	
	Node * root = planner.plan();

	
	system("pause");
    return 0;
}

State * genStart() {
	State s1;
	s1.On(&s1, 0, 1);//A on B
	s1.On(&s1, 1, 2);//B on C
	s1.On(&s1, 3, 4);//D on E
	s1.On(&s1, 5, 6);//F on G

	s1.Clear(&s1, 0);//A clear
	s1.Clear(&s1, 3);//D clear
	s1.Clear(&s1, 5);//F clear

	s1.Location(&s1, 0, 0);//A Location 0
	s1.Location(&s1, 1, 0);//B Location 0
	s1.Location(&s1, 2, 0);//C Location 0
	s1.Location(&s1, 3, 1);//D Location 1
	s1.Location(&s1, 4, 1);//E Location 1
	s1.Location(&s1, 5, 3);//F Location 3
	s1.Location(&s1, 6, 3);//G Location 3

	s1.Table(&s1, 2);//C Table
	s1.Table(&s1, 4);//E Table
	s1.Table(&s1, 6);//G Table

	return &s1;
}

State * genGoal() {
	State s1;
	s1.On(&s1, 1, 2);//B on C
	s1.On(&s1, 3, 4);//D on E
	s1.On(&s1, 5, 6);//F on G

	s1.Clear(&s1, 0);//A clear
	s1.Clear(&s1, 1);//B clear
	s1.Clear(&s1, 3);//D clear
	s1.Clear(&s1, 5);//F clear

	
	s1.Location(&s1, 1, 0);//B Location 0
	s1.Location(&s1, 2, 0);//C Location 0
	s1.Location(&s1, 3, 1);//D Location 1
	s1.Location(&s1, 4, 1);//E Location 1
	s1.Location(&s1, 0, 2);//A Location 2
	s1.Location(&s1, 5, 3);//F Location 3
	s1.Location(&s1, 6, 3);//G Location 3

	s1.Table(&s1, 0);//A Table
	s1.Table(&s1, 2);//C Table
	s1.Table(&s1, 4);//E Table
	s1.Table(&s1, 6);//G Table

	return &s1;
}
