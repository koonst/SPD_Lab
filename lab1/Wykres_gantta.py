

import matplotlib.pyplot as plt
import numpy as np

# Dane
total_time = 50
number_machines = 2
range_y = 10
machinery = ["M2", "M1"]

a1 = [0,4,8,18,24]
b1 = [4,4,10,6,2]
a2 = [4,9,18,24,34]
b2 = [5,1,4,10,3]
d = ["Z1","Z2","Z3","Z4","Z5"]
e = ["g","r","b","c","m"]

    


fig, gantt = plt.subplots()

# Podpisy osi:
gantt.set_xlabel("Time")
gantt.set_ylabel("Machinery")

# Zakres w pionie i poziomie:
gantt.set_xlim(0, total_time)
gantt.set_ylim(0, number_machines*range_y)

# Podziały czasowe:
gantt.set_xticks(range(0, total_time, 1), minor=True)
gantt.grid(True, axis='x', which='both')

gantt.set_yticks(range(range_y, number_machines*range_y, range_y), minor=True)
gantt.grid(True, axis='y', which='minor')

# Skalowanie etykiet:
gantt.set_yticks(np.arange(range_y/2, range_y*number_machines - range_y/2 + range_y,
                           range_y))
gantt.set_yticklabels(machinery)

# Funkcja budowania słupków:
def build_chart(t0, d, mach, name, color):
    # Indeksowanie maszyn
    imach = machinery.index(mach)
    # Pozycja słupków
    gantt.broken_barh([(t0, d)], (range_y*imach, range_y),
                      facecolors=(color))
    # Pozycja tekstu:
    gantt.text(x=(t0), y=(range_y*imach + range_y/2),
                  s=f"{name}({d})", va='center', color='k')

# Wywołanie funkcji:

for i in range(len(a1)):
    build_chart( a1[i], b1[i], "M1", d[i], e[i])
    build_chart( a2[i], b2[i], "M2", d[i], e[i])




plt.savefig("gantt1111222.png") 