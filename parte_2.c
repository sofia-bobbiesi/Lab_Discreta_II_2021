#include "RomaVictor.h"
#include "funSobreGrafos.h"
#include "cola.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// FIXME: al reiniciar el loop se revisan innecesariamente los vecinos varias veces 
u32 Greedy(Grafo G) {
    u32 n_vertx = NumeroDeVertices(G);
    u32 max_color = 0;
    // El primer color siempre es 0, asignamos los siguientes
    FijarColor(0,0,G);
    for (u32 i = 1; i < n_vertx ; ++i) {
        u32 color = 0;
        // Para cada vecino del vertice i
        for (u32 j = 0; j < Grado(i,G); ++j) {
            // Si el vecino estaba antes en el orden o si tiene el mismo color que 
            // asignamos antes, cambio de color y reinicio el loop
            if ((OrdenVecino(j, i, G) < i) && (ColorVecino(j, i, G) == color)){
                    color++;
                    j = -1; //si, esto hace que ++j=0 y reinicia el ciclo, pero recorre
                            // muchas veces al pedo >:(
            }
        }
        if (color > max_color) {
            max_color = color;
        }
        FijarColor(color, i, G);
    }
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

static int ChequeoColoreoPropio(Grafo G){
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