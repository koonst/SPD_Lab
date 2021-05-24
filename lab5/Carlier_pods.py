import time
import operator


def zwr_a(U, pi, zadania, b):
    q = zadania[b][2]
    idx_b = pi.index(b)
    for val in pi:
        p = 0
        r = zadania[val][0]
        mi = pi.index(val)
        for a in range(mi, idx_b+1):
            p += zadania[pi[a]][1]
        if U == r+p+q:
            return val


def zwr_b(U, pi, zadania):
    p = 0
    for val in pi:
        r = zadania[val][0]
        p = max(p, r) + zadania[val][1]
        if U == p + zadania[val][2]:
            j = val
    return j


def zwr_c(pi, zadania, a, b):
    flag = 0
    a = pi.index(a)
    b = pi.index(b)
    for val in range(a, b+1):
        if zadania[pi[val]][2] < zadania[pi[b]][2]:
            j = pi[val]
            flag = 1
    if flag == 1:
        return j
    else:
        return []


################################################# CLASSICAL APPROACH #################################################
def Carlier(zadania):
    global UB                           # UB gorne ograniczenie, wynik Schrage
    global n                            # n liczba zadan
    pi, U = Schrage(zadania)            # U wartosc funkcji celu -  Cmax
    if U < UB:
        UB = U
    b = zwr_b(U, pi, zadania)           #zadanie najdalsze
    a = zwr_a(U, pi, zadania, b)        #zadanie najbliższe
    c = zwr_c(pi, zadania, a, b)        #zadanie krytyczne
    if c == []:
        return UB, zadania
    K = []

    for i in pi[pi.index(c)+1:pi.index(b)+1]:
        K.append(i)

    rK = []                             #czas przygotowania
    qK = []                             #czas dostarczania
    pK = 0                              #czas wykonywania na maszynie
    for val in K:
        rK.append(zadania[val][0])
        qK.append(zadania[val][2])
        pK += zadania[val][1]
    qK = min(qK)
    rK = min(rK)
    rpq = [rK, pK, qK]
    LB = Schrage_pmtn(zadania)
    zach_R = zadania[c][0]
    zadania[c][0] = max(zadania[c][0], rK+pK)
    hkc = min(rK, zadania[c][0])+pK+zadania[c][1]+min(qK, zadania[c][2])
    LBL = max(sum(rpq), LB, hkc)
    if LBL < UB:
        Carlier(zadania)
    zadania[c][0] = zach_R
    zach_Q = zadania[c][2]
    zadania[c][2] = max(zadania[c][2], qK + pK)
    hkc = min(rK, zadania[c][0]) + pK + zadania[c][1] + min(qK, zadania[c][2])
    LBP = max(sum(rpq), hkc, LB)
    if LBP < UB:
        Carlier(zadania)
    zadania[c][2] = zach_Q
    return UB



##################   Algorytm Schrage
def Schrage(N):
    teta = []
    NG = []
    NN = []
    a = 0
    for i in N:
        NN.append([a, i[0], i[1], i[2]])
        a += 1
    t = min(NN, key=operator.itemgetter(1))[1]
    Cmax = 0
    while (NN != [] or NG != []):
        while (NN != [] and t >= min(NN, key=operator.itemgetter(1))[1]):
            j = NN.index(min(NN, key=operator.itemgetter(1)))
            NG.append(NN[j])
            NN.pop(j)

        if NG == []:
            t = min(NN, key=operator.itemgetter(1))[1]
        else:
            i = NG.index(max(NG, key=operator.itemgetter(3)))
            j = NG[i]
            NG.pop(i)
            teta.append(j[0])
            t = t + j[2]
            Cmax = max(Cmax, t+j[3])
    return teta, Cmax

##################   Algorytm Schrage dla problemu z podziałem zadań (Schrage pmtn)

def Schrage_pmtn(N):
    NG = []
    NN = []
    a = 0
    for i in N:
        NN.append([a, i[0], i[1], i[2]])
        a += 1
    t = min(NN, key=operator.itemgetter(1))[1]
    Cmax = 0
    l = [0, 0, 0, 100000000]
    while (NN != [] or NG != []):
        while (NN != [] and t >= min(NN, key=operator.itemgetter(1))[1]):
            j = NN.index(min(NN, key=operator.itemgetter(1)))
            i = NN[j]
            NG.append(NN[j])
            NN.pop(j)
            if i[3] > l[3]:
                l[2] = t - i[1]
                t = i[1]
                if l[2] > 0:
                    NG.append(l)
        if NG == []:
            t = min(NN, key=operator.itemgetter(1))[1]
        else:
            i = NG.index(max(NG, key=operator.itemgetter(3)))
            j = NG[i]
            NG.pop(i)
            l = j
            t = t + j[2]
            Cmax = max(Cmax, t+j[3])
    return Cmax



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

    file.close()
    return ilosc_zadan, ilosc_kolumn, zadania



if __name__=="__main__":

    print("Algorytm Carlier")
    data = [0, 1, 3, 4]
    poprawny = [228, 3026, 3309, 3191]
    tmp = 0
    for i in data:
        UB = 9999999
        plik = "../data/carlier_data" + str(i) + ".txt"
        ilosc_zadan, ilosc_kolumn, zadania = funkcja_czytania_danych(plik)
        start = time.perf_counter()
        UB = Carlier(zadania)
        stop = time.perf_counter()
        czas = round((stop - start), 5)
        print("{} {}  Poprawne: {}  Czas: {}".format(plik, UB, poprawny[tmp], czas))
        tmp += 1


