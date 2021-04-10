#ifndef ROMA_VICTOR_H
#define ROMA_VICTOR_H

#include "GrafoSt21.h"
typedef struct GrafoSt *Grafo;

/* Funciones extra para el manejo de grafos */

/*
    Imprime la información general del grafo, sus vértices con los
    correspondientes vecinos y los vertices ordenados, también con sus
    vecinos. Usar con cuidado ya que en grafos grandes podría realentizar
    la ejecución.
*/
void imprimir_grafo(Grafo graph);

/* Funciones De Construccion/Destruccion/Copia del grafo */

/*
    La funcion aloca memoria, inicializa lo que haya que inicializar de
    una estructura GrafoSt, lee un grafo desde standard input en el formato
    indicado en la seccion 3, lo carga en la estructura, incluyendo algun
    orden de los vertices, y devuelve un puntero a la estructura. Como la
    carga en si del grafo no incluye los pesos en los lados, inicialmente
    le dara peso nulo a cada lado. En caso de error, la funcion devolvera
    un puntero a NULL. Si no hay AL MENOS m lineas luego de esa, debe
    retornar NULL.
*/
Grafo ConstruccionDelGrafo();

/* Destruye G y libera la memoria alocada. */
void DestruccionDelGrafo(Grafo G);

/*
    La funcion aloca memoria suficiente para copiar todos los
    datos guardados en G, hace una copia de Gen esa memoria y
    devuelve un puntero a esa memoria. En caso de no poder
    alocarse suficiente memoria, la funcion devolvera un
    puntero a NULL.

*/
Grafo CopiarGrafo(Grafo G);

/* Funciones para extraer informacion de datos del grafo (Deben ser O(1))*/

/* Devuelve el numero de vertices de G. */
u32 NumeroDeVertices(Grafo G);

/* Devuelve el numero de lados de G. */
u32 NumeroDeLados(Grafo G);

/* Devuelve ∆(G), es decir, el mayor grado. */
u32 Delta(Grafo G);

/* Funciones para extraer informacion de los vertices (Deben ser O(1)) */

/*
    Devuelve el nombre real del vertice numeroien el orden
    guardado en ese momento en G, (el ındice 0 indica el
    primer vertice, el ındice 1 el segundo, etc)
*/
u32 Nombre(u32 i, Grafo G);


/*
    Devuelve el color con el que esta coloreado el vertice numero i
    en el orden guardado en ese momento en G. (el ındice 0 indica el
    primer vertice, el ındice 1 el segundo, etc). Si i es mayor o
    igual que el numero de v ́ertices, devuelve 2**32-1.
*/
u32 Color(u32 i, Grafo G);

/*
    Devuelve el grado del vertice numero i en el orden guardado
    en ese momento en G. (el ındice 0 indica el primer vertice,
    el ındice 1 el segundo, etc). Si i es  mayor o igual  que
    el numero de vertices, devuelve  2**32−1.
*/
u32 Grado(u32 i, Grafo G);


/* Funciones para extraer informacion de los vecinos de un vertice */

/*
    Devuelve el color del vecino numerojdel vertice numero i en
    el orden guardado en ese momento en G. (el ındice 0 indica el
    primer vertice, el ındice 1 el segundo, etc).
*/
u32 ColorVecino(u32 j, u32 i, Grafo G);

/*
    Devuelve el nombre del vecino numero j del vertice numero i en
    el orden guardado en ese momento en G. (el ındice 0 indica el
    primer vertice, el ındice 1 el segundo, etc).
*/
u32 NombreVecino(u32 j, u32 i, Grafo G);

/*
    OrdenVecino(j,i,Grafo G) es igual a k si y solo si
    el vecino j-esimo del i-esimo vertice de G en el orden
    interno es el k-esimo vertice del orden interno de G.
*/
u32 OrdenVecino(u32 j, u32 i, Grafo G);

/*
    Devuelve el peso del lado formado por el i-esimo vertice de G
    en el orden interno con el j-esimo vecino de ese vertice.
*/
u32 PesoLadoConVecino(u32 j, u32 i, Grafo G);

/* Funciones para modificar datos de los vertices */

/*
    Si i es menor que el numero de vertices, le asigna el color x al
    vertice numero i en el orden guardado en ese momento en G y retorna 0.
    De lo contrario, retorna 1.
*/
char FijarColor(u32 x, u32 i, Grafo G);

/*
    Si i y N son menores que el numero de vertices, fija que el vertice i
    en el orden guardado en G sera el N-esimo vertice del orden “natural”
    (el que se obtiene al ordenar los vertices en orden creciente de sus
    “nombres” reales) y retorna 0.  De lo contrario retorna 1.
*/
char FijarOrden(u32 i, Grafo G, u32 N);

/*
    Hace que el lado formado por el i-esimo vertice de G en el orden
    interno con el j-esimo vecino de ese vertice tenga peso p.
*/
u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G);

#endif