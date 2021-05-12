#ifndef __uh_H
#define __uh_H

#include "RomaVictor.h"
/* Funciones sobre grafos de las partes 2 y 3 */

/* 
    Corre greedy en G comenzando con el color 0, con el orden 
    interno que debe estar guardado de alguna formadentro de G. 
    Devuelve el número de colores que se obtiene.
*/
u32 Greedy(Grafo G);

/*
    Devuelve 1 si G es bipartito, 0 si no. Ademas, si devuelve 1, colorea
    G con un coloreo propio de dos colores.  Si devuelve 0, debe dejar a G 
    coloreado con algun coloreo propio. (no necesariamente el mismo que
    tenia al principio).
*/
char Bipartito(Grafo G);

/*
    “Aleatoriza” el orden de los v ́ertices de G, usando como semilla de
    aleatoridad el numero R. Retorna 0 si todo anduvo bien y 1 si hubo
    algun problema.
*/
char AleatorizarVertices(Grafo G,u32 R);


/*
    Ordena los vertices por colores, poniendo los vertices 
    de color perm[0] primero, luego los de color perm[1], etc...
*/
char OrdenPorBloqueDeColores(Grafo G,u32* perm);

/* Funciones auxiliares */

// Intercambia los valores de dos punteros en u32.
inline void swap (u32 *a, u32 *b){
    u32 temp = *a;
    *a = *b;
    *b = temp;
}

// Devuelve un grafo con sus vértices ordenados de manera creciente.
void OrdenNatural(Grafo G);

// Maximo para u32
// inline u32 max(u32 a, u32 b) {
//     return (a > b) ? a : b;
// }

/*
    Comprueba si un arreglo representa una permutación o no, 0 si no es
    una permutación, 1 si lo es.
*/
char permutacion(u32 *arr, u32 N);

/*
    Devuelve el maximo color con el que fue coloreado alguno 
    de los vértices para un grafo dado G
*/
u32 MaxColor(Grafo G);

#endif