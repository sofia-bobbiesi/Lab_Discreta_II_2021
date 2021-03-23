#ifndef ROMA_VICTOR_H
#define ROMA_VICTOR_H

#include "GrafoSt21.h"
typedef struct GrafoSt *Grafo;

/* Funciones De Construccion/Destruccion/Copia del grafo */

Grafo ConstruccionDelGrafo();


void DestruccionDelGrafo(Grafo G);
/* Destruye G y libera la memoria alocada. */

Grafo CopiarGrafo(Grafo G);
/*
    La funcion aloca memoria suficiente para copiar todos los
    datos guardados enG, hace una copia deGen esa memoria y 
    devuelve un puntero a esa memoria.En caso de no poder 
    alocarse suficiente memoria, la funci ́on devolvera un
    puntero a NULL.
*/

/* Funciones para extraer informaci ́on de datos del grafo (Deben ser O(1))*/ 

u32 NumeroDeVertices(Grafo G);
/* Devuelve el numero de vertices de G. */

u32 NumeroDeLados(Grafo G);
/* Devuelve el numero de lados de G. */ 

u32 Delta(Grafo G);
/* Devuelve ∆(G), es decir, el mayor grado. */


/* Funciones para extraer informacion de los vertices (Deben ser O(1)) */

u32 Nombre(u32 i,Grafo G);
/* 
    Devuelve el nombre real del vertice numeroien el orden
    guardado en ese momento en G, (el  ́ındice 0 indica el
    primer vertice, el ındice 1 el segundo, etc)
*/
u32 Color(u32 i,Grafo G);
/* Devuelve el color con el que esta coloreado el vertice numero i 
en el orden guardado en ese momento en G. (el  ́ındice 0indica el primer v ́ertice, el  ́ındice 1 el segundo, etc).Siies mayor o igual que el n ́umero de v ́ertices, devuelve 232−1.(esto nunca puede ser un color en los grafos que testeeemos,pues para que eso fuese un color de alg ́un v ́ertice, el grafo deberia tener al menos 232vertices, lo cual lo har ́ıa inmanejable). */



#endif