#include "RomaVictor.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u32 Greedy(Grafo G) {
    FijarColor(0,0,G);
    u32 max_color = 0;
    for (u32 i = 1; i < NumeroDeVertices(G); i++) {
        u32 color = 0;
        for (u32 j = 0; j < Grado(i,G); j++) {
            if (OrdenVecino(j, i, G) < i) {
                if (ColorVecino(j, i, G) == color) {
                    color++;
                    j = -1;
                }
            }
        }
        if (color > max_color) {
            max_color = color;
        }
        FijarColor(color, i, G);
    }
    return max_color + 1;
}

char Bipartito(Grafo G){
    return;
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
    for (int i = n_vertx-1; i > 0; --i){
        // Elige un índice aleatorio de 0 a i.
        int j = rand() % (i+1);
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