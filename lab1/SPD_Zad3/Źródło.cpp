#include <iostream>
#include <algorithm>


using namespace std;

int main()
{
    int IlZad, Cmax = 0, PierwM = 0;

    cout << "podaj liczbe zadan dla  dwoch maszyn:" << "\n";

    cin >> IlZad;
    
    int* maszyna1 = new int[IlZad];
    int* maszyna2 = new int[IlZad];
    int* kolejnosc = new int[IlZad];

    cout << "podaj czas wypelniania zadan dla maszyny 1:" << "\n";

    for (int i = 0; i < IlZad; ++i)
    {
        cin >> maszyna1[i];
    }

    cout << "podaj czas wypelniania zadan dla maszyny 2:" << "\n";

    for (int i = 0; i < IlZad; ++i)
    {
        cin >> maszyna2[i];
    }

    /////////////////////algorytm Johnsona//////////////////////

    //tworzê kopie dla maszyn, bo bêdê wewn¹trz zmieniaæ wartoœci

    int* maszyna11 = new int[IlZad];
    int* maszyna22 = new int[IlZad];

    for (int i = 0; i < IlZad; ++i)
    {
        maszyna11[i] = maszyna1[i];
        maszyna22[i] = maszyna2[i];
    }

    int num1, num2, krok = IlZad;
    int* Johnson = new int[krok];
    
    for (int j = 0; j < krok; ++j)
    {          
        //szukam najmniejszy czas zadania
        int min1 = maszyna11[0];
        int min2 = maszyna22[0];
        num1 = 0;
        num2 = 0;
        for (int i = 1; i < IlZad; ++i)
        {
            if (maszyna11[i] < min1)
            {
                min1 = maszyna11[i];
                num1 = i;
            }
            if (maszyna22[i] < min2)
            {
                min2 = maszyna22[i];
                num2 = i;
            }
        }
        
        /////////////////////////////////
        // !! +"wycinam" najkrotsze zadanie, przypisujê du¿¹ wartoœæ dla czasu wykonania znalezionego
        //numeru zadania, równie¿ w³aœnie zmieniam wartoœci dlatego stworzy³em kopii tablic
        if (min1 == min2)
        {
            if (num1 <= num2)
            {
                Johnson[j] = num1+1;
                maszyna11[num1] = 999;
                maszyna22[num1] = 999;               
            }
            else              
            {
                Johnson[krok-1] = num2+1;
                krok--;
                maszyna11[num2] = 999;
                maszyna22[num2] = 999;
                j--;
            }
        }
         
        if (min1 < min2)      
        {
             Johnson[j] = num1+1;
             maszyna11[num1] = 999;
             maszyna22[num1] = 999;
        }
        if (min1 > min2)
        {
             Johnson[krok - 1] = num2+1;
             krok--;
             maszyna11[num2] = 999;
             maszyna22[num2] = 999;
             j--;
        }
        
    }
    
    cout << "\n";
    for (int i = 0; i < IlZad; ++i)
    {
        cout << Johnson[i] << " ";
    }
    cout << "\n";
     

    //obliczenie Cmax


    

    for (int i = 0; i < IlZad; ++i)
    {

        PierwM += maszyna1[Johnson[i] - 1];
        Cmax = max(Cmax, PierwM);
        Cmax += maszyna2[Johnson[i] - 1];


    }

    cout << "Cmax wynosi: " << Cmax << "\n";

    
    delete[] maszyna1;
    maszyna1 = nullptr;

    delete[] maszyna2;
    maszyna2 = nullptr;

    delete[] kolejnosc;
    kolejnosc = nullptr;

    delete[] Johnson;
    Johnson = nullptr;


    system("pause");
    return 0;
}