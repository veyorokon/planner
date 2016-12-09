#pragma once
#include <iostream>
#include <string>
#include "Record.h"
#include <iomanip>
#include <float.h>
#include <fstream>
#define MAXHASH 1000
#define HASHPRIME 769

using namespace std;

template <class T> class HashTable {


public:
	Record<T>* table;
	int size;
	/*Default constructor for the hash table.*/
	HashTable<T>::HashTable()
	{
		table = new Record<T>[MAXHASH];
		size = 0;
	}

	HashTable<T>::~HashTable()
	{
	}


	/*Overloads the << operator to print the hash table to cout. */
	friend ostream& operator<<(ostream& os, HashTable& me) {
		for (int i = 0; i < MAXHASH; i++) 
			os << "Index: "<< i << ". " << me.table[i] << endl;
		return os;
	}

	/* Inserts the key into the table. If the key is a duplicate, then the function
	returns false. Else the function returns true.*/
	bool HashTable<T>::insert(int key, T value, int& collisions) {
		int collides = 1, factor =0;
		int index = hash(key), home = index; //Quadratic hash on key
		collisions = collides;
		if (table[index].isEmpty()) return create(index, key, value, collisions); //If index is empty - create new record.
		collides++; //Increment collision count
		index = probe(home, key, factor); //Else double hash for new index
		while (!table[index].isEmpty() && !table[index].isTombstone()) {
			if (table[index].getKey() == key) {//Does that index have an equal key?
				if (!table[index].isTombstone()) {//If so, is it a tombstone?
					//cout << "Duplicate.";
					collisions = collides;//If it isn't a tombstone, return false;
					return 0;
				}
			}
			factor++;//quadratic probe for next index
			index = probe(home, key, factor);
			collides++; //update collisions
		}
		collisions = collides;
		//cout << index << ". Collisions: "<< collisions << ". Expected: "<< expectedCollisions();
		//cout << index;
		return create(index, key, value, collides);//create the node
	}

	/*Removes the key from the table. Returns true if the key was successfully removed. Otherwise,
	the function returns false. */
	bool HashTable<T>::remove(int key) {
		int index = hash(key), home = index, factor=0; //Declare vars
		if (table[index].getKey() == key) {
			table[index].kill();//kill index that has key.
			size--;
			//cout << "Collisions: "<< factor ;
			return true;//check if first hash index has key
		}
		index = probe(home, key, factor);//get probe index 
		while (factor < MAXHASH) {
			if (table[index].getKey() == key) {
				table[index].kill();//delete the index if it has the key
				size--;
				//cout << "Collisions: " << factor;
				return true;//return true if probe index has key
			}
			factor++;
			index = probe(home, key, factor);
		}
		return false;
	}

	/*Searches the table for the key, returns true if the key is found. Else, the function returns
	false. */
	bool HashTable<T>::find(int key, T& value) {
		int index = hash(key), home = index, factor=0; //Declare vars
		if (table[index].getKey() == key && !table[index].isTombstone()) {
			value = table[index].getValue();//save return value
			//cout << factor;
			return true;//check if first hash index has key
		}
		index = probe(home, key, factor);//get probe index 
		while (factor < MAXHASH) {
			if (table[index].getKey() == key && !table[index].isTombstone()) {
				value = table[index].getValue();//save return value
				//cout << factor;
				return true;//return true if probe index has key
			}
			factor++;
			index = probe(home, key, factor);
		}
		cout << "Not found" << endl;
		return false;
	}

	/*Returns the loading factor of the table.*/
	float HashTable<T>::alpha() {
		float a = (float(size) / MAXHASH);
		return a;
	}

	/*Returns the loading factor of the table.*/
	float HashTable<T>::expectedCollisions() {
		float a = alpha();
		float collisions = float(1 / (1 - a));
		collisions = floor(collisions + 0.5);
		return collisions;
	}

	/*Quadratic hash returns the row index modded by MAXHASH to insert key.*/
	int HashTable<T>::hash(int key) {
		return(key * key) % MAXHASH;
	}

	/*Probes the table for the next available slot using double hashing. Returns the first index found. Double
	hashing algorithm using a modified version of the hashing algorithm found:
	http://www.cs.princeton.edu/courses/archive/spr03/cs226/lectures/hashing.4up.pdf and includes a custom algorithm*/
	int HashTable<T>::probe(int home, int key, int factor) {
		unsigned int doubleHash = (HASHPRIME - (key % HASHPRIME));
		unsigned int index = (((factor*HASHPRIME+key)+(home/doubleHash))+HASHPRIME) %MAXHASH;
		return index;
	}

	/*Output the data to output files.*/
	void HashTable<T>::write(int collisions, float a) {
		ofstream myfile;
		ofstream ofile;
		
		myfile.open("Collisions.txt", ios::app);
		myfile << to_string(a) << " " << to_string(collisions) << "\n";
		myfile.close();

		ofile.open("Theory.txt", ios::app);
		ofile << to_string(a) << " " << to_string(expectedCollisions()) << "\n";
		ofile.close();
	}

	/*Assign key and value at index(row) in both table and data vectors.*/
	bool HashTable<T>::create(int index, int key, T value, int collisions) {
		table[index] = Record<T>(key, value);
		size++; 
		write(collisions, alpha());
		return true;
	}
};

