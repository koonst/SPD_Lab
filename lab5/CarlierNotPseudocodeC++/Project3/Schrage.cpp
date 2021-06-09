#include "Schrage.h"
#include "Carlier.h"

using namespace std;

int Schrage::Schrage_with()
{
	//	int number_of_tasks;
		//int Cmax_temp=0;
	Cmax = 0;
	int t = tab[0].r;
	Cmax_with = 0;
	//number_of_tasks=tab[0].r;
	//tab[0].r=0;
	Quest l, e; //aktualnie wykonywane zadanie
	priority_queue<Quest, vector<Quest>, Nset> N;
	priority_queue<Quest, vector<Quest>, Gset> G;


	l.q = 0; //by³o l=10000000;
	for (int i = 0; i < number_of_tasks; i++)
	{
		N.push(tab[i]);
	}
	while (!G.empty() || !N.empty())
	{
		while (!N.empty() && N.top().r <= t)
		{
			e = N.top();
			G.push(e); // zadanie zaczyna sie wykonywac
			N.pop();
			if (e.q > l.q)
			{
				l.p = t - e.r;
				t = e.r;
				if (l.p > 0)
				{
					G.push(l);
				}
			}
		}

		if (G.empty())
			t = N.top().r;
		else
		{
			e = G.top();
			G.pop();
			l = e;
			t = t + e.p;
			Cmax = max(Cmax, t + e.q);
		}
		Cmax_with = Cmax;
	}
	return Cmax;
}

int Schrage::Schrage_without()
{

	//int number_of_tasks;
	//int Cmax=0;
	int t = 0;//tab[0].r;
//	int k=0;
	//number_of_tasks=tab[0].r;
	//tab[0].r=0;
	Cmax = 0;
	//Cmax_without=0;
	t = tab[0].r;
	priority_queue<Quest, vector<Quest>, Nset> N;
	priority_queue<Quest, vector<Quest>, Gset> G;

	for (int i = 0; i < number_of_tasks; i++)
	{
		N.push(tab[i]);
	}
	int j = 0;
	while (!G.empty() || !N.empty())
	{
		while (!N.empty() && N.top().r <= t)
		{
			G.push(N.top());
			N.pop();
		}
		if (G.empty())
			t = N.top().r;
		else
		{
			tab[j] = G.top();
			//per.push_back(G.top().task_number);
			t = t + G.top().p;
			//tab[j].task_number=j;

			Cmax = max(Cmax, t + G.top().q);//t+tab[j].q);//G.top().q);
			G.pop();
			tab[j].C = t;
			//cout << "j " << j << endl;
			j++;


		}
		Cmax_without = Cmax;


	}
	return Cmax;
}

bool Schrage::Read()
{
	ifstream file;
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	file.open("SCHRAGE5.DAT", ios::in);
	//int n;
	file >> number_of_tasks;
	//number_of_tasks=n+1;
	//number_of_tasks=n+1;
	for (int i = 0; i < number_of_tasks; i++)
	{
		file >> tab[i];
		tab[i].task_number = i;
	}


	file.close();
	//tab[0].r=number_of_tasks;
	return true;
}

void Schrage::Sort()
{
	for (int i = 0; i < number_of_tasks; i++)
		for (int j = 0; j < number_of_tasks - 1; j++)
			if (tab[j].r > tab[j + 1].r)
				swap(tab[j], tab[j + 1]);
}

void Schrage::Display()
{
	for (int i = 0; i < number_of_tasks; i++)
		cout << tab[i];
}

Schrage::Schrage() {}
Schrage::~Schrage() {}
