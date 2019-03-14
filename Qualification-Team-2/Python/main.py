import random
import math


diferencia_par_permitida = 16
diferencia_impar_permitida = 17
divisor_limite_interseccion = 16


def leeFichero(fichero):
    input_file = open(fichero, "r")

    primera = input_file.readline()
    numFotos = int(primera)
    horizontales = []
    verticales = []
    idFoto = 0
    for line in input_file:
        linea = line.split()
        orientacion = linea[0]
        numTags = int(linea[1])
        tags = []
        for i in range(numTags):
            tags.append(linea[i+2])
        if (orientacion == "H"):
            horizontales.append((idFoto, tags))
        else:
            verticales.append((idFoto, tags))
        idFoto += 1
    return numFotos, horizontales, verticales


def escribeSolucion(fichero, slides):
    output_file = open(fichero, "w")
    output_file.write(str(len(slides)) + "\n")
    for slide in slides:
        if isinstance(slide[0], tuple):
            output_file.write(str(slide[0][0]) + " " + str(slide[1][0]) + "\n")
        else:
            output_file.write(str(slide[0]) + "\n")
    output_file.close()

def agrupaVerticalesRestantes(verticales):
    parejas = []
    diferencia_permitida_local = 16
    divisor_limite_interseccion_local = 16
    while(len(verticales) > 1):
        i = 0
        j = 0
        found = False
        longitud = len(verticales)
        while(i < longitud):
            foto1 = verticales[i]
            tags1 = foto1[1]
            numTags1 = len(tags1)
            j = i+1
            while(j < longitud and not found):
                foto2 = verticales[j]
                tags2 = foto2[1]
                numTags2 = len(tags2)
                if abs(numTags1 - numTags2) <= diferencia_permitida_local:
                    temp = set(tags2) 
                    interseccion = [value for value in tags1 if value in temp]
                    if numTags1 > numTags2:
                        limite_interseccion = numTags1/divisor_limite_interseccion_local
                    else:
                        limite_interseccion = numTags2/divisor_limite_interseccion_local
                    limite_interseccion = math.ceil(limite_interseccion)
                    if len(interseccion) <= limite_interseccion:
                        parejas.append((foto1, foto2))
                        verticales.remove(foto1)
                        verticales.remove(foto2)
                        longitud = len(verticales)
                        found = True
                j += 1
            i += 1
            found = False
        diferencia_permitida_local = diferencia_permitida_local * 2
        divisor_limite_interseccion_local = divisor_limite_interseccion_local / 2
    return parejas


def agrupaVerticales(verticales):
    longitud = len(verticales)
    i = 0
    j = 0
    parejas = []
    found = False
    while(i < longitud):
        foto1 = verticales[i]
        tags1 = foto1[1]
        numTags1 = len(tags1)
        j = i+1
        if numTags1 % 2 == 0:
            while (j < longitud and not found):
                foto2 = verticales[j]
                tags2 = foto2[1]
                numTags2 = len(tags2)
                if numTags2 % 2 == 0 and abs(numTags1 - numTags2) < diferencia_par_permitida:
                    temp = set(tags2) 
                    interseccion = [value for value in tags1 if value in temp]
                    if numTags1 > numTags2:
                        limite_interseccion = numTags1/divisor_limite_interseccion
                    else:
                        limite_interseccion = numTags2/divisor_limite_interseccion
                    limite_interseccion = math.ceil(limite_interseccion)
                    if len(interseccion) <= limite_interseccion:
                        parejas.append((foto1, foto2))
                        verticales.remove(foto1)
                        verticales.remove(foto2)
                        longitud = len(verticales)
                        found = True
                j += 1
        else:
            while (j < longitud and not found):
                foto2 = verticales[j]
                tags2 = foto2[1]
                numTags2 = len(tags2)
                if numTags2 % 2 != 0 and abs(numTags1 - numTags2) < diferencia_impar_permitida:
                    temp = set(tags2) 
                    interseccion = [value for value in tags1 if value in temp]
                    if numTags1 > numTags2:
                        limite_interseccion = numTags1/divisor_limite_interseccion
                    else:
                        limite_interseccion = numTags2/divisor_limite_interseccion
                    if len(interseccion) <= limite_interseccion:
                        parejas.append((verticales[i], verticales[j]))
                        verticales.remove(foto1)
                        verticales.remove(foto2)
                        longitud = len(verticales)
                        found = True
                j += 1
        i += 1
        found = False
    return parejas, verticales
        

def algoritmo_random(numFotos, horizontales, verticales):
    parejas, verticales_restantes = agrupaVerticales(verticales)
    slides_totales = horizontales + parejas
    parejas = agrupaVerticalesRestantes(verticales_restantes)
    slides_totales += parejas
    random.shuffle(slides_totales)
    return slides_totales

    
def main():
        files = ["a_example","b_lovely_landscapes","c_memorable_moments", "d_pet_pictures", "e_shiny_selfies"]
        for filename in files:
            numFotos, horizontales, verticales = leeFichero(filename+".txt")
            solucion = algoritmo_random(numFotos, horizontales, verticales)
            escribeSolucion(filename+".out", solucion)


if __name__ == '__main__':
    main()
