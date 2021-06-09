#pragma once
#ifndef CARLIER_H_INCLUDED
#define CARLIER_H_INCLUDED

#define MAX_L 1000000

#include "Schrage.h"

using namespace std;


class Carlier : public Schrage
{
public:
    Carlier();
    ~Carlier();
    Quest tab2[3000];
    int UB;//=MAX_L;






    int carlier(int numb);
    int find_a(int a, int b, int c, int numb);
    int find_b(int a, int b, int c, int numb);
    int find_c(int a, int b, int c);


};



#endif // CARLIER_H_INCLUDED
