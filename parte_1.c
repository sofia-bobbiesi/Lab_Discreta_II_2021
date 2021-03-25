#include "RomaVictor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Grafo ConstruccionDelGrafo(){
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
    // NOTE: cargar los vertices a medida que entran, si aparece un vecino se carga como vertice
    for(int i = 0; i < grafito->m_lados; ++i){
        fgets(buffer,255,stdin);
        sscanf(buffer,"%c %u %u", &indict,curr_v,curr_s);
        if(curr_v!=last_v){
            vertice v = malloc(sizeof(struct _vertice_t));
            v->nombre_real = curr_v;
            grafito->vertices[index] = curr_v;
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
    return G->n_vertices;
}

u32 NumeroDeLados(Grafo G){
    return G->m_lados;
}

u32 Delta(Grafo G){
    return G->delta;
}

u32 Nombre(u32 i, Grafo G){
    return G->vertices[i]->nombre_real;
}

u32 Color(u32 i, Grafo G){
    return G->vertices[i]->color;
}
u32 Grado(u32 i, Grafo G){
    return G->vertices[i]->grado;
}

u32 ColorVecino(u32 j, u32 i, Grafo G){
    return G->vertices[i]->vecinos[j]->vertice_j->color;
}

u32 NombreVecino(u32 j, u32 i, Grafo G){
    return G->vertices[i]->vecinos[j]->vertice_j->nombre_real;
}

u32 OrdenVecino(u32 j, u32 i, Grafo G){
    u32 k = 0;
    for (k; k < G->n_vertices; ++k){
        if(G->vertices[i]->vecinos[j] == G->vertices[k]){
            break;
        }
    }
    return k;
}

u32 PesoLadoConVecino(u32 j, u32 i, Grafo G){
    return G->vertices[i]->vecinos[j]->peso_u2v;
}

char FijarColor(u32 x, u32 i, Grafo G){
    // NOTE: la numeración de vértices es [0,..,n-1] ?
    if(i < G-> n_vertices){
        (G->vertices[i])->color = x;
        return 0;
    } 
    return 1;
}

char FijarOrden(u32 i, Grafo G, u32 N){
    if(i < G->n_vertices && N < G->n_vertices){
        // NOTE: tomar el vertice i, ordenar, insertar el
        // vertice i en la posicion N, hacer swap? 
        return 0;
    }
    return 1;
}

u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G){ 
    G->vertices[i]->vecinos[j]->peso_u2v = p;
    // NOTE: debería retornar 2**32 - 1 como indice de que hubo un error ?
    return;
}