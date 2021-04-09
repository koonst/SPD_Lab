#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/// funkcja obliczenia Cmaxa dla zadanej tablicy maszyny[][] i zapisywanie kolejnosci, jesli Cmax na razie najmniejszy
//do tablicy minimkol, warto�� Cmax zapisuje do dodatkowej ostatniej kom�rki minimkol[]

int* ObliczCmax(int IloscMaszyn, int IloscZadan, int** maszyny, int* kolejnosc, int* minimkol)
{
    for (int i = 1; i < IloscMaszyn; ++i)
    {
        maszyny[i][kolejnosc[0] - 1] += maszyny[i - 1][kolejnosc[0] - 1];
    }
    for (int i = 1; i < IloscZadan; ++i)
    {
        maszyny[0][kolejnosc[i] - 1] += maszyny[0][kolejnosc[i - 1] - 1];
    }
    //Oper = maszyny[0][0];

    for (int i = 1; i < IloscMaszyn; ++i)
    {
        for (int j = 1; j < IloscZadan; ++j)
        {
            maszyny[i][kolejnosc[j] - 1] += max(maszyny[i - 1][kolejnosc[j] - 1], maszyny[i][kolejnosc[j - 1] - 1]);
        }
    }
    if (minimkol[IloscZadan] > maszyny[IloscMaszyn - 1][kolejnosc[IloscZadan - 1] - 1])//szukam minimum Cmax
    {
        minimkol[IloscZadan] = maszyny[IloscMaszyn - 1][kolejnosc[IloscZadan - 1] - 1];

        for (int l = 0; l < IloscZadan; ++l)//kolejnosc zadan dla minimum Cmax
        {
            minimkol[l] = kolejnosc[l];
        }


    }
    return minimkol;
}



///

int modyfikacja(int IloscMaszyn, int IloscZadan, int** maszyny, int* minimkol)
{
    int NumOper;
    int Oper;
    int NumZad;
    int DlOper;
    int rozm = IloscMaszyn + 2;
    int kopija[50][600];


    for (int ii = 0; ii < IloscMaszyn; ++ii)
    {
        for (int jj = 0; jj < IloscZadan; ++jj)
        {
            kopija[ii][jj] = maszyny[ii][minimkol[jj]-1];                                                 
        }
    }

    for (int i = 0; i < IloscMaszyn; ++i)
    {
        kopija[i][IloscZadan] = 0;
    }


    {
        kopija[IloscMaszyn][0] = 0;
    }


    NumOper = 1;
    NumZad = 1;
    Oper = kopija[0][0];
    DlOper = kopija[0][0];
    int zad = 0, masz = 0;
    
    


    while ((masz < IloscMaszyn-1) || (zad < IloscZadan-1))
    {
            
                if (kopija[masz + 1][zad] > kopija[masz][zad+1])
                {
                    NumOper = minimkol[zad];
                    Oper = kopija[masz+1][zad];
                    masz++;
                }
                if (kopija[masz + 1][zad] <= kopija[masz][zad+1])
                {
                    NumOper = minimkol[zad + 1];
                    Oper = kopija[masz][zad+1];
                    zad++;
                }
                if (Oper > DlOper)
                {
                    NumZad = NumOper;
                    DlOper = Oper;
                }
            
        
    }
    if (kopija[IloscMaszyn-1][IloscZadan-1] > DlOper)
    {
        NumZad = minimkol[IloscZadan-1]; 
    }

    return NumZad;
}






int main()
{
    int IlZad, IlM;

    cout << "podaj liczbe zadan:" << "\n";
    cin >> IlZad;

    cout << "podaj liczbe maszyn:" << "\n";
    cin >> IlM;


    // tworzenie tablicy maszyny[ilosc maszyn][liczba zadan]
    int** maszyny = new int* [IlM+2];
    int** maszynyC = new int* [IlM+2];

    for (int i = 0; i < IlM; ++i)
    {
        maszyny[i] = new int[IlZad+2];
        maszynyC[i] = new int[IlZad+2];
    }
    //tablica wspomagaj�ca dla permutacji kolejno�ci wype�niania zada� w algorytmie neh
    int* nehwspom = new int[IlZad+1];

    //tablica kolejnosci wypelniania zadan dla r�nych permutacji w algorytmie neh
    int* kolejnosc = new int[IlZad+1];


    for (int i = 0; i < IlZad; ++i)
    {
        cout << "podaj czas wypelniania zadania " << i + 1 << ":" << "\n";
        nehwspom[i] = 1;   //przy okazji przypisuj� warto�ci do tablicy wspomagaj�cej dla neh
        kolejnosc[i] = 1;
        for (int j = 0; j < IlM; ++j)
        {
            cin >> maszyny[j][i];
            maszynyC[j][i] = maszyny[j][i];
        }
    }

    cout << endl;




    //inicjuj� dwuwymiarow� tabel� [ilo�� zada�][2], pierwszy rz�d to suma czas�w wszystkich operacji na
    // wszystkich maszynach dla poszczeg�lnych zada� a drugi to numer zadania czasy kt�rego sumuj� w
    // pierwszym rz�dzie, taka sobie "numeracja" sum dla konkretnych zada� 
    // na razie zadania po kolei

    int** sumaczasow = new int* [IlZad+1];
    int* minkol = new int[IlZad + 2]; // tablica kolejno�ci wype�niania zada� z minimalnym Cmax
    int* mod = new int[IlZad + 2];
    minkol[IlZad] = 99999;

    for (int i = 0; i < IlZad; ++i)
    {
        sumaczasow[i] = new int[2];
        sumaczasow[i][0] = 0;
        sumaczasow[i][1] = i + 1;    //od razu numeruje zadania
        minkol[i] = 0;
    }

    //zapisuj� do komurek tabeli sumaczasow sum� operacji dla poszczeg�lnych zada�
    for (int i = 0; i < IlZad; ++i)
    {
        for (int j = 0; j < IlM; ++j)
        {
            sumaczasow[i][0] += maszyny[j][i];
        }
    }

    //sortowanie nierosn�co, bombelkowe, najd�u�sze ale
    //jestem zbyt leniwy �eby co� skomplikowanego pisa�
    //!z zachowaniem numer�w zada�!
    int temp1, temp2;
    for (int i = 0; i < IlZad - 1; ++i)
    {
        for (int j = i + 1; j < IlZad; ++j)
        {
            if (sumaczasow[i][0] < sumaczasow[j][0])
            {
                temp1 = sumaczasow[i][0];
                sumaczasow[i][0] = sumaczasow[j][0];
                sumaczasow[j][0] = temp1;
                temp2 = sumaczasow[i][1];           //tutaj zmieniam numery zada�
                sumaczasow[i][1] = sumaczasow[j][1];//tu
                sumaczasow[j][1] = temp2;           //i tu
            }
        }
    }



    ///////////ALGORYTM NEH//////////

    int modyfik; //dla modyfikacji


    //tablela kolejnosc z tymczasow� kolejno�ci� dla pierwszego elementu
    kolejnosc[0] = sumaczasow[0][1];
    //i wspomagaj�ca r�wnie�
    nehwspom[0] = sumaczasow[0][1];

    for (int i = 1; i < IlZad; ++i) //ile razy bierzemy warto�ci z posortowanej tabeli sum czas�w
    {
        minkol[i + 1] = 99999;
        //kopiuj� warto�ci poprzedniej kolejnosci do wspomagaj�cej tabeli nehwspom
        for (int g = 0; g < i; ++g)
        {
            nehwspom[g] = kolejnosc[g];
            //algorytm stworzenia kolejnosci permutacji b�dzie taki, �e
            //bierz� tablic� nehwspom[] i wstawiam nast�pny element na 
            //miejsce 1, 2, i td po kolei
        }

        for (int j = 0; j < i + 1; ++j) //ile permutacji, r�wnie� na kt�re miejsce wstawiam nast�pny element
        {
            int k = 0;

            //tworz� now� tabele kolejno��[]
            for (int n = 0; n < i + 1; ++n) //to taki "indykator" miejsca gdzie wstawiam element 
            {
                if (n == j) //je�li indykator r�wny numeru permutacji to wstawiamy tu nowy i-ty element
                {
                    kolejnosc[n] = sumaczasow[i][1];
                }
                else
                {
                    kolejnosc[n] = nehwspom[k]; //inaczej wstawiamy element z nehwspom - poprzedniej tablicy kolejno�ci dla i-1
                    k++;
                }
            }

            //obliczam Cmaxa wyliczonej kolejno�ci////

            for (int ii = 0; ii < IlM; ++ii)
            {
                for (int jj = 0; jj < IlZad; ++jj)
                {
                    maszynyC[ii][jj] = maszyny[ii][jj]; //w funkcji wyliczania Cmax zmieniam tabel� maszyny
                                                        //wi�c tworz� kopi� i z niej pracuj�
                }
            }

            minkol = ObliczCmax(IlM, i + 1, maszynyC, kolejnosc, minkol);

            ///////////////////////////////////////////


        }
        for (int gg = 0; gg < i + 1; ++gg) // po obliczaniu wszystkich Cmax�w dla i-tego elementu wybieram
        {                                  //kolejno�� z najmniejszym Cmax
            kolejnosc[gg] = minkol[gg];    //i z niej dalej b�d� pracowa�, b�dzie ona wspomagaj�c� tabel� nehwspom[]
        }                                  //dla nast�pnej i+1 -ej kolejno�ci


        ///////////modyfikacja///////////


        modyfik = modyfikacja(IlM, i + 1, maszyny, minkol);

        //tworze tabele numerow zadan bez tego zadania z najdluzsza operacja

        int kk = 0;
        for (int gg = 0; gg < i+1; ++gg)
        {
            
            if (minkol[gg] != modyfik)
            {
                mod[kk] = minkol[gg];//tabela wspomagajaca dla kolejnosci zamiast tabeli [nehwspom]
                kk++;
            }
        }

        //i jeszcze razik tworze wszystkie mozliwe kolejnosci

        minkol[i + 1] = 99999;

        for (int j = 0; j < i + 1; ++j) //ile permutacji, r�wnie� na kt�re miejsce wstawiam nast�pny element
        {
            int k1 = 0;

            //tworz� now� tabele kolejno��[]
            for (int n = 0; n < i + 1; ++n) //to taki "indykator" miejsca gdzie wstawiam element 
            {
                if (n == j) //je�li indykator r�wny numeru permutacji to wstawiamy tu nowy i-ty element
                {
                    kolejnosc[n] = modyfik;
                }
                else
                {
                    kolejnosc[n] = mod[k1]; //inaczej wstawiamy element z nehwspom - poprzedniej tablicy kolejno�ci dla i-1
                    k1++;
                }
            }

            //obliczam Cmaxa wyliczonej kolejno�ci////

            for (int ii = 0; ii < IlM; ++ii)
            {
                for (int jj = 0; jj < IlZad; ++jj)
                {
                    maszynyC[ii][jj] = maszyny[ii][jj]; //w funkcji wyliczania Cmax zmieniam tabel� maszyny
                                                        //wi�c tworz� kopi� i z niej pracuj�
                }
            }

            minkol = ObliczCmax(IlM, i + 1, maszynyC, kolejnosc, minkol);


            //cout << modyfik << endl;

            for (int gg = 0; gg < i + 1; ++gg) // po obliczaniu wszystkich Cmax�w dla i-tego elementu wybieram
            {                                  //kolejno�� z najmniejszym Cmax
                kolejnosc[gg] = minkol[gg];    //i z niej dalej b�d� pracowa�, b�dzie ona wspomagaj�c� tabel� nehwspom[]
            }
        }
    }


    for (int i = 0; i < IlZad; ++i)
    {
        cout << minkol[i] << " ";
    }
    cout << endl << minkol[IlZad] << endl;

    delete[] maszyny;
    maszyny = nullptr;

    delete[] maszynyC;
    maszynyC = nullptr;

    delete[] kolejnosc;
    kolejnosc = nullptr;

    delete[] sumaczasow;
    sumaczasow = nullptr;

    delete[] nehwspom;
    nehwspom = nullptr;

    delete[] minkol;
    minkol = nullptr;

    system("pause");
    return 0;
}