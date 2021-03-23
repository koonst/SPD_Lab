#include <iostream>
#include <algorithm>
using namespace std;
void swap(int* a, int i, int j)
{
    int s = a[i];
    a[i] = a[j];
    a[j] = s;
}
bool NextSet(int* a, int n)
{
    int j = n - 2;
    while (j != -1 && a[j] >= a[j + 1]) j--;
    if (j == -1)
        return false; // wiecej permutacji nie ma
    int k = n - 1;
    while (a[j] >= a[k]) k--;
    swap(a, j, k);
    int l = j + 1, r = n - 1; // sortuje pozostala czesc kolejnosci
    while (l < r)
        swap(a, l++, r--);
    return true;
}
void Print(int* a, int n)  // 
{
    static int num = 1; //
    //cout.width(3); // 
    cout << num++ << ": ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    
}
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
    int* kolejnosc = new int[IlZad];


    for (int i = 0; i < IlZad; ++i)
    {
        cout << "podaj czas wypelniania zadania " << i + 1 << ":" << "\n";

        for (int j = 0; j < IlM; ++j)
        {
            cin >> maszyny[j][i];
            maszynyC[j][i] = maszyny[j][i];
        }
    }



    for (int i = 0; i < IlZad; i++)
        kolejnosc[i] = i + 1;
  
    //obliczenie Cmax

    for (int i = 1; i < IlM; ++i)
    {
        maszynyC[i][kolejnosc[0] - 1] += maszynyC[i - 1][kolejnosc[0] - 1];
    }
    for (int i = 1; i < IlZad; ++i)
    {
        maszynyC[0][kolejnosc[i] - 1] += maszynyC[0][kolejnosc[i - 1] - 1];
    }


    for (int i = 1; i < IlM; ++i)
    {
        for (int j = 1; j < IlZad; ++j)
        {
            maszynyC[i][kolejnosc[j] - 1] += max(maszynyC[i - 1][kolejnosc[j] - 1], maszynyC[i][kolejnosc[j - 1] - 1]);
        }
    }

    cout << "dla kolejnosci ";
    Print(kolejnosc, IlZad);
    cout << "Cmax wynosi: " << maszynyC[IlM - 1][kolejnosc[IlZad - 1] - 1] << "\n";
    cout << endl;


    int minim = maszynyC[IlM - 1][kolejnosc[IlZad - 1] - 1];//szukam minimum Cmax

    int* minkol = new int[IlZad];
    for (int i = 0; i < IlZad; ++i)//kolejnosc zadan dla minimum Cmax
    {
        minkol[i] = kolejnosc[i];
    }


    while (NextSet(kolejnosc, IlZad))
    {

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
            maszynyC[i][kolejnosc[0] - 1] += maszynyC[i - 1][kolejnosc[0] - 1];
        }
        for (int i = 1; i < IlZad; ++i)
        {
            maszynyC[0][kolejnosc[i] - 1] += maszynyC[0][kolejnosc[i - 1] - 1];
        }


        for (int i = 1; i < IlM; ++i)
        {
            for (int j = 1; j < IlZad; ++j)
            {
                maszynyC[i][kolejnosc[j] - 1] += max(maszynyC[i - 1][kolejnosc[j] - 1], maszynyC[i][kolejnosc[j - 1] - 1]);
            }
        }
        cout << "dla kolejnosci ";
        Print(kolejnosc, IlZad);
        cout << "Cmax wynosi: " << maszynyC[IlM - 1][kolejnosc[IlZad - 1] - 1] << "\n";
        cout << endl;

        if (minim > maszynyC[IlM - 1][kolejnosc[IlZad - 1] - 1])//szukam minimum Cmax
        {
            minim = maszynyC[IlM - 1][kolejnosc[IlZad - 1] - 1];

            for (int k = 0; k < IlZad; ++k)//kolejnosc zadan dla minimum Cmax
            {
                minkol[k] = kolejnosc[k];
            }
        }
    }

    

    cout << "minimalny Cmax wynosi: " << minim << endl;
    cout << "dla kolejnosci: ";
    for (int i = 0; i < IlZad; ++i)
    {
        cout << minkol[i] << " ";
    }

    cin.get(); cin.get();

    delete[] maszyny;
    maszyny = nullptr;

    delete[] maszynyC;
    maszynyC = nullptr;

    delete[] kolejnosc;
    kolejnosc = nullptr;

    delete[] minkol;
    minkol = nullptr;


    system("pause");
    return 0;
}