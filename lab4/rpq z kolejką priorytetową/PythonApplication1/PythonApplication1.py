import copy
import operator
import queue
import time

def funkcja_czytania_danych(filename):
    file = open(filename, "r")
    ilosc_zadan, ilosc_kolumn = file.readline().split()
    ilosc_zadan = int(ilosc_zadan)
    ilosc_kolumn = int(ilosc_kolumn)
    zadania = []
    wartosci = []
    for w in file.read().split():
        wartosci.append(float(w))

    for a in range(0, len(wartosci), 3):
        tab = []
        for b in range(0,3):
            tab = tab + [wartosci[a+b]]
        zadania.append(tab)
    print("Ilość zadań: ", ilosc_zadan)
    print("Ilość kolumn: ", ilosc_kolumn)
    print("Zadania: \n", zadania)
    print("")
    file.close()
    return ilosc_zadan, ilosc_kolumn, zadania


##################   Algorytm Schrage
def Schrage(zadania):
    sigma = []                                          #częściowa kolejność składająca się z uszeregowanych zadań
    Ng = queue.PriorityQueue()                          #zbiór zadanć gotowych do uszeregowania
    Nn = copy.deepcopy(zadania)                         #zbiór zadań nieuszeregowanych
    t = min(Nn)[0]
    Cmax = 0

    start_time = time.time()

    while (Ng.empty() == False or Nn!=[]):
        while(Nn !=[] and min(Nn)[0] <=t):
            i = Nn.index(min(Nn))
            Ng.put((-Nn[i][2], Nn[i]))
            Nn.pop(i)
        if Ng.empty() == True:
            t = min(Nn)[0]
        else:
            k = Ng.get()
            tmp = k[1]
            sigma.append(tmp)
            t = t + tmp[1]
            Cmax = max(Cmax, t+tmp[2])

    print("--- %s seconds ---" % (time.time() - start_time))

    return  sigma, Cmax


##################   Algorytm Schrage dla problemu z podziałem zadań (Schrage pmtn)
def Schrage_pmtn(zadania):
    sigma = []                                      #częściowa kolejność składająca się z uszeregowanych zadań
    Ng = queue.PriorityQueue()                      #zbiór zadanć gotowych do uszeregowania
    Nn = copy.deepcopy(zadania)                     #zbiór zadań nieuszeregowanych
    t = 0
    Cmax = 0
    l = [0, 0, 0]

    start_time = time.time()

    while (Ng.empty() == False or Nn != []):
        while (Nn != [] and min(Nn)[0] <= t):
            i = Nn.index(min(Nn))
            tmp = Nn[i]
            Ng.put((-Nn[i][2], Nn[i]))
            Nn.pop(i)
            if tmp[2] > l[2]:
                l[1] = t-tmp[0]
                t = tmp[0]
                if l[1] > 0:
                    Ng.put((-l[2], l))
        if Ng.empty() == True:
             t = min(Nn)[0]
        else:
            k = Ng.get()
            i = k[1]           
            sigma.append(i)
            l = i
            t = t + i[1]
            Cmax = max(Cmax, t + i[2])

    print("--- %s seconds ---" % (time.time() - start_time))

    return sigma, Cmax


################## Funkcja main odpowiadająca za poprawne działanie funkcji

if __name__=="__main__":
    nr = 0

    while (nr != 5):

        print("----------------------------")
        print("")
        print("Algorytm Schrage'a")
        print(" 1. in50 \r\n 2. in100 \r\n 3. in200 \r\n 4. suma \r\n 5. koniec ")
        nr = int(input("Podaj swój wybór: "))

        if nr == 1:
            ilosc_zadan, ilosc_kolumn, zadania = funkcja_czytania_danych("schrage_in50.txt")
            print(zadania)
            sigma50, Cmax50 = Schrage(zadania)
            print("Algorytm Schrage'a")
            print("Wynik: ", Cmax50)

            print("----------------------------")
            sigma50_pmtn, Cmax50_pmtn = Schrage_pmtn(zadania)
            print("Algorytm Schrage'a - pmtn")
            print("Wynik: ", Cmax50_pmtn)

        elif nr == 2:
            ilosc_zadan, ilosc_kolumn, zadania = funkcja_czytania_danych("schrage_in100.txt")
            sigma100, Cmax100 = Schrage(zadania)
            print("Algorytm Schrage'a")
            print("Wynik: ", Cmax100)

            print("----------------------------")
            sigma100_pmtn, Cmax100_pmtn = Schrage_pmtn(zadania)
            print("Algorytm Schrage'a - pmtn")
            print("Wynik: ", Cmax100_pmtn)

        elif nr == 3:
            ilosc_zadan, ilosc_kolumn, zadania = funkcja_czytania_danych("schrage_in200.txt")
            sigma200, Cmax200 = Schrage(zadania)
            print("Algorytm Schrage'a")
            print("Wynik: ", Cmax200)

            print("----------------------------")
            sigma200_pmtn, Cmax200_pmtn = Schrage_pmtn(zadania)
            print("Algorytm Schrage'a - pmtn")
            print("Wynik: ", Cmax200_pmtn)

        elif nr == 4:
            wyniki = []
            wyniki_pmtn = []
            tests = ["schrage_in50.txt", "schrage_in100.txt", "schrage_in200.txt"]
            for test_file in tests:
                ilosc_zadan, ilosc_kolumn, zadania = funkcja_czytania_danych(test_file)
                sigma, Cmax = Schrage(zadania)
                sigma_pmtn, Cmax_pmtn = Schrage_pmtn(zadania)
                wyniki.append(Cmax)
                wyniki_pmtn.append(Cmax_pmtn)
            suma_Schrage = sum(wyniki)
            suma_Schrage_pmtn = sum(wyniki_pmtn)
            print("Algorytm Schrage'a")
            print("Twoje WYniki to:", wyniki)
            print("Po zsumowaniu:", suma_Schrage)
            print("----------------------------")
            print("Algorytm Schrage'a - pmtn")
            print("Twoje WYniki to:", wyniki_pmtn)
            print("Po zsumowaniu:", suma_Schrage_pmtn)