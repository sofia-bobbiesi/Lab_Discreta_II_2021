#include "UnleashHell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    // Inciso 1
    if(argc != 7){
        fprintf(stderr,"ERROR: Formato inválido\n");
        fprintf(stderr,"Cerrando el programa...\n");
        exit(1);
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    int d = atoi(argv[4]);
    int e = atoi(argv[5]);
    int f = atoi(argv[6]);

    Grafo G = ConstruccionDelGrafo();
    if(G == NULL){
        fprintf(stderr,"ERROR: No se pudo cargar el grafo\n");
        fprintf(stderr,"Cerrando el programa...\n");
        exit(1);
    }
    // Inciso 2
    u32 n_vertx = NumeroDeVertices(G);
    printf("Número de vértices para G: %u\n",n_vertx);
    printf("Número de lados para G: %u\n",NumeroDeLados(G));
    printf("Delta de G: %u\n",Delta(G));

    // Inciso 3
    if(Bipartito(G)){
        fprintf(stderr,"El grafo G es bipartito\n");
        fprintf(stderr,"Cerrando el programa...\n");
        exit(0);
    }
    printf("El grafo G NO es bipartito\n");
    // Inciso 4-5
    OrdenNatural(G);
    u32 color = 0;
    u32 mejor_color = n_vertx;
    u32 mejor_semilla = 0;
    for (int i = 0; i <= a; ++i){
        AleatorizarVertices(G,f+i);
        color = Greedy(G);
        printf("El coloreo fue de %u colores\n",color);
        if(color < mejor_color){
            mejor_color = color;
            mejor_semilla = f+i;
        }
    }
    if(mejor_semilla != f + a) {
        AleatorizarVertices(G,mejor_semilla);
        Greedy(G);
    }
    printf("El mejor coloreo fue en %u colores para la semilla: %u\n",mejor_color,mejor_semilla);
    // Inciso 6

    // Inciso 7

    // Inciso 8
    DestruccionDelGrafo(G);
    return 0;
}