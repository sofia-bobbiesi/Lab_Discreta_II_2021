#include "UnleashHell.h"
#include "auxiliares.h"
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
    u32 *colores = calloc(n_vertx, sizeof(u32));
    bool *colores_usados = calloc(Delta(G)+1, sizeof(bool)); // 0 es disponible, 1 es usado
    // Decolorar los vértices asignándole UINT32_MAX
    for (u32 i = 0; i < n_vertx; i++){ 
        colores[i] = UINT32_MAX;
    }

    for (u32 v = 0u; v < n_vertx; ++v){
        u32 grado = Grado(v, G);
        for (u32 w = 0u; w < grado; ++w){
            color = colores[OrdenVecino(w,v,G)];
            // Si el vértice ya está coloreado, marco el color como usado
            if (color < UINT32_MAX){
                colores_usados[color] = 1;
            }       
        }
        // Busco el color mínimo que no haya sido asignado aún
        for(k = 0u; colores_usados[k] != 0; ++k);
        FijarColor(k, v, G);
        colores[v] = k;
        max_color = max(k, max_color);
        // Reseteo los colores usados para el próximo vértice
        for (u32 w = 0; w < grado; w++) {
           color = colores[OrdenVecino(w,v,G)];
            if (color != UINT32_MAX) {
                colores_usados[color] = 0;
            }
        }
        
    }
    free(colores);
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

char ChequeoColoreoPropio(Grafo G){
    for(u32 i = 0; i < NumeroDeVertices(G); ++i) {
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

void OrdenNatural(Grafo G){
    for (u32 i = 0u; i < NumeroDeVertices(G); ++i){
	    FijarOrden(i, G, i);
    }
}

char esPermutacion(u32 *arr, u32 N) {
    u32 *hash = calloc(N, sizeof(u32));
    u32 es_perm = 1;
    // Cuenta la frecuencia de colores
    for (u32 i = 0; i < N; ++i) {
        if (arr[i] >= N){
            es_perm = 0;
            break;
        }
        hash[arr[i]]++;
        // Verifica que la frecuencia sea 1
        if (hash[arr[i]] != 1) {
            es_perm = 0;
            break;
        }
    }
    free(hash);
    return es_perm;
}

u32 MaxColor(Grafo G){
    u32 max_color = 0;
    for (u32 i = 0u; i < NumeroDeVertices(G); ++i) {
        if (Color(i,G) > max_color){
            max_color = Color(i,G);
        }
    }
    return max_color;
}

char OrdenPorBloqueDeColores(Grafo G, u32 *perm) {
    u32 n_vertx = NumeroDeVertices(G);
    // La permutación tiene exactamente r colores.
    u32 len_perm = MaxColor(G) + 1;
    // Chequeo que para r colores exista una permutación
    if (!esPermutacion(perm, len_perm)) {
        return 0;
    }
    // Conviene tener los vértices ordenados para luego orden por bloques
    OrdenNatural(G);
    // Cuenta la frecuencia de colores de los vertices
    u32 *freq = calloc(len_perm, sizeof(u32));
    for (u32 i = 0u; i < n_vertx; ++i) {
        freq[Color(i,G)]++;
    }
    /* 
        Creo un collection de tamaño r * freq[i],(i entre 0 y r) donde se 
        guardarán las posiciones que tienen el color correspondiente a perm[i]
    */
    u32 **hash = calloc(len_perm,sizeof(u32*)); 	
	for (u32 i = 0u; i < len_perm; ++i) {
		hash[i] = calloc(freq[i],sizeof(u32));
    }
    /*
        Reseto el arreglo para usarlo de consulta al llenar la collection
        en las posiciones correctas
    */
    memset(freq,0,len_perm*sizeof(u32));
    u32 color = 0;

    for (u32 i = 0u; i < n_vertx; ++i) {
        color = Color(i,G);
        hash[color][freq[color]] = i;
        freq[color]++;
    }
    // Agrupo los vertices en el orden de los colores dados por perm
    u32 k = 0;
    for (u32 i = 0u; i < len_perm; ++i) {
        for (u32 j = 0u; j < freq[perm[i]]; ++j){
            FijarOrden(k,G,hash[perm[i]][j]);
            k++;
        }
    }
    //Libero la memoria usada
	for (u32 i = 0u; i<len_perm; ++i) {
		free(hash[i]);
    }
    free(hash);
    free(freq);
    return 1;
}