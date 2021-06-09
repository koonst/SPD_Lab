#include "Carlier.h"

#define MAX_L 1000000

using namespace std;

#include <stack>

Carlier::Carlier()
{
	UB = 10000000;

}
Carlier::~Carlier() {}

int Carlier::carlier(int alter)
{

	stack <Quest*> alterstack;
	do
	{
		bool ifpop;
		Cmax = 0;
		int left = 99999;
		int right = 99999;
		int nr_c = 0;
		int r_c = 0;
		int p_sum = 0;
		int q_c = 0;
		int r_new_for_c = MAX_L;
		int q_new_for_c = MAX_L;
		int a = 0, b = 0, c = -1;
		int U = 0, LB = 0;

		U = Schrage_without();

		if (U < UB)
			UB = U;
		b = find_b(a, b, c);
		a = find_a(a, b, c);
		c = find_c(a, b, c);

		if (c == -1)
		{
			return UB;
		}


		nr_c = tab[c].task_number;
		int nowa_suma = 0;
		for (int i = c + 1; i <= b; i++)
		{
			r_new_for_c = min(r_new_for_c, tab[i].r);

			p_sum += tab[i].p;
			nowa_suma += tab[i].p;
			q_new_for_c = min(q_new_for_c, tab[i].q);
		}
		r_c = tab[c].r;
		q_c = tab[c].q;

		tab[c].r = max(tab[c].r, r_new_for_c + p_sum);
		LB = Schrage_with();
		if (LB < UB)
		{
			left = LB;
			if (left >= alter)
			{
				alterstack.push(tab);
				ifpop = true;

				//carlier(alter);
			}
			else
			{
				ifpop = false;
				for (int i = 0; i < number_of_tasks; i++)
				{
					if (nr_c == tab[i].task_number)
					{
						tab[i].r = r_c;
					}
				}
			}
		}




		tab[c].q = max(tab[c].q, q_new_for_c + p_sum);


		LB = Schrage_with();
		if (LB < UB)//&& c!=-1)
		{
			right = LB;

				if (right <= left)
				{

					for (int i = 0; i < number_of_tasks; i++)
					{
						if (nr_c == tab[i].task_number)
						{
							tab[i].q = q_c;
						}
					}
				}
				else
				{
					if (ifpop)
					{
						alterstack.pop();
						alterstack.push(tab);
					}
				}
			
		}

		alter = max(left, right);

		if ((right != 99999) || (left != 99999))
		{
			if (alterstack.empty() == false)
			{
				for (int i = 0; i < number_of_tasks; i++)
				{
					tab[i] = alterstack.top()[i];
				}
				alterstack.pop();
				alter = 99999;
			}
		}
	} while (alterstack.empty() == false);

	return UB;
}

int Carlier::find_a(int a, int b, int c)
{
	int sum_a = 0;
	for (a = 0; a <= b; a++)
	{
		sum_a = 0;
		for (int i = a; i <= b; i++)
		{
			sum_a += tab[i].p;
		}

		if (Cmax_without == (tab[a].r + sum_a + tab[b].q))
		{
			return a;
		}
	}
	return a;
}


int Carlier::find_b(int a, int b, int c)
{
	b = number_of_tasks - 1;
	for (int i = number_of_tasks - 1; i > 0; i--)
	{
		if (Cmax_without == (tab[i].C + tab[i].q))
		{
			b = i;
			break;
		}
	}
	return b;
}

int Carlier::find_c(int a, int b, int c)
{
	c = -1;
	//int i;
	for (int i = b; i >= a; i--) //by³o i=b; i>=a; i--  i=a; i<=b; i++
	{
		if (tab[i].q < tab[b].q)
		{
			c = i;
			//  cout << "c " << c << endl;
			break;
		}
	}
	return c;
}



