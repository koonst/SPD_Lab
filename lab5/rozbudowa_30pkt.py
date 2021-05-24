def Carlier_Elim(tasks):
    global UB
    global n
    pi, U = Schrage(tasks)
    if U < UB:
        UB = U
    b = get_b(U, pi, tasks)
    a = get_a(U, pi, tasks, b)
    c = get_c(pi, tasks, a, b)
    if c == []:
        return UB, tasks
    K = []

    for i in pi[pi.index(c)+1:pi.index(b)+1]:
        K.append(i)

    rK = []
    qK = []
    pK = 0
    for i in K:
        rK.append(tasks[i][0])
        qK.append(tasks[i][2])
        pK += tasks[i][1]
    qK = min(qK)
    rK = min(rK)
    rpq = [rK, pK, qK]
    LB = Schrage_pmtn(tasks)

    L = []
    for i in pi[0:pi.index(c)]:
        L.append(i)
    for i in pi[pi.index(b)+1:]:
        L.append(i)
    for i in L:
        if UB - sum(rpq) >= tasks[i][1]:
            L.pop(L.index(i))

    for i in L:
        if UB <= tasks[i][0] + tasks[i][1] + rpq[1] + tasks[b][2]:
            tasks[i][0] = max(tasks[i][0], rpq[0]+rpq[1])
        if UB <= rpq[0] + tasks[i][1] + rpq[1] + tasks[i][2]:
            tasks[i][2] = max(tasks[i][2], rpq[2]+rpq[1])

    remember_R = tasks[c][0]
    tasks[c][0] = max(tasks[c][0], rK+pK)
    hkc = min(rK, tasks[c][0])+pK+tasks[c][1]+min(qK, tasks[c][2])
    LBL = max(sum(rpq), LB, hkc)
    if LBL < UB:
        Carlier_Elim(tasks)
    tasks[c][0] = remember_R
    remember_Q = tasks[c][2]
    tasks[c][2] = max(tasks[c][2], qK + pK)
    hkc = min(rK, tasks[c][0]) + pK + tasks[c][1] + min(qK, tasks[c][2])
    LBP = max(sum(rpq), hkc, LB)
    if LBP < UB:
        Carlier_Elim(tasks)
    tasks[c][2] = remember_Q
    return UB





##################################


"""

    print("-"*23)
    print("\nWith elimination")
    data = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    correct = [228, 3026, 3665, 3309, 3191, 3618, 3446, 3821, 3634]

    for i in data:
        UB = 9999999
        plik = "../data/carlier_data" + str(i) + ".txt"
        ilosc_zadan, ilosc_kolumn, zadania = funkcja_czytania_danych(plik)
        start = time.perf_counter()
        UB = Carlier_Elim(zadania)
        stop = time.perf_counter()
        czas = round((stop - start), 5)
        print("{} {}  Correct: {}  Time: {}".format(plik, UB, correct[i], czas))

"""