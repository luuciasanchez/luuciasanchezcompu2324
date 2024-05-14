from matplotlib import pyplot as plt
import numpy as np

def leer_archivo(nombre_archivo):
    e = []
    t = []

# Abre el archivo en modo lectura
    with open('energiayl.txt', 'r') as file:
    # Lee cada línea del archivo
        for line in file:
        # Separa los datos de la línea en dos columnas
            datos = line.split()  # Suponiendo que los datos están separados por espacio en blanco
        
        # Añade los datos a las listas correspondientes
            energia.append(float(datos[0]))  # Suponiendo que la primera columna contiene números
            tiempo.append(float(datos[1])) 

    vector_energia = np.array(energia)
    vector_tiempo = np.array(tiempo)

    return vector_energia, vector_tiempo

nombre_archivo = 'energiayl.txt'
energia, tiempo = leer_archivo(nombre_archivo)

print("energia:", energia)
print("tiempo:", tiempo)


