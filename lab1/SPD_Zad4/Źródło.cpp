#include <iostream>
#include <algorithm>


using namespace std;

int main()
{
    int IlZad, IlM;

    cout << "podaj liczbe zadan:" << "\n";
    cin >> IlZad;

    cout << "podaj liczbe maszyn:" << "\n";
    cin >> IlM;


    // tworzenie tablicy maszyny[ilosc maszyn][liczba zadan]
    int** maszyny = new int* [IlM];
    int** maszynyC = new int* [IlM];
    for (int i = 0; i < IlM; ++i)
    {
        maszyny[i] = new int[IlZad];
        maszynyC[i] = new int[IlZad];
    }

    //tablica kolejnosci wypelniania zadan
    //int* kolejnosc = new int[IlZad];


    for (int i = 0; i < IlZad; ++i)
    {
        cout << "podaj czas wypelniania zadania " << i + 1 << ":" << "\n";

        for (int j = 0; j < IlM; ++j)
        {
            cin >> maszyny[j][i];
            maszynyC[j][i] = maszyny[j][i];
        }
    }

    int* maszyna11 = new int [IlZad];
    int* maszyna22 = new int [IlZad];


    /*for (int i = 0; i < IlZad; i++)
        kolejnosc[i] = i + 1;*/

    /////////////////////algorytm Johnsona//////////////////////


    //tworzê dwie maszyny dla algorytmu
    for (int j = 0; j < IlZad; ++j)
        for (int i = 0; i < (IlM+1)/2; ++i)        
    {
        maszyna11[j] += maszyny[i][j];
        maszyna22[j] += maszyny[IlM - i - 1][j];
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
                Johnson[j] = num1 + 1;
                maszyna11[num1] = 999;
                maszyna22[num1] = 999;
            }
            else
            {
                Johnson[krok - 1] = num2 + 1;
                krok--;
                maszyna11[num2] = 999;
                maszyna22[num2] = 999;
                j--;
            }
        }

        if (min1 < min2)
        {
            Johnson[j] = num1 + 1;
            maszyna11[num1] = 999;
            maszyna22[num1] = 999;
        }
        if (min1 > min2)
        {
            Johnson[krok - 1] = num2 + 1;
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

    for (int i = 0; i < IlM; ++i)
    {
        for (int j = 0; j < IlZad; ++j)
        {
            maszynyC[i][j] = maszyny[i][j];
        }
    }


    for (int i = 1; i < IlM; ++i)
    {
        maszynyC[i][Johnson[0] - 1] += maszynyC[i - 1][Johnson[0] - 1];
    }
    for (int i = 1; i < IlZad; ++i)
    {
        maszynyC[0][Johnson[i] - 1] += maszynyC[0][Johnson[i - 1] - 1];
    }


    for (int i = 1; i < IlM; ++i)
    {
        for (int j = 1; j < IlZad; ++j)
        {
            maszynyC[i][Johnson[j] - 1] += max(maszynyC[i - 1][Johnson[j] - 1], maszynyC[i][Johnson[j - 1] - 1]);
        }
    }
    cout << "Cmax wynosi: " << maszynyC[IlM - 1][Johnson[IlZad - 1] - 1] << "\n";
    cout << endl;

    delete[] maszyna11;
    maszyna11 = nullptr;

    delete[] maszyna22;
    maszyna22 = nullptr;   

    delete[] Johnson;
    Johnson = nullptr;

    delete[] maszyny;
    maszyny = nullptr;

    delete[] maszynyC;
    maszynyC = nullptr;


    system("pause");
    return 0;
}