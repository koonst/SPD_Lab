#pragma once
#ifndef QUEST_H_INCLUDED
#define QUEST_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <queue>
#include <functional>

using namespace std;

class Quest
{
public:
	Quest();
	~Quest();
	int r, p, q;
	int task_number;
	//int l;
	int C;

	friend istream& operator >> (istream& enter, Quest& request);
	friend ostream& operator << (ostream& exit, Quest& request);


};

struct Nset
{
	bool operator()(const Quest& a, const Quest& b)
	{
		return a.r > b.r;
	}
};

struct Gset
{
	bool operator()(const Quest& a, const Quest& b)
	{
		return a.q < b.q;
	}
};
#endif // QUEST_H_INCLUDED
