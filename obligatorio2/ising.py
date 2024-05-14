import numpy as np
import matplotlib.pyplot as plt
import random

def numaleatorio(minimo,maximo):
    return random.uniform(minimo,maximo)
def numdimaleatoria(minimo,maximo):
    return random.randint(minimo,maximo)



dim = int(input('Introduzca la dimensión de la cuadrícula: '))
temp = float(input('Introduzca la temperatura (Kelvin): '))
pasos = int(input('Introduzca el número de pasos Montecarlo: '))
pasos = pasos*dim*dim

# Paso 0: rellenamos la matriz inicialmente con 1, que luego cambiaremos
# aleatoriamente por -1
matriz = np.ones((dim, dim), dtype=int)
print(matriz)



#Abro un fichero para escribir las matrices y empiezo los pasos montecarlo
with open("datosising.txt", "w") as file:
    for k in range(pasos+1):
        i = random.randint(0, dim-1)
        j = random.randint(0, dim-1)

        for i in range(0, dim-1):
            matriz[i][0] = matriz[i][dim-1]
            #matriz[i][dim] = matriz[i][0]


        for j in range(0, dim-1):
            matriz[0][j] = matriz[dim-1][j]
            #matriz[dim][j-1] = matriz[0][j-1]


        energia = 2 * matriz[i, j] * (matriz[(i+1)%dim, j] + matriz[(i-1)%dim, j] +matriz[i, (j+1)%dim] + matriz[i, (j-1)%dim])
        p = np.exp(-energia/temp)
        if p > 1:
            p = 1
        aux = numaleatorio(0,1)
        if aux < p:
            matriz[i,j] = -matriz[i,j]

        #cambiar las filas y columnas extremas si es necesario
        if i == 0:
            matriz[dim-1, :] *= -1
        elif i == dim-1:
            matriz[0, :] *= -1
        if j == 0:
            matriz[:, dim-1] *= -1
        elif j == dim-1:
            matriz[:, 0] *= -1

        #escribo la matriz en el fichero solo en cada paso montecarlo
        if k % (dim * dim) == 1:
            for i in range(dim):
                file.write(' '.join(map(str, matriz[i])) + '\n')
            

    
        

file.close()
        



 

