#include "RomaVictor.h"
#include <stdio.h>

Grafo ConstruccionDelGrafo(){
    
    return NULL;
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
    vertice v = G -> vertice_array[i];
    return v -> nombre_real;
}

u32 Color(u32 i, Grafo G){
    vertice v = G -> vertice_array[i];
    return v -> color;
}

u32 Grado(u32 i, Grafo G){
    vertice v = G -> vertice_array[i];
    return v -> grado;
}

u32 ColorVecino(u32 j, u32 i, Grafo G){
    vertice v_i = G -> vertice_array[i];
    vertice v_j = v_i -> vecinos[j];
    return v_j -> color;
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
    return NULL;
}

char FijarColor(u32 x, u32 i, Grafo G){
    return NULL;
}

char FijarOrden(u32 i, Grafo G, u32 N){
    return NULL;
}

u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G){
    return NULL;
}