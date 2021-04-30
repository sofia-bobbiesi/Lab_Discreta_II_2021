#include "RomaVictor.h"
#include "funSobreGrafos.h"
#include "cola.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// FIXME: al reiniciar el loop se revisan innecesariamente los vecinos varias veces 
u32 Greedy(Grafo G)
{
    u32 color = 1, color_vertice, n = NumeroDeVertices(G), grado, i, j, *colores_usados=(u32*)calloc(Delta(G), sizeof(u32));
    for (i = 0; i < n; i++) {
        color_vertice = 0;
        grado = Grado(i, G);
        if (grado) {
            memset(colores_usados,0,grado);
            for (j = 0; j < grado; j++) {
            if (ColorVecino(j, i, G) < grado && OrdenVecino(j, i, G) < i)
                colores_usados[ColorVecino(j, i, G)] = 1;
            }
            while (colores_usados[color_vertice] && color_vertice < Grado(i, G)) {
            color_vertice++;
            }
            if (color < color_vertice + 1)
            color++;
        }
        FijarColor(color_vertice, i, G);
    }
    free(colores_usados); 
    return color;
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