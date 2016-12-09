#pragma once
class Relation {
#define SIZE 7
public:
	int data[SIZE];

	Relation() {
		for (int i = 0; i < SIZE; i++) {
			data[i] = -1;
		}
	}

	void operator = (Relation const relation) {
		for (int i = 0; i < SIZE; i++) {
			data[i] = relation.data[i];
		}
	}

	int& operator[](int index) {
		return data[index];
	}
};