#include <iostream>
#include <algorithm>


using namespace std;

int main()
{
    int IlZad, Cmax = 0, PierwM = 0;

    cout << "podaj liczbe zadan dla maszyn:" << "\n";

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


    //kolejnosc zadan

  /*  cout << "podaj kolejnosc pi dla zadan:" << "\n";

    for (int i = 0; i < IlZad; ++i)
    {
        cin >> kolejnosc[i];
    }
    */

    //algorytm Johnsona
    int num1, num2, krok = IlZad;
    int* Johnson = new int[krok];
    
    for (int j = 0; j < krok; ++j)
    {          
        //szukam najmniejszy czas zadania
        int min1 = maszyna1[0];
        int min2 = maszyna2[0];
        num1 = 0;
        num2 = 0;
        for (int i = 1; i < IlZad; ++i)
        {
            if (maszyna1[i] < min1)
            {
                min1 = maszyna1[i];
                num1 = i;
            }
            if (maszyna2[i] < min2)
            {
                min2 = maszyna2[i];
                num2 = i;
            }
        }
        cout << "num1 = " << num1+1 << " " << "min1 = " << min1 << "\n";
        cout << "num2 = " << num2+1 << " " << "min2 = " << min2 << "\n" << "\n";
        /////////////////////////////////
        // !! +"wycinam" najkrotsze zadanie
        if (min1 == min2)
        {
            if (num1 <= num2)
            {
                Johnson[j] = num1+1;
                maszyna1[num1] = 999;
                maszyna2[num1] = 999;               
            }
            else              
            {
                Johnson[krok-1] = num2+1;
                krok--;
                maszyna1[num2] = 999;
                maszyna2[num2] = 999;
                j--;
            }
        }
         
        if (min1 < min2)      
        {
             Johnson[j] = num1+1;
             maszyna1[num1] = 999;
             maszyna2[num1] = 999;
        }
        if (min1 > min2)
        {
             Johnson[krok - 1] = num2+1;
             krok--;
             maszyna1[num2] = 999;
             maszyna2[num2] = 999;
             j--;
        }
        
    }
    
    for (int i = 0; i < IlZad; ++i)
    {
        cout << Johnson[i] << " ";
    }
     

    //obliczenie Cmax


    /*

    for (int i = 0; i < IlZad; ++i)
    {

        PierwM += maszyna1[kolejnosc[i] - 1];
        Cmax = max(Cmax, PierwM);
        Cmax += maszyna2[kolejnosc[i] - 1];
        cout << Cmax << "\n";

    }

    cout << "Cmax wynosi:" << "\n" << Cmax << "\n";

    */
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