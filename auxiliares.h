#ifndef auxiliares_h
#define auxiliares_h

#include "RomaVictor.h"

/* Funciones auxiliares */

// Intercambia los valores de dos punteros en u32.
inline void swap(u32 *a, u32 *b) {
    u32 temp = *a;
    *a = *b;
    *b = temp;
}

// Minímo para u32
inline u32 min(u32 num1, u32 num2) {
    return (num1 > num2) ? num2 : num1;
}

// Maximo para u32
inline u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;
}

// Devuelve un grafo con sus vértices ordenados de manera creciente.
void OrdenNatural(Grafo G);

// Devuelve 0 si el coloreo de un grafo G NO es propio, 1 si lo es.
char ChequeoColoreoPropio(Grafo G);

/*
    Dado un arreglo y su longitud, comprueba si el arreglo representa una
    permutación o no, 0 si no es una permutación, 1 si lo es.
*/
char esPermutacion(u32 *arr, u32 N);

/*
    Devuelve el maximo color con el que fue coloreado alguno
    de los vértices para un grafo dado G
*/
u32 MaxColor(Grafo G);

#endif