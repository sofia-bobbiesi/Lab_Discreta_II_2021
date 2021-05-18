#include "UnleashHell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void RandomizarPermutaciones(u32* perm, u32 len, u32 R){
    // Inicializa los indices en [0 ... len-1]
    for (u32 i = 0u; i < len; ++i){
        perm[i] = i;
    }
    // Establece la semilla que rand() usará para generar números pseudo-aleatorios.
    srand(R); 
    // Algoritmo de Fisher-Yates limitado al R dado.
   int j;
    for (u32 i = len-1; i > 0; --i){
        // Elige un índice aleatorio de 0 a i.
        j = rand() % (i+1);
        // Intercambia perm[i] con el elemento en el índice aleatorio.
        swap(&perm[i], &perm[j]);
    }
}

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
    //float e = atoi(argv[5]);
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
        DestruccionDelGrafo(G);
        exit(0);
    }
    printf("El grafo G NO es bipartito\n");
    // Inciso 4-5
    u32 superGridito = 0; //Nombre final, al que lo cambia lo mato
    OrdenNatural(G);
    u32 color = Greedy(G);
    superGridito++;
    u32 mejor_color_G = color;
    printf("El coloreo fue de %u colores para el orden natural\n",color);
    int mejor_semilla = f;
    for (int i = 0; i < a; ++i) {
        AleatorizarVertices(G,f+i);
        color = Greedy(G);
        superGridito++;
        printf("El coloreo fue de %u colores\n",color);
        if(color < mejor_color_G){
            mejor_color_G = color;
            mejor_semilla = f+i;
        }
    }
    // Si la mejor semilla no fue la última, vuelvo a ordenar
    if(mejor_semilla != f+a-1) {
        AleatorizarVertices(G,mejor_semilla);
        mejor_color_G = Greedy(G);
        superGridito++;
    }
    printf("El mejor coloreo fue en %u colores para la semilla: %u\n", mejor_color_G, mejor_semilla);
    
    // Inciso 6
    u32 *perm = calloc(mejor_color_G, sizeof(u32));
    for (int i = 0; i < b; ++i) {
        RandomizarPermutaciones(perm,mejor_color_G,f+i);
        OrdenPorBloqueDeColores(G,perm);
        color = mejor_color_G;
        mejor_color_G = Greedy(G);
        superGridito++;
        printf("El coloreo fue de %u colores\n", color);
        // Esto en teoría no va, pero viste, uno nunca sabe
        if(mejor_color_G > color){
            free(perm);
            fprintf(stderr,"Te fuiste al orto perry, aprende a programar\n");
            fprintf(stderr,"Cerrando el programa...\n");
            free(perm);
            DestruccionDelGrafo(G);
            exit(1);
        }
    }
    // Inciso 7
    u32 mejor_color_H = mejor_color_G;
    u32 mejor_color_W = mejor_color_G;
    u32 SuperColor = 0;
    for (int i = 0; i < c; ++i) {
        // G en cada corrida va a tener el grafo con mejor coloreo
        // NOTE: capaz habría que hacer un realloc o volver a crear perm
        Grafo H = CopiarGrafo(G);
        Grafo W = CopiarGrafo(G);
        for (int j = 0; j < d; ++j) {
            // Estrategia A:
            RandomizarPermutaciones(perm,mejor_color_G,f+j);
            OrdenPorBloqueDeColores(G,perm);
            mejor_color_G = Greedy(G);
            superGridito++;     

            // Estrategia B:
            for (u32 k = 0; k < mejor_color_H; ++k){
                perm[k] = mejor_color_H-k-1;
            }
            OrdenPorBloqueDeColores(H,perm);
            mejor_color_H = Greedy(H);
            superGridito++;

            /* (c) El tercero ordenará los colores de mayor a menor y luego cambiara aleatoria-
                    mente de lugar ALGUNAS de sus entradas solamente. Para ello mirará cada
                    entrada y con probabilidad 1/e la intercambiará con otra elegida al azar. */
        //     u32 idx_rand = 0;
        //     float prob = 0;
        //     srand(f);
        //     for (u32 k = 0; k < mejor_color_W; ++k) {
        //         idx_rand = rand() % mejor_color_W;
        //         prob = 1/idx_rand;
        //         if (prob == 1/e) {
        //             printf("PROBABILIDAD: %f %f\n",prob, 1/e);
        //             swap(&perm[k],&perm[idx_rand]);
        //         }
        //         OrdenPorBloqueDeColores(W,perm);
        //         mejor_color_W = Greedy(W);
        //         superGridito++;
        //     }
            printf("El coloreo obtenido fue de G: %u, H: %u, W: %u colores\n", mejor_color_G, mejor_color_H, mejor_color_W);
        }
        // Pelea de grafos
        SuperColor = min(min(mejor_color_G, mejor_color_H), mejor_color_W);
        if (SuperColor == mejor_color_H) {
            DestruccionDelGrafo(G);
            G = CopiarGrafo(H);
            mejor_color_G = mejor_color_H;
        }
        else if (SuperColor == mejor_color_W) {
            DestruccionDelGrafo(G);
            G = CopiarGrafo(W);
            mejor_color_G = mejor_color_W;
        }
        DestruccionDelGrafo(H);
        DestruccionDelGrafo(W);
        mejor_color_H = mejor_color_G;
        mejor_color_W = mejor_color_G;
    }
    // Inciso 8
    printf("\nEl último coloreo obtenido fue de %u colores\n", mejor_color_G);
    printf("Se realizaron %u coloreos con Greedy\n", superGridito);

    free(perm);
    DestruccionDelGrafo(G);
    return 0;
}