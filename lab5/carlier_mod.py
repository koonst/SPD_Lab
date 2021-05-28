import time
import operator
import queue
import time
import heapq


def zwr_a(U, pi, zadania, b):
    q = zadania[b][2]
    idx_b = pi.index(b)
    for wart in pi:
        p = 0
        r = zadania[wart][0]
        mi = pi.index(wart)
        for a in range(mi, idx_b+1):
            p += zadania[pi[a]][1]
        if U == r+p+q:
            return wart


def zwr_b(U, pi, zadania):
    p = 0
    for wart in pi:
        r = zadania[wart][0]
        p = max(p, r) + zadania[wart][1]
        if U == p + zadania[wart][2]:
            j = wart
    return j


def zwr_c(pi, zadania, a, b):
    flag = 0
    a = pi.index(a)
    b = pi.index(b)
    for wart in range(a, b+1):
        if zadania[pi[wart]][2] < zadania[pi[b]][2]:
            j = pi[wart]
            flag = 1
    if flag == 1:
        return j
    else:
        return []


##################   Algorytm Carlier
def Carlier(zadania):
    global UB                           # UB gorne ograniczenie
    global n                            # n liczba zadan
    pi, U = Schrage(zadania)            # U wartosc funkcji celu -  Cmax
    if U < UB:
        UB = U                          #aktualizacja
    b = zwr_b(U, pi, zadania)           #zadanie najdalsze
    a = zwr_a(U, pi, zadania, b)        #zadanie najbliższe
    c = zwr_c(pi, zadania, a, b)
    if c == []:
        return UB, zadania
    K = []

    for i in pi[pi.index(c)+1:pi.index(b)+1]:
        K.append(i)

    rK = []                             #czas przygotowania
    qK = []                             #czas dostarczania
    pK = 0                              #czas wykonywania na maszynie
    for wart in K:
        rK.append(zadania[wart][0])
        qK.append(zadania[wart][2])
        pK += zadania[wart][1]
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

##################   Algorytm Carlier mod
def Carlier_mod(zadania):
    global UB
    global n
    pi, U = Schrage(zadania)
    if U < UB:
        UB = U
    b = zwr_b(U, pi, zadania)
    a = zwr_a(U, pi, zadania, b)
    c = zwr_c(pi, zadania, a, b)
    if c == []:
        return UB, zadania
    K = []

    for i in pi[pi.index(c)+1:pi.index(b)+1]:
        K.append(i)

    rK = []
    qK = []
    pK = 0
    for i in K:
        rK.append(zadania[i][0])
        qK.append(zadania[i][2])
        pK += zadania[i][1]
    qK = min(qK)
    rK = min(rK)
    rpq = [rK, pK, qK]
    LB = Schrage_pmtn(zadania)

    L = []
    for i in pi[0:pi.index(c)]:
        L.append(i)
    for i in pi[pi.index(b)+1:]:
        L.append(i)
    for i in L:
        if UB - sum(rpq) >= zadania[i][1]:
            L.pop(L.index(i))

    for i in L:
        if UB <= zadania[i][0] + zadania[i][1] + rpq[1] + zadania[b][2]:
            zadania[i][0] = max(zadania[i][0], rpq[0]+rpq[1])
        if UB <= rpq[0] + zadania[i][1] + rpq[1] + zadania[i][2]:
            zadania[i][2] = max(zadania[i][2], rpq[2]+rpq[1])

    zach_R = zadania[c][0]
    zadania[c][0] = max(zadania[c][0], rK+pK)
    hkc = min(rK, zadania[c][0])+pK+zadania[c][1]+min(qK, zadania[c][2])
    LBL = max(sum(rpq), LB, hkc)
    if LBL < UB:
        Carlier_mod(zadania)
    zadania[c][0] = zach_R
    zach_Q = zadania[c][2]
    zadania[c][2] = max(zadania[c][2], qK + pK)
    hkc = min(rK, zadania[c][0]) + pK + zadania[c][1] + min(qK, zadania[c][2])
    LBP = max(sum(rpq), hkc, LB)
    if LBP < UB:
        Carlier_mod(zadania)
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

    print("####################################################################")
    print("Algorytm Carlier modyfikacja")
    data = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    correct = [228, 3026, 3665, 3309, 3191, 3618, 3446, 3821, 3634]

    for i in data:
        UB = 9999999
        plik = "../data/carlier_data" + str(i) + ".txt"
        ilosc_zadan, ilosc_kolumn, zadania = funkcja_czytania_danych(plik)
        start = time.perf_counter()
        UB = Carlier_mod(zadania)
        stop = time.perf_counter()
        czas = round((stop - start), 5)
        print("{} {}  Correct: {}  Time: {}".format(plik, UB, correct[i], czas))




