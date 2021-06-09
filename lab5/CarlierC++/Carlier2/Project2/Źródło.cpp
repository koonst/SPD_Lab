#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <queue>
#include <vector>
#include "Carlier.h"
#include<windows.h>

using namespace std;



int main()
{
	int n;
	int numb = 400;
	double ar[400];
	long t;
	for (int i = 1; i < numb/10; ++i)
	{
		//int start = GetTickCount64();
		t = clock();
		Carlier ob;
		ob.Read(10*i);
		ob.Sort(10*i);

		ob.carlier(10*i);
		
		//ob.Display(i);
		cout << endl;
		int end = GetTickCount64();
		//cout << "czas: " << end - start << " ms" << endl;
		//ar[i - 1] = end - start;
		ar[i - 1] = (clock() - t) * 0.001;
	}
	//ob.Schrage_without();
	//ob.Schrage_with();
	

	for (int i = 0; i < 39; ++i)
		cout << ar[i] << endl;


	//cout << "U: " << ob.carlier() << endl;
	
	return 0;
}

