#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;



const int STOP = 50000;
const int TABU = 80;


bool NotTabu(int** tabu, int IloscZadan, int* kolejnosc)
{
    for (int i = 0; i < TABU; ++i)
    {
        int indykator = 0;
        for (int j = 0; j < IloscZadan; ++j)
        {
            if (tabu[i][j] == kolejnosc[j])
            {
                indykator = 1;
            }
            else
            {
                indykator = 0;
                j = IloscZadan;
            }
        }
        if (indykator == 1)
        {
            return 0;
            break;
        }
    }
    return 1;
}


int** RefreshTabu(int** tabu, int IloscZadan, int* kolejnosc)
{
    for (int i = TABU - 1; i > 0; --i)
    {
        for (int j = 0; j < IloscZadan; ++j)
        {
            tabu[i][j] = tabu[i][j - 1];
        }
    }

    for (int j = 0; j < IloscZadan; ++j)
    {
        tabu[0][j] = kolejnosc[j];
    }

    return tabu;
}


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

/////////////







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

    //tablica wspomagaj�ca dla permutacji kolejno�ci wype�niania zada� w algorytmie neh
    int* nehwspom = new int[IlZad];

    //tablica kolejnosci wypelniania zadan dla r�nych permutacji w algorytmie neh
    int* kolejnosc = new int[IlZad];


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

    int** sumaczasow = new int* [IlZad];
    int* minkol = new int[IlZad+1]; // tablica kolejno�ci wype�niania zada� z minimalnym Cmax
    minkol[IlZad] = 99999;

    for (int i = 0; i < IlZad; ++i)
    {
        sumaczasow[i] = new int[2];
        sumaczasow[i][0] = 0;
        sumaczasow[i][1] = i+1;    //od razu numeruje zadania
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
    int temp1,temp2;
    for (int i = 0; i < IlZad-1; ++i)
    {
        for (int j = i+1; j < IlZad; ++j)
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


                /*******************************/
                ///////////ALGORYTM NEH//////////
                /*******************************/


    unsigned int start_time = clock();
    //tablela kolejnosc z tymczasow� kolejno�ci� dla pierwszego elementu
    kolejnosc[0] = sumaczasow[0][1];
    //i wspomagaj�ca r�wnie�
    nehwspom[0] = sumaczasow[0][1];

    for (int i = 1; i < IlZad; ++i) //ile razy bierzemy warto�ci z posortowanej tabeli sum czas�w
    {
        minkol[i+1] = 99999;
        //kopiuj� warto�ci poprzedniej kolejnosci do wspomagaj�cej tabeli nehwspom
        for (int g = 0; g < i; ++g)
        {
            nehwspom[g] = kolejnosc[g];
            //algorytm stworzenia kolejnosci permutacji b�dzie taki, �e
            //bierz� tablic� nehwspom[] i wstawiam nast�pny element na 
            //miejsce 1, 2, i td po kolei
        }

        for (int j = 0; j < i+1; ++j) //ile permutacji, r�wnie� na kt�re miejsce wstawiam nast�pny element
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

                minkol = ObliczCmax(IlM, i+1, maszynyC, kolejnosc, minkol);

                ///////////////////////////////////////////
               

        }
        for (int gg = 0; gg < i + 1; ++gg) // po obliczaniu wszystkich Cmax�w dla i-tego elementu wybieram
        {                                  //kolejno�� z najmniejszym Cmax
            kolejnosc[gg] = minkol[gg];    //i z niej dalej b�d� pracowa�, b�dzie ona wspomagaj�c� tabel� nehwspom[]
        }                                  //dla nast�pnej i+1 -ej kolejno�ci
    }
    

    for (int i = 0; i < IlZad; ++i)
    {
        cout << minkol[i] << " ";
    }
    cout << endl << "algorytm neh: " << minkol[IlZad] << endl;
    cout << endl;
    cout << endl;

    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout << "czas wykonania neh: "<< search_time << " ms" <<endl;


                /*********************************************************/
                ///////////////////////TABU SEARCH/////////////////////////
                /*********************************************************/

    unsigned int start_time1 = clock();

    //zainicjowalem liste zabronien   lista_tabu
    int** lista_tabu = new int* [TABU];
    for (int i = 0; i < TABU; ++i)
    {
        lista_tabu[i] = new int[IlZad];
        for (int j = 0; j < IlZad; ++j)
        {
            lista_tabu[i][j] = 0;
        }
    }

    int* sasiad = new int[IlZad];

    int ind = 0;

    while (ind < STOP)
    {
        /// ////generacja sasiada dla kolejnosci minkol

        for (int i = 0; i < IlZad - 1; ++i)
        {
            for (int j = 0; j < IlZad; ++j)
            {
                sasiad[j] = kolejnosc[j];
            }
            swap(sasiad[i], sasiad[i + 1]);


            //obliczam Cmax dla kolejnosci sasiad
            if (NotTabu(lista_tabu, IlZad, sasiad)) //jesli nie znajduje sie na liscie tabu oczywiscie
            {

                for (int ii = 0; ii < IlM; ++ii)
                {
                    for (int jj = 0; jj < IlZad; ++jj)
                    {
                        maszynyC[ii][jj] = maszyny[ii][jj]; //w funkcji wyliczania Cmax zmieniam tabel� maszyny
                                                            //wi�c tworz� kopi� i z niej pracuj�
                    }
                }

                minkol = ObliczCmax(IlM, IlZad, maszynyC, sasiad, minkol);
                lista_tabu = RefreshTabu(lista_tabu, IlZad, sasiad);  ////no i dodaje do listy tabu bo nie bylo
            }
        }

        for (int g = 0; g < IlZad; ++g)
        {
            kolejnosc[g] = minkol[g];
        }

        ind++;
    }

    cout << "tabu search: " << minkol[IlZad] << endl;

    for (int i = 0; i < IlZad; ++i)
    {
        cout << minkol[i] << " ";
    }
    cout << endl;

    unsigned int end_time1 = clock();
    cout << "czas wykonywania tabu search: "<< end_time1 - start_time1 << " ms" << endl;


    /// /////////////////
    /// /////////////////
    /// /////////////////


    delete[] sasiad;
    sasiad = nullptr;

    delete[] lista_tabu;
    lista_tabu = nullptr;

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