import numpy as np
import matplotlib.pyplot as plt
 
N = 1000
pi = 4.0 * np.arctan(1.0)
icomplejo = 0.0 + 1.0j
nciclos = int(input("Por favor, introduzca el número de ciclos que quiere emplear: "))
k0 = 2.0 * pi * nciclos / N
s = 1.0 / (4.0 * k0**2)
V = np.zeros(N+1, dtype=np.complex128)
l = 0

for i in range(1, N + 1):
    if i <= 2.0 * N / 5.0 or i >= 3.0 * N / 5.0:
        V[i] = 0.0
    else:
        V[i] = l * k0**2.0

#inicializamos la norma a 0 para luego poder calcularla
norma = 0.0