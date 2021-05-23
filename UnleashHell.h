#ifndef __uh_H
#define __uh_H

#include "RomaVictor.h"
/* Funciones sobre grafos de las partes 2 y 3 */

/* 
    Corre greedy en G comenzando con el color 0, con el orden 
    interno que debe estar guardado de alguna formadentro de G. 
    Devuelve el número de colores que se obtiene. Devuelve 2**32-1 
    si hubo algún error interno y no pudo continuar el coloreo.
*/
u32 Greedy(Grafo G);

/*
    Devuelve 1 si G es bipartito, 0 si no. Además, si devuelve 1, colorea
    G con un coloreo propio de dos colores. Si devuelve 0, deja a G 
    coloreado con algun coloreo propio. (no necesariamente el mismo que
    tenia al principio).
*/
char Bipartito(Grafo G);

/*
    “Aleatoriza” el orden de los vértices de G, usando como semilla de
    aleatoridad el numero R. Retorna 0 si todo anduvo bien y 1 si hubo
    algun problema.
*/
char AleatorizarVertices(Grafo G,u32 R);

/*
    Ordena los vertices por colores, poniendo los vertices 
    de color perm[0] primero, luego los de color perm[1], etc...
    Si perm NO es una permutación devuelve 0, de lo contrario, 
    ordena y devuelve 1.
*/
char OrdenPorBloqueDeColores(Grafo G,u32* perm);


#endif