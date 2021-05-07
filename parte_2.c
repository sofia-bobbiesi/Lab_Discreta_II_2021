#include "UnleashHell.h"
#include "cola.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

u32 Greedy(Grafo G){
    u32 color = 0, max_color = 0;
    u32 n_vertx = NumeroDeVertices(G);
    u32 k;
    bool *colores_usados = calloc(n_vertx, sizeof(u32)); // 0 es disponible, 1 es usado
    // Decolarar los vértices asignándole UINT32_MAX
    for (u32 i = 0; i < n_vertx; i++){ 
        FijarColor(UINT32_MAX, i, G);
    }

    for (u32 v = 0u; v < n_vertx; ++v){
        for (u32 w = 0u; w < Grado(v, G); ++w){
            color = ColorVecino(w, v, G);
            // Si el vértice ya está coloreado, marco el color como usado
            if (color < UINT32_MAX){
                colores_usados[color] = 1;
            }       
        }
        // Busco el color mínimo que no haya sido asignado aún
        for(k = 0u; colores_usados[k] != 0; ++k);
        FijarColor(k, v, G);
        max_color = max(k, max_color);
        // Reseteo los colores usados para el próximo vértice
        memset(colores_usados, 0, n_vertx);
    }
    free(colores_usados);
    // El maximo de colores + el color 0
    return max_color + 1;
}

static void BFS(Grafo G, u32 vertice){
    queue cola = newQueue(NumeroDeVertices(G));
    FijarColor(0, vertice, G);
    enqueue(cola, vertice);
    while (!isEmptyQueue(cola)){
        u32 v = front(cola);
        dequeue(cola);
        for (u32 j = 0; j < Grado(v, G); j++) {
            if (ColorVecino(j, v, G) == UINT32_MAX) { 
                FijarColor(1 - Color(v, G), OrdenVecino(j, v, G), G);
                enqueue(cola, OrdenVecino(j, v, G));
            }
        }
    }
    deleteQueue(cola);
}

static char ChequeoColoreoPropio(Grafo G){
    u32 n_vertx = NumeroDeVertices(G);
    for(u32 i = 0; i < n_vertx; ++i) {
        for (u32 j = 0; j < Grado(i, G); ++j){
            if(Color(i, G) == ColorVecino(j, i, G)){
                return 0;
            }
        }
    }
    return 1;
}

char Bipartito(Grafo G){
    u32 n_vertx = NumeroDeVertices(G);
    // Inicializa los colores en un color que no puede tomar
    for (u32 i = 0; i < n_vertx; i++) {
	    FijarColor(UINT32_MAX, i, G);
    }    
    for (u32 i = 0; i < n_vertx; i++) {
        if (Color(i, G) == UINT32_MAX) {
            BFS(G,i);
        }
    }
    // Si el coloreo que dio BFS no es propio, no es bipartito, 
    // le asignamos un coloreo que se propio y retornamos 0.
    if (!ChequeoColoreoPropio(G)) {
        for (u32 i = 0; i < n_vertx; i++) {
            FijarColor(i, i, G);
        }
	    return 0;
    }
    return 1;
}

char AleatorizarVertices(Grafo G,u32 R){
    u32 n_vertx = NumeroDeVertices(G);

    /*
        Arreglo que se usará para guardar los indices aleatorizados,
        mediante el algoritmo de Fisher-Yates, para fijar el orden
        en las respectivas posiciones. 
    */
    u32 *orden_aleatorio = calloc(n_vertx, sizeof(u32));
    if (orden_aleatorio == NULL){
        return 1;
    }

    // Inicializa los indices en [0 ... n_vertx-1]
    for (u32 i = 0u; i < n_vertx; ++i){
        orden_aleatorio[i] = i;
    }

    // Establece la semilla que rand() usará para generar números pseudo-aleatorios.
    srand(R); 
    /*
        Algoritmo de Fisher-Yates limitado al R dado. El mismo permite 
        recorrer toda una selección de forma aleatoria una sola vez.
    */
   int j;
    for (u32 i = n_vertx-1; i > 0; --i){
        // Elige un índice aleatorio de 0 a i.
        j = rand() % (i+1);
        // Intercambia arr[i] con el elemento en el índice aleatorio.
        swap(&orden_aleatorio[i], &orden_aleatorio[j]);
    }

    // Auxiliar para evaluar si falla FijarOrden y cortar el programa.
    char check = 0;
    // Finalmente, se aleatoriza el orden de los vertices del grafo G.
    for (u32 i = 0u; i < n_vertx; ++i){
        check = FijarOrden(i,G,orden_aleatorio[i]);
        if (check == 1) {
            break;
        }
    }
    free(orden_aleatorio);
    return check;
}

char permutacion(u32 *arr, u32 N) {
    u32 *hash = calloc(N, sizeof(u32));
    // Cuenta la frecuencia
    for (u32 i = 0; i < N; ++i) {
        hash[arr[i]]++;
    }
    // Verifica que la frecuencia sea 1
    for (u32 i = 0; i < N; i++) {
        if (hash[i] != 1)
            return 0; // No es una permutación
    }
    return 1; // Es una permutación
}

char OrdenPorBloqueDeColores(Grafo G,u32* perm){
    u32 len_perm = sizeof(perm)/sizeof(perm[0]);
    if (len_perm > NumeroDeVertices(G) || permutacion(perm, len_perm) == 0){
        return 0; // No es una perm válida
    }
    // Si es una perm -> ordena los vertices segun colores 

    return 1; //fue una permutacion válida
}


void OrdenNatural(Grafo G){
    for (u32 i = 0u; i < NumeroDeVertices(G); ++i){
	    FijarOrden(i, G, i);
    }
}