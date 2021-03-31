#include "avl-tree.h"
#include "sorting.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void imprimir_grafo(Grafo graph) {
    if (graph != NULL) {
        printf("Vertices: %d, Lados: %d\n", graph->n_vertices, graph->m_lados);
        printf("Delta: %d\n", graph->delta);
        for (u32 i = 0; i < graph->n_vertices; i++) {
            vertice curr_vtx = graph->vertices[i];
            printf("Id: %d, Grado: %d, Color: %d\n", curr_vtx->nombre_real,
                   curr_vtx->grado, curr_vtx->color);

            if (curr_vtx->vecinos != NULL) {
                printf("Vecinos: {");
                for (u32 j = 0; j < curr_vtx->grado; j++) {
                    vecinos curr_vecino = curr_vtx->vecinos[j];
                    if (curr_vecino != NULL) {
                        printf("%d", curr_vecino->vertice_j->nombre_real);
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
    vecinos nuevo_vecino = malloc(sizeof(struct lado_t));
    assert(nuevo_vecino != NULL);
    nuevo_vecino->vertice_j = lado;
    nuevo_vecino->peso_u2v = 0;
    return nuevo_vecino;
}

void agregar_vecino(vertice vertx, vertice lado) {
    assert(vertx->vecinos != NULL);
    vertx->vecinos[vertx->grado] = crear_vecino(lado);
    vertx->grado++;
    vertx->vecinos = (vecinos *)realloc(vertx->vecinos,
                                        (vertx->grado) * sizeof(struct lado_t));
}

Grafo ConstruccionDelGrafo() {
    Grafo grafo = malloc(sizeof(struct GrafoSt));
    assert(grafo != NULL);
    char buffer[255], discard[255], edge[255], indicador;
    u32 check = 0, n = 0, m = 0, vertx = 0, lado = 0, position = 0, pos_v = 0;
    vertice v1, v2;
    Node avl = NULL; // creo el arbol
    // Avanza leyendo sobre las lineas que debe omitir ('c')
    while (fgets(buffer, 255, stdin) != NULL && buffer[0] == 'c')
        ;
    // leo la primera linea con los datos del grafo
    check = sscanf(buffer, "%c %s %u %u %s", &indicador, edge, &n, &m, discard);
    if (check != 4 || (indicador != 'p') || strcmp(edge, "edge")) {
        fprintf(stderr, "\tERROR: Formato invalido.\n");
        exit(EXIT_FAILURE);
    }
    /* Si no falla, creo el grafo */
    grafo->n_vertices = n;
    grafo->m_lados = m;
    grafo->delta = 0;
    grafo->vertices = malloc(sizeof(struct _vertice_t) * n);
    assert(grafo->vertices != NULL);

    for (u32 i = 0u; (i < m) && (fgets(buffer, 255, stdin) != NULL); ++i) {
        check =
            sscanf(buffer, "%c %u %u %s", &indicador, &vertx, &lado, discard);
        if (check != 3 || (indicador != 'e')) {
            fprintf(stderr, "\tERROR: Formato invalido.\n");
            exit(EXIT_FAILURE);
        }
        // Si no falla, empiezo a cargar vertice y lado al arbol
        // No puedo crear el vertice antes de saber si está en el arbol.
        avl = insert(avl, vertx, grafo, &position, &pos_v); // cargo el vertice
        v1 = grafo->vertices[pos_v]; // NOTE: si sale mal antes era puntero xd
        avl = insert(avl, lado, grafo, &position, &pos_v); // cargo el lado
        v2 = grafo->vertices[pos_v];
        // crear_vecino para v1 y v2 en agregar vecino
        agregar_vecino(v1, v2);
        agregar_vecino(v2, v1);

        // defino el delta xdxd
        grafo->delta = max(grafo->delta, max(v1->grado, v2->grado));
    }
    // Matar el avl, ya que no lo volvemos a usar
    deleteTree(avl);
    return grafo;
}

void DestruccionDelGrafo(Grafo G) {
    if (G != NULL) {
        u32 n = G->n_vertices;
        for (u32 i = 0; i < n && (G->vertices != NULL); ++i) {
            if (G->vertices[i] != NULL) {
                u32 grado = G->vertices[i]->grado;
                for (u32 j = 0; j < grado && (G->vertices[i]->vecinos != NULL);
                     ++j) {
                    if (G->vertices[i]->vecinos[j] != NULL) {
                        free(G->vertices[i]->vecinos[j]);
                        G->vertices[i]->vecinos[j] = NULL;
                    }
                }
                free(G->vertices[i]->vecinos);
                G->vertices[i]->vecinos = NULL;
                free(G->vertices[i]);
                G->vertices[i] = NULL;
            }
        }
        free(G->vertices);
        G->vertices = NULL;
        free(G);
        G = NULL;
    }
}

Grafo CopiarGrafo(Grafo G) {
    Grafo grafo_copia = calloc(1, sizeof(struct GrafoSt));
    assert(grafo_copia != NULL);
    grafo_copia->n_vertices = G->n_vertices;
    grafo_copia->m_lados = G->m_lados;
    grafo_copia->delta = G->delta;
    grafo_copia->vertices = malloc(sizeof(struct _vertice_t) * G->n_vertices);
    assert(grafo_copia->vertices != NULL);

    for (u32 i = 0u; i < G->n_vertices; ++i) {
        grafo_copia->vertices[i] = malloc(sizeof(struct _vertice_t));
        grafo_copia->vertices[i]->color = G->vertices[i]->color;
        grafo_copia->vertices[i]->grado = G->vertices[i]->grado;
        grafo_copia->vertices[i]->nombre_real = G->vertices[i]->nombre_real;
        grafo_copia->vertices[i]->vecinos =
            malloc(sizeof(struct lado_t) * G->vertices[i]->grado);
        for (u32 j = 0; j < G->vertices[i]->grado; ++j) {
            grafo_copia->vertices[i]->vecinos[j] =
                malloc(sizeof(struct lado_t));
            grafo_copia->vertices[i]->vecinos[j]->vertice_j =
                G->vertices[i]->vecinos[j]->vertice_j;
            grafo_copia->vertices[i]->vecinos[j]->peso_u2v =
                G->vertices[i]->vecinos[j]->peso_u2v;
        }
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
    u32 res = 0;
    for (u32 k = 0u; k < G->n_vertices; ++k) {
        if (G->vertices[i]->vecinos[j]->vertice_j == G->vertices[k]) {
            res = k;
            break;
        }
    }
    return res;
}

u32 PesoLadoConVecino(u32 j, u32 i, Grafo G) {
    return G->vertices[i]->vecinos[j]->peso_u2v;
}

char FijarColor(u32 x, u32 i, Grafo G) {
    if (i < G->n_vertices) {
        (G->vertices[i])->color = x;
        return 0;
    }
    return 1;
}

char FijarOrden(u32 i, Grafo G, u32 N) {
    if (i < G->n_vertices && N < G->n_vertices) {
        // NOTE: basta con ordenar el arreglo y recuperar la posición N.
        Grafo G_copia = CopiarGrafo(G);
        radix_sort(G_copia, G_copia->n_vertices);
        G->vertices[i] = G_copia->vertices[N];
        return 0;
    }
    return 1;
}

u32 FijarPesoLadoConVecino(u32 j, u32 i, u32 p, Grafo G) {
    if (i >= G->n_vertices) {
        return UINT32_MAX;
    }
    G->vertices[i]->vecinos[j]->peso_u2v = p;
    return 1; // NOTE: qué retorna el caso exitoso?
}

int main() {
    Grafo graph = ConstruccionDelGrafo();
    Grafo copito = CopiarGrafo(graph);
    imprimir_grafo(copito);
    DestruccionDelGrafo(copito);
    DestruccionDelGrafo(graph);
    return 0;
}