#include "RomaVictor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializar leyendo del archivo, lo que no se pueda va default :)
// pedir el path???
Grafo ConstruccionDelGrafo(){ // parametro *flie_path
    Grafo grafito = malloc(sizeof(struct GrafoSt));

    FILE *file = fopen(file_path, "r"); //MESI CHIKITO Y ENOJADO
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    grafito->n_vertices = Entrada();
    grafito->m_lados = Entrada();
    grafito->delta = Entrada();
    /* Llenar lados */
    //FIXME PLZ :C
    for (u32 i = 0; grafito->n_vertices > i; ++i){
        vertice v_actual = malloc(sizeof(struct _vertice_t));
        v_actual->nombre_real = Entrada();
        v_actual->etiqueta = Entrada();
        v_actual->grado = Entrada();
        v_actual->color = Entrada();
        v_actual->vecinos[v_actual->grado] = Entrada();
        grafito->vertice_array[i] = v_actual;
        };

    fclose(file);
    return grafito;
}

void DestruccionDelGrafo(Grafo G){
    return NULL;
}

Grafo CopiarGrafo(Grafo G){
    return NULL;
}

u32 NumeroDeVertices(Grafo G){
    return G -> n_vertices;
}

u32 NumeroDeLados(Grafo G){
    return G -> m_lados;
}

u32 Delta(Grafo G){
    return G -> delta;
}

u32 Nombre(u32 i, Grafo G){
    return (G->vertice_array[i])->nombre_real;
}

u32 Color(u32 i, Grafo G){
    return (G->vertice_array[i])->color;
}

u32 Grado(u32 i, Grafo G){
    return (G->vertice_array[i])->grado;
}

u32 ColorVecino(u32 j, u32 i, Grafo G){
    return ((G->vertice_array[i])->vecinos[j])->color;
}

u32 NombreVecino(u32 j, u32 i, Grafo G){
    vertice v_i = G -> vertice_array[i];
    vertice v_j = v_i -> vecinos[j];
    return v_j -> nombre_real;
}

u32 OrdenVecino(u32 j, u32 i, Grafo G){
    return NULL;
}

u32 PesoLadoConVecino(u32 j, u32 i, Grafo G){
    return ((G->vertice_array[i])->vecinos[j])->peso_u2v;
}

char FijarColor(u32 x, u32 i, Grafo G){    // NOTE: Seguro que es char pibe?
    // NOTE: la numeración de vértices es desde 1
    if(i < G-> n_vertices){
        (G->vertice_array[i-1])->color = x;
        return 0;
    } 
    return 1;
}

char FijarOrden(u32 i, Grafo G, u32 N){    // NOTE: Seguro que es char pibe?
    if(i < G->n_vertices && N < G->n_vertices){
        // NOTE: hay que reordernar?
        return 0;
    }
    return 1;
}
/* 
    Si i y N son menores que el numero de vertices, fija que el vertice i 
    en el orden guardado en G sera el N-esimo vertice del orden “natural” 
    (el que se obtiene al ordenar los vertices en orden creciente de sus 
    “nombres” reales) y retorna 0.  De lo contrario retorna 1.
*/

u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G){ // NOTE: debería ser void pibe?
    ((G->vertice_array[i])->vecino[j])->peso_u2v = p;
    return;
}