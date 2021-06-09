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

	//*********************//
	//  task 20 speed 14!  //
	//*********************//

	int n;
	int start = GetTickCount64();
	Carlier ob;
	ob.Read();
	ob.Sort();
	ob.carlier(100000);
	

	ob.Display();
	//ob.Schrage_without();
	//ob.Schrage_with();
	int end = GetTickCount64();

	cout << "U: " << ob.carlier(100000) << endl;
	cout << "czas: " << end - start << " ms" << endl;
	return 0;
}

