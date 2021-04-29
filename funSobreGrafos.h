#ifndef FUN_SOBRE_GRAFOS_H
#define FUN_SOBRE_GRAFOS_H

#include "RomaVictor.h"
/* Funciones sobre grafos */

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

/* Funciones auxiliares */

/* Intercambia los valores de dos punteros en u32 */
inline void swap (u32 *a, u32 *b){
    u32 temp = *a;
    *a = *b;
    *b = temp;
}

#endif