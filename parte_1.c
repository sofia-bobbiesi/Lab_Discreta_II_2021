#include "RomaVictor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializar leyendo del archivo, lo que no se pueda va default :)
// pedir el path???
Grafo ConstruccionDelGrafo(){ // parametro *flie_path
    Grafo grafito = malloc(sizeof(struct GrafoSt));
    char* buffer,indict,*edge,*discard;
    int number,curr_v,curr_s,last_v=0,index=0;
    buffer = malloc(sizeof(char*)*255);
    edge = malloc(sizeof(char*)*255);
    discard = malloc(sizeof(char*)*255);

    while((NULL!=fgets(buffer,255,stdin))&&(buffer[0]=='c'));
    number = sscanf(buffer, "%c %s %u %d %s", &indict, edge, &grafito->n_vertices, &grafito->m_lados, discard);
    if(((number!=4) || (indict!='p')) || (strcmp(edge,"edge"))){
        return NULL;
    }

    for(int i=0;i<grafito->m_lados;i++){
        fgets(buffer,255,stdin);
        sscanf(buffer,"%c %u %u", &indict,curr_v,curr_s);
        if(curr_v!=last_v){
            vertice v = malloc(sizeof(struct _vertice_t));
            v->etiqueta = curr_v;
            grafito->vertice_array[index] = curr_v;
            last_v=curr_v;
        }
    }
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