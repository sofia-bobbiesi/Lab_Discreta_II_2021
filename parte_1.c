#include "avl-tree.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimir_grafo(Grafo graph) {
    if (graph != NULL) {
        printf("Vertices: %u, Lados: %u\n", graph->n_vertices, graph->m_lados);
        printf("Delta: %u\n", graph->delta);
        for (u32 i = 0; i < graph->n_vertices; i++) {
            vertice curr_vtx = graph->vertices[i];
            printf("Id: %u, Grado: %u, Color: %u, Posicion %u\n", curr_vtx->nombre_real,
                   curr_vtx->grado, curr_vtx->color, curr_vtx->posicion);

            if (curr_vtx->vecinos != NULL) {
                printf("Vecinos: {");
                for (u32 j = 0; j < curr_vtx->grado; j++) {
                    vecinos curr_vecino = curr_vtx->vecinos[j];
                    if (curr_vecino != NULL) {
                        printf("%u", curr_vecino->vertice_j->nombre_real);
                    }
                    if (j != (curr_vtx->grado) - 1) {
                        printf(", ");
                    }
                }
                printf("}\n\n");
            }
        }
        printf("Ordenado:\n");
        for (u32 i = 0; i < graph->n_vertices; i++) {
            vertice curr_vtx = graph->vertices_ordenados[i];
            printf("Id: %u, Grado: %u, Color: %u, Posicion %u \n", curr_vtx->nombre_real,
                   curr_vtx->grado, curr_vtx->color, curr_vtx->posicion);

            if (curr_vtx->vecinos != NULL) {
                printf("Vecinos: {");
                for (u32 j = 0; j < curr_vtx->grado; j++) {
                    vecinos curr_vecino = curr_vtx->vecinos[j];
                    if (curr_vecino != NULL) {
                        printf("%u", curr_vecino->vertice_j->nombre_real);
                    }
                    if (j != (curr_vtx->grado) - 1) {
                        printf(", ");
                    }
                }
                printf("}\n\n");
            }
        }
    }
}

vecinos crear_vecino(vertice lado) {
    vecinos nuevo_vecino = calloc(1, sizeof(struct lado_t));
    if (nuevo_vecino == NULL) {
        return NULL;
    }
    nuevo_vecino->vertice_j = lado;
    nuevo_vecino->peso_u2v = 0;
    return nuevo_vecino;
}

void agregar_vecino(Grafo G, vertice vertx, vertice lado) {
    if (vertx->grado == (vertx->size)) {
        u32 new_size = min(((vertx->size) * 2), G->m_lados);
        vertx->vecinos = (vecinos *)realloc(vertx->vecinos,
                                            (new_size * sizeof(struct lado_t)));
        vertx->size = new_size;
    }
    if (vertx->vecinos == NULL) {
        DestruccionDelGrafo(G);
        return;
    }
    vertx->vecinos[vertx->grado] = crear_vecino(lado);
    if (vertx->vecinos[vertx->grado] == NULL) {
        DestruccionDelGrafo(G);
        return;
    }
    vertx->grado++;
}

Grafo ConstruccionDelGrafo() {
    Grafo grafo = NULL;
    char buffer[255], discard[255], edge[255], indicador;
    u32 check = 0, n = 0, m = 0, vertx = 0, lado = 0, position = 0, pos_v = 0,
        pos_l = 0;
    vertice v1 = NULL, v2 = NULL;
    Node avl = NULL; // creo el arbol

    // Avanza leyendo sobre las lineas que debe omitir ('c')
    while (fgets(buffer, 255, stdin) != NULL && buffer[0] == 'c');
    // leo la primera linea con los datos del grafo
    check = sscanf(buffer, "%c %s %u %u %s", &indicador, edge, &n, &m, discard);
    if (check != 4 || (indicador != 'p') || strcmp(edge, "edge")) {
        fprintf(stderr, "\tERROR: Formato invalido.\n");
        return NULL;
    }
    // Si no falla, creo el grafo
    grafo = malloc(sizeof(struct GrafoSt));
    if (grafo == NULL) {
        DestruccionDelGrafo(grafo);
        return NULL;
    }
    grafo->n_vertices = n;
    grafo->m_lados = m;
    grafo->delta = 0;
    grafo->vertices = calloc(n, sizeof(struct _vertice_t));
    grafo->vertices_ordenados = calloc(n, sizeof(struct _vertice_t));
    if (grafo->vertices == NULL || grafo->vertices_ordenados == NULL) {
        DestruccionDelGrafo(grafo);
        return NULL;
    }

    for (u32 i = 0u; i < m; ++i) {
        if ((fgets(buffer, 255, stdin) == NULL)) {
            fprintf(stderr, "\tERROR: Formato invalido.\n");
            DestruccionDelGrafo(grafo);
            deleteTree(avl);
            return NULL;
        }
        check =
            sscanf(buffer, "%c %u %u %s", &indicador, &vertx, &lado, discard);
        if (check != 3 || (indicador != 'e')) {
            fprintf(stderr, "\tERROR: Formato invalido.\n");
            DestruccionDelGrafo(grafo);
            deleteTree(avl);
            return NULL;
        }
        // Si no falla, empiezo a cargar vertice y lado al arbol
        // No puedo crear el vertice antes de saber si está en el arbol.
        avl = insert(avl, vertx, grafo, &position, &pos_v); // cargo el vertice
        if (avl == NULL) {
            DestruccionDelGrafo(grafo);
            return NULL;
        }
        v1 = grafo->vertices[pos_v];
        avl = insert(avl, lado, grafo, &position, &pos_l); // cargo el lado
        if (avl == NULL) {
            DestruccionDelGrafo(grafo);
            return NULL;
        }
        v2 = grafo->vertices[pos_l];
        // crear_vecino para v1 y v2 en agregar vecino
        agregar_vecino(grafo, v1, v2);
        agregar_vecino(grafo, v2, v1);
        if (grafo == NULL) {
            deleteTree(avl);
            return NULL;
        }
        grafo->delta = max(grafo->delta, max(v1->grado, v2->grado));
    }
    for (u32 i = 0u; i < n; ++i) {
        if ((grafo->vertices[i]->grado) != (grafo->vertices[i]->size)) {
            grafo->vertices[i]->vecinos = (vecinos *)realloc(
                grafo->vertices[i]->vecinos,
                (grafo->vertices[i]->grado) * sizeof(struct lado_t));
        }
    }

    vertice *v_orden = grafo->vertices_ordenados;
    avl_to_sorting_array(avl, grafo->vertices, &v_orden);
    // Matar el avl, ya que no lo volvemos a usar
    deleteTree(avl);
    return grafo;
}

void DestruccionDelGrafo(Grafo G) {
    if (G == NULL || G->vertices == NULL) {
        return;
    }
    for (u32 i = 0; i < (G->n_vertices) && (G->vertices[i] != NULL); i++) {
        u32 grado = (G->vertices[i]->grado);
        for (u32 j = 0; j < grado && (G->vertices[i]->vecinos != NULL); j++) {
            free(G->vertices[i]->vecinos[j]);
        }
        free(G->vertices[i]->vecinos);
        free(G->vertices[i]);
    }
    free(G->vertices_ordenados);
    free(G->vertices);
    free(G);
}

Grafo CopiarGrafo(Grafo G) {
    if (G == NULL) {
        return NULL;
    }
    Grafo grafo_copia = calloc(1, sizeof(struct GrafoSt));
    if (grafo_copia == NULL) {
        return NULL;
    }
    grafo_copia->n_vertices = G->n_vertices;
    grafo_copia->m_lados = G->m_lados;
    grafo_copia->delta = G->delta;
    grafo_copia->vertices = calloc(G->n_vertices, sizeof(struct _vertice_t));
    if (grafo_copia->vertices == NULL) {
        DestruccionDelGrafo(grafo_copia);
        return NULL;
    }
    grafo_copia->vertices_ordenados =
        calloc(G->n_vertices, sizeof(struct _vertice_t));
    if (grafo_copia->vertices_ordenados == NULL) {
        DestruccionDelGrafo(grafo_copia);
        return NULL;
    }

    for (u32 i = 0u; i < G->n_vertices; ++i) {
        grafo_copia->vertices[i] = calloc(1, sizeof(struct _vertice_t));
        if (grafo_copia->vertices[i] == NULL) {
            DestruccionDelGrafo(grafo_copia);
            return NULL;
        }
        grafo_copia->vertices[i]->posicion = G->vertices[i]->posicion;
        grafo_copia->vertices[i]->color = G->vertices[i]->color;
        grafo_copia->vertices[i]->grado = G->vertices[i]->grado;
        grafo_copia->vertices[i]->size = G->vertices[i]->size;
        grafo_copia->vertices[i]->nombre_real = G->vertices[i]->nombre_real;
        grafo_copia->vertices[i]->vecinos =
            calloc(G->vertices[i]->grado, sizeof(struct lado_t));
        if (grafo_copia->vertices[i]->vecinos == NULL) {
            DestruccionDelGrafo(grafo_copia);
            return NULL;
        }
    }
    for (u32 i = 0u; i < G->n_vertices; ++i) {
        for (u32 j = 0; j < G->vertices[i]->grado; ++j) {
            grafo_copia->vertices[i]->vecinos[j] =
                calloc(1, sizeof(struct lado_t));
            if (grafo_copia->vertices[i]->vecinos[j] == NULL) {
                DestruccionDelGrafo(grafo_copia);
                return NULL;
            }
            grafo_copia->vertices[i]->vecinos[j]->vertice_j =
                grafo_copia
                    ->vertices[G->vertices[i]->vecinos[j]->vertice_j->posicion];
            grafo_copia->vertices[i]->vecinos[j]->peso_u2v =
                G->vertices[i]->vecinos[j]->peso_u2v;
        }
        // recupero la posicion ordenada del vertice para recuperarlo
        // en el arreglo sin orden, así, la copia no genera punteros vacios
        u32 idx_orden = G->vertices_ordenados[i]->posicion;
        grafo_copia->vertices_ordenados[i] = grafo_copia->vertices[idx_orden];
    }
    return grafo_copia;
}

u32 NumeroDeVertices(Grafo G) {
    return G->n_vertices;
}

u32 NumeroDeLados(Grafo G) {
    return G->m_lados;
}

u32 Delta(Grafo G) {
    return G->delta;
}

u32 Nombre(u32 i, Grafo G) {
    return G->vertices[i]->nombre_real;
}

u32 Color(u32 i, Grafo G) {
    if (i >= G->n_vertices) {
        return UINT32_MAX;
    }
    return G->vertices[i]->color;
}
u32 Grado(u32 i, Grafo G) {
    if (i >= G->n_vertices) {
        return UINT32_MAX;
    }
    return G->vertices[i]->grado;
}

u32 ColorVecino(u32 j, u32 i, Grafo G) {
    if ((i >= G->n_vertices) || (j >= G->vertices[i]->grado)) {
        return UINT32_MAX;
    }
    return G->vertices[i]->vecinos[j]->vertice_j->color;
}

u32 NombreVecino(u32 j, u32 i, Grafo G) {
    return G->vertices[i]->vecinos[j]->vertice_j->nombre_real;
}

u32 OrdenVecino(u32 j, u32 i, Grafo G) {
    if ((i >= G->n_vertices)) {
        return UINT32_MAX;
    }
    return G->vertices[i]->vecinos[j]->vertice_j->posicion;
}

u32 PesoLadoConVecino(u32 j, u32 i, Grafo G) {
    return G->vertices[i]->vecinos[j]->peso_u2v;
}

char FijarColor(u32 x, u32 i, Grafo G) {
    if (i < G->n_vertices) {
        G->vertices[i]->color = x;
        return 0;
    }
    return 1;
}        

char FijarOrden(u32 i, Grafo G, u32 N) {
    if (i < G->n_vertices && N < G->n_vertices) {
        G->vertices[i] = G->vertices_ordenados[N];
        G->vertices[i]->posicion = i;
        return 0;
    }
    return 1;
}

u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G) {
    if (i >= G->n_vertices) {
        return UINT32_MAX;
    }
    G->vertices[i]->vecinos[j]->peso_u2v = p;
    return 0;
}