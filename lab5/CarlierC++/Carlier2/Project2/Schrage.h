#pragma once
#ifndef SCHRAGE_H_INCLUDED
#define SCHRAGE_H_INCLUDED

#include "Quest.h"

using namespace std;

extern int n;

class Schrage
{

public:

	Quest tab[1000];

	int Cmax;
	int Cmax_without;
	int Cmax_with;
	int number_of_tasks;
	vector<int> per;


	//    priority_queue<Quest,vector<Quest>,Nset> N;
	  //  priority_queue<Quest,vector<Quest>,Gset> G;

	friend bool operator<(const Quest& q1, const Quest& q2);
	//struct Nset;
	//struct Gset;

	bool Read(int numb);
	void Sort(int numb);
	void Display(int numb);
	int Schrage_without(int numb);
	int Schrage_with(int numb);

	Schrage();
	~Schrage();
};


#endif // SCHRAGE_H_INCLUDED
